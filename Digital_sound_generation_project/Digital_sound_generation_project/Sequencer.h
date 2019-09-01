#pragma once
#include <vector>

#include "Note.h"
#include "Synthesizer.h"

class Sequencer {
public:
	float run(int time, int sampleFrequency, int maxAmplitude);
	void addNote(int duration, int frequency, int startTime, float volume, float phase, int generationType, int sampleIndex, Envelope envelope);
	void addDot(int startTime, float volume);
	Envelope getEnvelope(float attack, float decay, float sustain, float release);
	void setSampleFrequency(int _sampleFrequency);
	int getSize();
	float getFreq(int _index);
private:
	int sampleFrequency;
	Synthesizer synthesizer;
	float playNote(Note note, int time, int sampleFrequency, int maxAmplitude);
	float getEnvelopeAmplitude(Note note, int time);
	std::vector<Note> notes;
};