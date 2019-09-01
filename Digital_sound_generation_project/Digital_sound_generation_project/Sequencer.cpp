#include "Sequencer.h"
//gets the output a a specific point in time
float Sequencer::run(int time, int sampleFrequency, int maxAmplitude)
{
	float output = 0;
	for (int i = 0; i < notes.size(); i++) {
		//deletes a note if it's already been played
		if (time > notes[i].getTotalDuration() + notes[i].startTime ) {
			//notes.erase(notes.begin() + i);
			//i--;
		}
		else if (time > notes[i].startTime){
			if (time < notes[i].startTime + notes[i].getTotalDuration()) {
				//if too close to the end, return 0
				float waveLengthInSamples = (float)sampleFrequency / notes[i].frequency;
				//if the endpoint of the note minus current time is smaller than a full wavelength, dont do anything, otherwise add the proper displacement
				if (notes[i].startTime + notes[i].getTotalDuration() - time + waveLengthInSamples*notes[i].startPhase > waveLengthInSamples) {
					//adds the displacement from the note at the current time to the final sequencer output
					output += playNote(notes[i], time, sampleFrequency, maxAmplitude);
					// notes[i].dutyCycle += 0.000001;
				}
				
			}
		}
	}
	return output * maxAmplitude;
}

void Sequencer::addNote(int duration, int frequency, int startTime, float volume, float phase, int generationType, int sampleIndex, Envelope envelope)
{
	Note note;
	note.duration = duration;
	note.frequency = frequency;
	note.startTime = startTime;
	note.volume = volume;
	note.generationType = generationType;
	note.sampleIndex = sampleIndex;
	note.envelope = envelope;
	note.startPhase = phase;
	note.dutyCycle = 0.0;
	notes.push_back(note);
}

void Sequencer::addDot(int startTime, float volume)
{
	Note note;
	Envelope envelope;
	envelope.attack = 0;
	envelope.decay = 0;
	envelope.sustain = 1;
	envelope.release = 0;
	note.duration = 3;
	note.startTime = startTime;
	note.volume = volume;
	note.generationType = 5;
	note.envelope = envelope;
	notes.push_back(note);
}

Envelope Sequencer::getEnvelope(float attack, float decay, float sustain, float release)
{
	Envelope envelope;
	envelope.attack = attack;
	envelope.decay = decay;
	envelope.sustain = sustain;
	envelope.release = release;
	return envelope;
}

void Sequencer::setSampleFrequency(int _sampleFrequency)
{
	sampleFrequency = _sampleFrequency;
}

int Sequencer::getSize()
{
	return notes.size();
}

float Sequencer::getFreq(int _index)
{
	return notes[_index].frequency;
}

float Sequencer::playNote(Note note, int time, int sampleFrequency, int maxAmplitude)
{
	float output = 0;
	//getting the apmlitude of the envelope at this point in time
	float envelopeAmplitude = getEnvelopeAmplitude(note, time);
	//0: sin, 1: saw, 2: triangle, 3: square, 4: noise, 5: clipping dot, 6: pwm
	switch (note.generationType) {
	case 0:
		output = synthesizer.sinOscillator(time, note.frequency, envelopeAmplitude, note.startPhase, sampleFrequency, maxAmplitude);
		break;
	case 1:
		output = synthesizer.sawOscillator(time, note.frequency, envelopeAmplitude, note.startPhase, sampleFrequency, maxAmplitude);
		break;
	case 2:
		output = synthesizer.triangleOscillator(time, note.frequency, envelopeAmplitude, note.startPhase, sampleFrequency, maxAmplitude);
		break;
	case 3:
		output = synthesizer.squareOscillator(time, note.frequency, envelopeAmplitude, note.startPhase, sampleFrequency, maxAmplitude);
		break;
	case 4:
		output = synthesizer.noiseGenerator(envelopeAmplitude);
		break;
	case 5:
		output = synthesizer.dotGenerator(time, note.startTime, note.duration, note.volume, maxAmplitude);
		break;
	case 6:
		output = synthesizer.pwmGenerator(note.startTime, time, note.dutyCycle, note.frequency, envelopeAmplitude, note.startPhase, sampleFrequency, maxAmplitude);
		break;
	}
	//printf("%f\n", output);
	return output;
}

//getting a value between 0 and 1 to be multiplied by the notes amplitude to implement the envelope
float Sequencer::getEnvelopeAmplitude(Note note, int time)
{
	float envelopeAmplitude = 0;
	//if still in the attack section of the envelope
	if (note.envelope.attack && time > note.startTime && time < note.startTime + note.envelope.attack) {
		envelopeAmplitude = ((float)time - note.startTime) / note.envelope.attack;
	}
	//if still in the decay section of the envelope
	else if (note.envelope.decay && time > note.startTime + note.envelope.attack && time < time + note.startTime + note.envelope.attack + note.envelope.decay) {
		envelopeAmplitude = note.envelope.sustain + (1 - (time - (note.startTime + note.envelope.attack)) / note.envelope.decay) * (1 - note.envelope.sustain);
	}
	//if still in the sustain section of the envelope
	else if (time >= note.startTime + note.envelope.attack + note.envelope.decay && time <= note.startTime + note.duration) {
		envelopeAmplitude = note.envelope.sustain;
	}
	//if still in the release section of the envelope
	else if (note.envelope.release && time > note.startTime + note.duration && time < note.startTime + note.duration + note.envelope.release) {
		envelopeAmplitude = 1 * (1-((float)time - (note.startTime + note.duration)) / note.envelope.release);
	}
	return envelopeAmplitude * note.volume;
}
