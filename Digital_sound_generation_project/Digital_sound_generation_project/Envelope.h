#pragma once
struct Envelope {
	Envelope() {};
	Envelope(float _attack, float _decay, float _sustain, float _release) {
		attack = _attack;
		decay = _decay;
		sustain = _sustain;
		release = _release;
	}
	float attack;
	float decay;
	float sustain;//(between 1 and 0), it is a volume unit not a time unit
	float release;
};