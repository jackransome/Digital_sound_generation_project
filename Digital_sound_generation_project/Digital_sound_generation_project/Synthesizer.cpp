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
	//get position in the full wavelength in samples
	float placeInWave = fmod(time + phase * waveLengthInSamples, waveLengthInSamples);
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

float Synthesizer::pwmGenerator(int startTime, int time, float dutyCycle, float frequency, float amplitude, float phase, int sampleFrequency, int maxAmplitude)
{
	float wavelength = (float)sampleFrequency / frequency;
	float placeInWave = fmod((time - startTime), wavelength);
	float normalizedPlaceInWave = placeInWave / (float)wavelength;

	if (normalizedPlaceInWave < dutyCycle) {
		return amplitude;
	}
	else {
		return 0;
	}

}
