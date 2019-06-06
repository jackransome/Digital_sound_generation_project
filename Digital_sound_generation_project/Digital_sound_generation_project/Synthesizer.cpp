#include <cmath>
#include "Synthesizer.h"

constexpr double two_pi = 6.283185307179586476925286766559;

//saw wave generator
float Synthesizer::sawOscillator(int time, float frequency, float amplitude, float phase, int sampleFrequency, int maxAmplitude) {
	//get number of samples in a wavelength
	float waveLengthInSamples = (float)sampleFrequency / frequency;
	//get position in the full wavelength
	float placeInWave = fmod(time + phase * waveLengthInSamples + waveLengthInSamples / 2, waveLengthInSamples);
	//get normalized position (range from 0 to waveLengthInSamples converted to 0 to 1)
	float normalizedPlaceInWave = placeInWave / (float)waveLengthInSamples;
	//finding the displacement at this point in time
	float final = (amplitude / 2 - (normalizedPlaceInWave * amplitude))/* +((float)maxAmplitude / 2)*/;
	return final;
}

//sin wave generator
float Synthesizer::sinOscillator(int time, float frequency, float amplitude, float phase, int sampleFrequency, int maxAmplitude) {
	//get number of samples in a wavelength
	float waveLengthInSamples = (float)sampleFrequency / frequency;
	//get position in the full wavelength
	float placeInWave = fmod(time + phase * waveLengthInSamples + waveLengthInSamples / 2, waveLengthInSamples);
	//get normalized position (range from 0 to waveLengthInSamples converted to 0 to 1)
	float normalizedPlaceInWave = placeInWave / (float)waveLengthInSamples;
	//finding the displacement at this point in time
	float final = sin(two_pi * (normalizedPlaceInWave)) * amplitude/* +((float)maxAmplitude / 2)*/;
	return final;
}

//square wave generator
float Synthesizer::squareOscillator(int time, float frequency, float amplitude, float phase, int sampleFrequency, int maxAmplitude) {
	//get number of samples in a wavelength
	float waveLengthInSamples = (float)sampleFrequency / frequency;
	//get position in the full wavelength
	float placeInWave = fmod(time + phase * waveLengthInSamples + waveLengthInSamples / 2, waveLengthInSamples);
	//get normalized position (range from 0 to waveLengthInSamples converted to 0 to 1)
	float normalizedPlaceInWave = placeInWave / (float)waveLengthInSamples;
	//finding the displacement at this point in time
	float final = (round(normalizedPlaceInWave) * amplitude - amplitude / 2)/* +((float)maxAmplitude / 2)*/;
	return final;
}

//triangle wave generator
float Synthesizer::triangleOscillator(int time, float frequency, float amplitude, float phase, int sampleFrequency, int maxAmplitude) {
	//get number of samples in a wavelength
	float waveLengthInSamples = (float)sampleFrequency / frequency;
	//get position in the full wavelength
	float placeInWave = fmod(time + phase * waveLengthInSamples + waveLengthInSamples / 2, waveLengthInSamples);
	//get normalized position (range from 0 to waveLengthInSamples converted to 0 to 1)
	float normalizedPlaceInWave = placeInWave / (float)waveLengthInSamples;
	//finding the displacement at this point in time
	float final;
	if (normalizedPlaceInWave < 0.5) {
		final = (2 * normalizedPlaceInWave * amplitude - amplitude / 2)/* +((float)maxAmplitude / 2)*/;
	}
	else {
		final = (amplitude / 2 - 2 * (normalizedPlaceInWave - 0.5) * amplitude)/* +((float)maxAmplitude / 2)*/;
	}
	return final;
}

//white noise generator
float Synthesizer::noiseGenerator(float amplitude) {
	float random = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	float final = random * amplitude / 2 - amplitude / 2;
	return final;
}
