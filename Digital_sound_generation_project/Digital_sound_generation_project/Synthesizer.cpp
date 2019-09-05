#include <cmath>
#include "Synthesizer.h"

constexpr double two_pi = 6.283185307179586476925286766559;

//saw wave generator
float Synthesizer::sawOscillator(int time, float frequency, float phase, int sampleFrequency, float min, float max) {
	//get number of samples in a wavelength
	float waveLengthInSamples = (float)sampleFrequency / frequency;
	//get position in the full wavelength
	float placeInWave = fmod(time + phase * waveLengthInSamples + waveLengthInSamples / 2, waveLengthInSamples);
	//get normalized position (range from 0 to waveLengthInSamples converted to 0 to 1)
	float normalizedPlaceInWave = placeInWave / (float)waveLengthInSamples;
	//finding the "middle":
	float middle = (max - min) / 2;
	//finding half amplitude
	
	float halfAmplitude = max - middle;

	//finding the displacement at this point in time

	if (normalizedPlaceInWave < 0.5) {
		return middle - normalizedPlaceInWave * 2 * halfAmplitude;
	}
	else {
		return middle + (1 - normalizedPlaceInWave) * 2 * halfAmplitude;
	}
}

//sin wave generator
float Synthesizer::sinOscillator(int time, float frequency, float phase, int sampleFrequency, float min, float max) {
	

	//get number of samples in a wavelength
	float waveLengthInSamples = (float)sampleFrequency / frequency;
	//get position in the full wavelength in samples
	float placeInWave = fmod(time + phase * waveLengthInSamples, waveLengthInSamples);
	//get normalized position (range from 0 to waveLengthInSamples converted to 0 to 1)
	float normalizedPlaceInWave = placeInWave / (float)waveLengthInSamples;
	//finding the displacement at this point in time
	float final = 0;//sin(two_pi * (normalizedPlaceInWave)) * amplitude/* +((float)maxAmplitude / 2)*/;
	return final;
}

//square wave generator
float Synthesizer::squareOscillator(int time, float frequency, float phase, int sampleFrequency, float min, float max) {
	//get number of samples in a wavelength
	float waveLengthInSamples = (float)sampleFrequency / frequency;
	//get position in the full wavelength
	float placeInWave = fmod(time + phase * waveLengthInSamples + waveLengthInSamples / 2, waveLengthInSamples);
	//get normalized position (range from 0 to waveLengthInSamples converted to 0 to 1)
	float normalizedPlaceInWave = placeInWave / (float)waveLengthInSamples;
	//finding the displacement at this point in time
	float final = 0;// (round(normalizedPlaceInWave) * amplitude - amplitude / 2)/* +((float)maxAmplitude / 2)*/;
	return final;
}

//triangle wave generator
float Synthesizer::triangleOscillator(int time, float frequency, float phase, int sampleFrequency, float min, float max) {
	//get number of samples in a wavelength
	float waveLengthInSamples = (float)sampleFrequency / frequency;
	//get position in the full wavelength
	float placeInWave = fmod(time + phase * waveLengthInSamples + waveLengthInSamples / 2, waveLengthInSamples);
	//get normalized position (range from 0 to waveLengthInSamples converted to 0 to 1)
	float normalizedPlaceInWave = placeInWave / (float)waveLengthInSamples;
	//finding the displacement at this point in time
	float final;
	if (normalizedPlaceInWave < 0.5) {
		final = 0;// (2 * normalizedPlaceInWave * amplitude - amplitude / 2)/* +((float)maxAmplitude / 2)*/;
	}
	else {
		final = 0;// (amplitude / 2 - 2 * (normalizedPlaceInWave - 0.5) * amplitude)/* +((float)maxAmplitude / 2)*/;
	}
	return final;
}

//white noise generator
float Synthesizer::noiseGenerator(float amplitude) {
	float random = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	float final = random * amplitude / 2 - amplitude / 2;
	return final;
}

float Synthesizer::dotGenerator(int time, int startTime, int duration, float volume, int maxAmplitude)
{
	if (time > startTime) {
		float pos = time - startTime;
		float absPos = pos / duration;
		if (absPos < 0.5) {
			return volume * absPos * 2;
		}
		else {
			return volume * (1 - absPos) * 2;
		}
		
	}
	return 0;
}

float Synthesizer::pwmGenerator(int startTime, int time, float dutyCycle, float frequency, float phase, int sampleFrequency, float min, float max)
{
	float wavelength = (float)sampleFrequency / frequency;
	float placeInWave = fmod((time - startTime), wavelength);
	float normalizedPlaceInWave = placeInWave / (float)wavelength;

	if (normalizedPlaceInWave < dutyCycle) {
		return 0;// amplitude;
	}
	else {
		return 0;
	}

}
