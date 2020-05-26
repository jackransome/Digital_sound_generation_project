#include "LowpassFilter.h"
#include <math.h>
LowpassFilter::LowpassFilter(int _sampleRate) {
	sampleRate = _sampleRate;
}

LowpassFilter::~LowpassFilter(){}

float LowpassFilter::getOutput(float _input)
{
	float final = _input;

	float output = _input + (lastValue - _input)*exp(-(1.0f / sampleRate) / (resistance*capacitance));
	lastValue = output;
	return output;
}