#pragma once
struct Envelope {
	int attack;
	int decay;
	int sustain;//(between 1 and 0), it is a volume unit not a time unit
	int release;
};