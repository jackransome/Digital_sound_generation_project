#pragma once
struct Envelope {
	float attack;
	float decay;
	float sustain;//(between 1 and 0), it is a volume unit not a time unit
	float release;
};