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
		else if (time >= notes[i].startTime){
			if (time < notes[i].startTime + notes[i].getTotalDuration()) {
				//if too close to the end, return 0
				float waveLengthInSamples = (float)sampleFrequency / notes[i].frequency;
				//if the endpoint of the note minus current time is smaller than a full wavelength, dont do anything, otherwise add the proper displacement
				if (notes[i].startTime + notes[i].getTotalDuration() - time + waveLengthInSamples*notes[i].startPhase > waveLengthInSamples) {
					
					if (time > sampleFrequency * 5) {
						int y = 0;
						y--;
					}
					//applying lfo
					// applyLFO(time);
					//adds the displacement from the note at the current time to the final sequencer output
					output += playNote(notes[i], time, sampleFrequency, maxAmplitude);
				}
				
			}
		}
	}
	return output * maxAmplitude;
}

void Sequencer::addNote(int duration, int frequency, int startTime, float volume, float phase, float dutyCycle, int generationType, int sampleIndex, Envelope envelope)
{
	notes.push_back(Note(duration, frequency, startTime, volume, generationType, sampleIndex, dutyCycle, phase, envelope));
}

void Sequencer::addNote(int duration, int frequency, int startTime, float volume, int generationType, Envelope envelope)
{
	notes.push_back(Note(duration, frequency, startTime, volume, generationType, -1, 0, 0, envelope));
}

void Sequencer::addDot(int startTime, float volume)
{
	notes.push_back(Note(3, 0, startTime, volume, 5, -1, 0, 0, Envelope(0,0,1,0)));
}

void Sequencer::setSampleFrequency(int _sampleFrequency)
{
	sampleFrequency = _sampleFrequency;
}

void Sequencer::addLFO(float * _target, float _startPhase, float _frequency, int _waveForm, float _amplitude)
{
	LFOs.push_back(LFO(_target, _startPhase, _frequency, _waveForm, _amplitude));
}

int Sequencer::getSize()
{
	return notes.size();
}

Envelope Sequencer::getEnvelope(float _attack, float _decay, float _sustain, float _release)
{
	return Envelope(_attack, _decay, _sustain, _release);
}

float Sequencer::getFreq(int _index)
{
	return notes[_index].frequency;
}

Note* Sequencer::getLastNote()
{
	return &notes[notes.size()-1];
}

void Sequencer::applyLFO(int time)
{
	float value;
	for (int i = 0; i < LFOs.size(); i++) {
		//0: sin, 1: saw, 2: triangle, 3: square, 4: noise, 5: clipping dot, 6: pwm
		switch (LFOs[i].waveForm) {
		case 0:
			value = synthesizer.sinOscillator(time, LFOs[i].frequency, LFOs[i].startPhase, sampleFrequency) * LFOs[i].amplitude;
			break;
		case 1:
			value = synthesizer.sawOscillator(time, LFOs[i].frequency, LFOs[i].startPhase, sampleFrequency) * LFOs[i].amplitude;
			break;
		case 2:
			value = synthesizer.triangleOscillator(time, LFOs[i].frequency, LFOs[i].startPhase, sampleFrequency) * LFOs[i].amplitude;
			break;
		case 3:
			value = synthesizer.squareOscillator(time, LFOs[i].frequency, LFOs[i].startPhase, sampleFrequency) * LFOs[i].amplitude;
			break;
		case 4:
			value = synthesizer.noiseGenerator() * LFOs[i].amplitude;
			break;
		case 6:
			//value = synthesizer.pwmGenerator(time, LFOs[i].frequency, LFOs[i].amplitude, LFOs[i].startPhase, sampleFrequency, maxAmplitude);
			break;
		}
		*LFOs[i].target *= value;
	}
}

void Sequencer::removeLFO(int time)
{
	float value;
	for (int i = 0; i < LFOs.size(); i++) {
		//0: sin, 1: saw, 2: triangle, 3: square, 4: noise, 5: clipping dot, 6: pwm
		switch (LFOs[i].waveForm) {
		case 0:
			value = synthesizer.sinOscillator(time, LFOs[i].frequency, LFOs[i].startPhase, sampleFrequency) * LFOs[i].amplitude;
			break;
		case 1:
			value = synthesizer.sawOscillator(time, LFOs[i].frequency, LFOs[i].startPhase, sampleFrequency) * LFOs[i].amplitude;
			break;
		case 2:
			value = synthesizer.triangleOscillator(time, LFOs[i].frequency, LFOs[i].startPhase, sampleFrequency) * LFOs[i].amplitude;
			break;
		case 3:
			value = synthesizer.squareOscillator(time, LFOs[i].frequency, LFOs[i].startPhase, sampleFrequency) * LFOs[i].amplitude;
			break;
		case 4:
			value = synthesizer.noiseGenerator() * LFOs[i].amplitude;
			break;
		case 6:
			//value = synthesizer.pwmGenerator(time, LFOs[i].frequency, LFOs[i].amplitude, LFOs[i].startPhase, sampleFrequency, maxAmplitude);
			break;
		}
		*LFOs[i].target /= value;
	}
}

float Sequencer::playNote(Note _note, int _time, int _sampleFrequency, int _maxAmplitude)
{
	float output = 0;
	//getting the apmlitude of the envelope at this point in time
	float envelopeAmplitude = getEnvelopeAmplitude(_note, _time);
	//0: sin, 1: saw, 2: triangle, 3: square, 4: noise, 5: clipping dot, 6: pwm
	switch (_note.generationType) {
	case 0:
		output = synthesizer.sinOscillator(_time, _note.frequency, _note.startPhase, _sampleFrequency) * envelopeAmplitude;
		break;
	case 1:
		output = synthesizer.sawOscillator(_time, _note.frequency, _note.startPhase, _sampleFrequency) * envelopeAmplitude;
		break;
	case 2:
		output = synthesizer.triangleOscillator(_time, _note.frequency, _note.startPhase, _sampleFrequency) * envelopeAmplitude;
		break;
	case 3:
		output = synthesizer.squareOscillator(_time, _note.frequency, _note.startPhase, _sampleFrequency) * envelopeAmplitude;
		break;
	case 4:
		output = synthesizer.noiseGenerator() * envelopeAmplitude;
		break;
	case 5:
		output = synthesizer.dotGenerator(_time, _note.startTime, _note.duration, _note.volume, _maxAmplitude);
		break;
	case 6:
		output = synthesizer.pwmGenerator(_note.startTime, _time, _note.dutyCycle, _note.frequency, _note.startPhase, _sampleFrequency) * envelopeAmplitude;
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
