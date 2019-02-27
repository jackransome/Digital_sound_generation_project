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
	int generationType; //0: sin, 1: saw, 2: triangle, 3: square, 4: noise
	int sampleIndex; //leave as -1 for none
	Envelope envelope;
};