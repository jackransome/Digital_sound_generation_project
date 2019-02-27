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
				//adds the displacement from the note at the current time to the final sequencer output
				output += playNote(notes[i], time, sampleFrequency, maxAmplitude);
			}
		}
	}
	return output * maxAmplitude;
}

void Sequencer::addNote(int duration, int frequency, int startTime, float volume, int generationType, int sampleIndex, Envelope envelope)
{
	Note note;
	note.duration = duration;
	note.frequency = frequency;
	note.startTime = startTime;
	note.volume = volume;
	note.generationType = generationType;
	note.sampleIndex = sampleIndex;
	note.envelope = envelope;
	notes.push_back(note);
}

Envelope Sequencer::getEnvelope(int attack, int decay, int sustain, int release)
{
	Envelope envelope;
	envelope.attack = attack;
	envelope.decay = decay;
	envelope.sustain = sustain;
	envelope.release = release;
	return envelope;
}

float Sequencer::playNote(Note note, int time, int sampleFrequency, int maxAmplitude)
{
	float output = 0;
	//getting the apmlitude of the envelope at this point in time
	float envelopeAmplitude = getEnvelopeAmplitude(note, time);
	//0: sin, 1: saw, 2: triangle, 3: square, 4: noise
	switch (note.generationType) {
	case 0:
		output = synthesizer.sinOscillator(time, note.frequency, envelopeAmplitude, 0, sampleFrequency, maxAmplitude);
		break;
	case 1:
		output = synthesizer.sawOscillator(time, note.frequency, envelopeAmplitude, 0, sampleFrequency, maxAmplitude);
		break;
	case 2:
		output = synthesizer.triangleOscillator(time, note.frequency, envelopeAmplitude, 0, sampleFrequency, maxAmplitude);
		break;
	case 3:
		output = synthesizer.squareOscillator(time, note.frequency, envelopeAmplitude, 0, sampleFrequency, maxAmplitude);
		break;
	case 4:
		output = synthesizer.noiseGenerator(envelopeAmplitude);
		break;
	}
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
