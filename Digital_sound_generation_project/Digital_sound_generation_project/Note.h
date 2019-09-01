#pragma once
#include "Envelope.h"
struct Note {
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