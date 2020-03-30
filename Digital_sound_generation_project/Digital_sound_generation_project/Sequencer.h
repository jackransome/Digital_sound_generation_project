#pragma once
#include <vector>

#include "Splitter.h"
#include "Note.h"
#include "Synthesizer.h"
#include "LFO.h"
class Sequencer {
public:
	float run(int time, int sampleFrequency, int maxAmplitude);
	void addNote(int duration, int frequency, int startTime, float volume, float phase, float dutyCycle, int generationType, int sampleIndex, Envelope envelope);
	void addNote(int duration, int frequency, int startTime, float volume, int generationType, Envelope envelope);
	void addDot(int startTime, float volume);
	void setSampleFrequency(int _sampleFrequency);
	void addLFO(float* _target, float _startPhase, float _frequency, int _waveForm, float _amplitude);
	int getSize();
	float getFreq(int _index);
	Note* getLastNote();
	void applyLFO(int time);
	void removeLFO(int time);
private:
	int sampleFrequency;
	Synthesizer synthesizer;
	float playNote(Note note, int time, int sampleFrequency, int maxAmplitude);
	float getEnvelopeAmplitude(Note note, int time);
	std::vector<Note> notes;
	std::vector<LFO> LFOs;
	std::vector<Splitter> Splitters;
};