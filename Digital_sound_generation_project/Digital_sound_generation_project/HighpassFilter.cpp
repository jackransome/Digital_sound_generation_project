#include "HighpassFilter.h"
#include <math.h>
HighpassFilter::HighpassFilter(int _sampleRate) {
	sampleRate = _sampleRate;
	lastValue = 0;
}

HighpassFilter::~HighpassFilter() {}

float HighpassFilter::getOutput(float _input)
{
	float thing = -(1.0f / sampleRate) / (resistance*capacitance);
	float output = _input - (_input + (lastValue - _input)*exp(-(1.0f / sampleRate) / (resistance*capacitance)));
	lastValue = output;
	return output;
}

void HighpassFilter::changeResistance(float _multiplier){
	resistance *= _multiplier;
}
