#include <cmath>
#include <fstream>
#include <iostream>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

using namespace std;

constexpr double two_pi = 6.283185307179586476925286766559;


template <typename Word>
std::ostream& write_word(std::ostream& outs, Word value, unsigned size = sizeof(Word))
{
	for (; size; --size, value >>= 8)
		outs.put(static_cast <char> (value & 0xFF));
	//printf("%d", value);
	return outs;
}



float sawOscillator(int time, float frequency, float amplitude, float phase, int sampleFrequency, int maxAmplitude) {
	//number of samples in a wavelength
	float waveLengthInSamples = (float)sampleFrequency / frequency;
	//position in the full wavelength
	float placeInWave = fmod(float(time) + phase * waveLengthInSamples + waveLengthInSamples / 2, waveLengthInSamples);
	//normalized position (range from 0 to waveLengthInSamples converted to 0 to 1)
	float normalizedPlaceInWave = placeInWave / (float)waveLengthInSamples;
	//finding the displacement at this point in time
	float final = amplitude - (normalizedPlaceInWave * amplitude) + ((float)maxAmplitude / 2 - amplitude / 2);
	return final;
}

float sinOscillator(int time, float frequency, float amplitude, float phase, int sampleFrequency, int maxAmplitude) {
	float waveLength = (float)sampleFrequency / frequency;
	float placeInWave = fmod(time + phase + waveLength / 2, waveLength);
	float normalizedPlaceInWave = placeInWave / (float)waveLength;
	float final = sin(two_pi * (normalizedPlaceInWave)) * amplitude + ((float)maxAmplitude / 2 - amplitude / 2);
	return final;
}

float squareOscillator(int time, float frequency, float amplitude, float phase, int sampleFrequency, int maxAmplitude) {
	float newFrequency = (float)sampleFrequency / frequency;
	float placeInWave = fmod(time + phase, newFrequency);
	float normalizedPlaceInWave = placeInWave / (float)newFrequency;
	float final = round(normalizedPlaceInWave) * amplitude + ((float)maxAmplitude / 2 - amplitude / 2);
	return final;
}
float triangleOscillator(int time, float frequency, float amplitude, float phase, int sampleFrequency, int maxAmplitude) {
	float newFrequency = (float)sampleFrequency / (float)frequency;
	float placeInWave = fmod(time + (phase*newFrequency) + newFrequency / 2, newFrequency);
	float normalizedPlaceInWave = placeInWave / (float)newFrequency;
	float final;
	if (normalizedPlaceInWave < 0.5) {
		final = 2 * normalizedPlaceInWave * amplitude + ((float)maxAmplitude / 2 - amplitude / 2);
	}
	else {
		final = (amplitude - 2 * (normalizedPlaceInWave - 0.5) * amplitude) + (maxAmplitude / 2 - amplitude / 2);
	}
	return final;
}

int noiseGenerator(int amplitude) {
	return rand() % amplitude;;
}

int main()
{
	ofstream f("example.wav", ios::binary);

	// Write the file headers
	f << "RIFF----WAVEfmt ";     // (chunk size to be filled in later)
	write_word(f, 16, 4);  // no extension data
	write_word(f, 1, 2);  // PCM - integer samples
	write_word(f, 2, 2);  // two channels (stereo file)
	write_word(f, 44100, 4);  // samples per second (Hz)
	write_word(f, 176400, 4);  // (Sample Rate * BitsPerSample * Channels) / 8
	write_word(f, 4, 2);  // data block size (size of two integer samples, one for each channel, in bytes)
	write_word(f, 16, 2);  // number of bits per sample (use a multiple of 8)

						   // Write the data chunk header
	size_t data_chunk_pos = f.tellp();
	f << "data----";  // (chunk size to be filled in later)

					  // Write the audio samples
					  // (We'll generate a single C4 note with a sine wave, fading from right to left)

	constexpr double max_amplitude = 32760;  // "volume"

	double hz = 44100;    // samples per second
	double initialFrequencyl = 261.626;  // middle C
	double initialFrequencyr = 261.626;  // middle C
	double seconds = 120;      // time

	int N = hz * seconds;  // total number of samples
	for (int n = 0; n < N; n++)
	{
		double amplitude = 32760;// *sin(n / 10000);// (double)n / N * max_amplitude;
		double frequencyl = initialFrequencyl;
		double frequencyr = initialFrequencyr + (35 * sin(two_pi*((double)n / N)));
		bool switchChannelsEverySample = false;
		bool invertSamples = false;
		int valuel = sinOscillator(n, 200, amplitude / 2, sinOscillator(n, pow(n, 2) / (float)10000000000, 2, 0, hz, 1), hz, max_amplitude);
		int valuer = sinOscillator(n, 200, amplitude / 2, sinOscillator(n, pow(n, 2) / (float)10000000000, 2, 0, hz, 1), hz, max_amplitude);
		//switches the channels every sample
		if ((double)n / 2 == floor((double)n / 2) && switchChannelsEverySample) {
			double test = valuel;
			valuel = valuer;
			valuer = test;
		}
		//invert
		if (invertSamples) {
			valuel = max_amplitude - valuel;
			valuer = max_amplitude - valuer;
		}
		//writing left channel
		write_word(f, valuel, 2);
		//writing right channel
		write_word(f, valuer, 2);
	}

	// (We'll need the final file size to fix the chunk sizes above)
	size_t file_length = f.tellp();

	// Fix the data chunk header to contain the data size
	f.seekp(data_chunk_pos + 4);
	write_word(f, file_length - data_chunk_pos + 8);

	// Fix the file header to contain the proper RIFF chunk size, which is (file size - 8) bytes
	f.seekp(0 + 4);
	write_word(f, file_length - 8, 4);
}