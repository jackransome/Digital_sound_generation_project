#pragma once
class HighpassFilter {
public:
	HighpassFilter(int _sampleRate);
	~HighpassFilter();
	float getOutput(float _input);
	void changeResistance(float _multiplier);
private:
	float lastValue;
	int sampleRate;
	float resistance = 10000;
	float capacitance = 1.5/1000000000;
};