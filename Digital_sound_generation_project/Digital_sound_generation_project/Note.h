#pragma once
#include "Lfo.h"
#include "Envelope.h"
struct Note {
	Note(int _duration, int _frequency, int _startTime, float _volume, int _generationType, int _sampleIndex, float _dutyCycle, float _startPhase, Envelope _envelope) {
		duration = _duration;
		frequency = _frequency;
		startTime = _startTime;
		volume = _volume;
		generationType = _generationType;
		sampleIndex = _sampleIndex;
		dutyCycle = _dutyCycle;
		startPhase = _startPhase;
		envelope = _envelope;
	}
	int duration;
	int getTotalDuration() {
		return duration + envelope.release;
	}
	int frequency;
	int startTime;
	float volume;
	int generationType; //0: sin, 1: saw, 2: triangle, 3: square, 4: noise, 5: dot, 6: pwm
	int sampleIndex; //leave as -1 for none
	float dutyCycle;
	float startPhase;
	Envelope envelope;
};