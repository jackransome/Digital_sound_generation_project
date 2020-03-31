#include <cmath>
#include "Synthesizer.h"

constexpr double two_pi = 6.283185307179586476925286766559;

//saw wave generator
float Synthesizer::sawOscillator(int _time, float _frequency, float _phase, int _sampleFrequency) {
	float normalizedPlaceInWave = getNormalizedPlaceInWave(_sampleFrequency, _frequency, _time, _phase);

	//finding the displacement at this point in time

	if (normalizedPlaceInWave < 0.5) {
		return (normalizedPlaceInWave*2);
	}
	else {
		return -1 + (normalizedPlaceInWave - 0.5) * 2;
	}
}

//sin wave generator
float Synthesizer::sinOscillator(int _time, float _frequency, float _phase, int _sampleFrequency) {
	

	float normalizedPlaceInWave = getNormalizedPlaceInWave(_sampleFrequency, _frequency, _time, _phase);
	//finding the displacement at this point in time
	float final = sin(two_pi * (normalizedPlaceInWave));
	return final;
}

//square wave generator
float Synthesizer::squareOscillator(int _time, float _frequency, float _phase, int _sampleFrequency) {
	float normalizedPlaceInWave = getNormalizedPlaceInWave(_sampleFrequency, _frequency, _time, _phase);
	//finding the displacement at this point in time
	float final = (round(normalizedPlaceInWave)) * 2 - 1;
	return final;
}

//triangle wave generator
float Synthesizer::triangleOscillator(int _time, float _frequency, float _phase, int _sampleFrequency) {
	float normalizedPlaceInWave = getNormalizedPlaceInWave(_sampleFrequency, _frequency, _time, _phase);
	//finding the displacement at this point in time
	float final;
	if (normalizedPlaceInWave < 0.25) {
		final = (normalizedPlaceInWave * 4);
	}
	else if (normalizedPlaceInWave < 0.75) {
		final = 1 - (normalizedPlaceInWave - 0.25) * 4;
	}
	else {
		final = -1 + (normalizedPlaceInWave - 0.75) * 4;
	}
	return final;
}

//white noise generator
float Synthesizer::noiseGenerator() {
	return static_cast <float> (rand()) / static_cast <float> (RAND_MAX) * 2 - 1;
}

float Synthesizer::dotGenerator(int _time, int _startTime, int _duration, float _volume, int _maxAmplitude)
{
	if (_time > _startTime) {
		float pos = _time - _startTime;
		float absPos = pos / _duration;
		if (absPos < 0.5) {
			return _volume * absPos * 2;
		}
		else {
			return _volume * (1 - absPos) * 2;
		}
		
	}
	return 0;
}

float Synthesizer::pwmGenerator(int _startTime, int _time, float _dutyCycle, float _frequency, float _phase, int _sampleFrequency)
{
	float wavelength = (float)_sampleFrequency / _frequency;
	float placeInWave = fmod((_time - _startTime), wavelength);
	float normalizedPlaceInWave = placeInWave / (float)wavelength;

	if (normalizedPlaceInWave < _dutyCycle) {
		return 1;
	}
	else {
		return 0;
	}

}

float Synthesizer::getNormalizedPlaceInWave(int _sampleFrequency, float _frequency, int _time, float _phase)
{
	//get number of samples in a wavelength
	float waveLengthInSamples = (float)_sampleFrequency / _frequency;
	//get position in the full wavelength
	float placeInWave = fmod(_time + _phase * waveLengthInSamples, waveLengthInSamples);
	//get normalized position (range from 0 to waveLengthInSamples converted to 0 to 1)
	return placeInWave / (float)waveLengthInSamples;
}
