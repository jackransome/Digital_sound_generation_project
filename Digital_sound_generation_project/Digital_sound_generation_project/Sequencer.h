#pragma once
#include <vector>

#include "Note.h"
#include "Synthesizer.h"

class Sequencer {
public:
	float run(int time, int sampleFrequency, int maxAmplitude);
	void addNote(int duration, int frequency, int startTime, float volume, int generationType, int sampleIndex, Envelope envelope);
	Envelope getEnvelope(int attack, int decay, int sustain, int release);
private:
	Synthesizer synthesizer;
	float playNote(Note note, int time, int sampleFrequency, int maxAmplitude);
	float getEnvelopeAmplitude(Note note, int time);
	std::vector<Note> notes;
};