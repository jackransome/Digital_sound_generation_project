#pragma once
class LowpassFilter {
public:
	LowpassFilter(int _sampleRate);
	~LowpassFilter();
	float getOutput(float _input);
private:
	float lastValue;
	int sampleRate;
	float resistance = 0.1;
	float capacitance = 0.01;
};