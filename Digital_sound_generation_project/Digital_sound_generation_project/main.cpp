#include <cmath>
#include <fstream>
#include <iostream>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <random>
#include <math.h>
#include <vector>

#include "Sequencer.h"
constexpr double two_pi = 6.283185307179586476925286766559;

//writes "words" to the file
template <typename Word>
std::ostream& write_word(std::ostream& outs, Word value, unsigned size = sizeof(Word))
{
	for (; size; --size, value >>= 8)
		outs.put(static_cast <char> (value & 0xFF));
	return outs;
}

//wave generators generate waveforms in the range of -amplitude/2 to amplitude/2
/*
//a test, cycling through all forms of sound generaton
int runTests(int time, int max_amplitude, int sampleRate) {
	int x = fmod(time / 8000, 8);
	int value;
	switch (x) {
	case 0:
		for (int i = 0; i < 50; i +=1)
		value = sinOscillator(time, 10+i, max_amplitude/2, 0, sampleRate, max_amplitude);
		break;
	case 1:
		value = sawOscillator(time, 300, max_amplitude / 4, 0, sampleRate, max_amplitude);
		break;
	case 2:
		value = squareOscillator(time, 300, max_amplitude / 4, 0, sampleRate, max_amplitude);
		break;
	case 3:
		value = sawOscillator(time, 300, max_amplitude / 4, 0, sampleRate, max_amplitude);
		break;
	case 4:
		value = noiseGenerator(max_amplitude / 4);
		break;
	case 5:
		value = sawOscillator(time, 300, max_amplitude / 4, 0, sampleRate, max_amplitude);
		break;
	case 6:
		value = squareOscillator(time, 300, max_amplitude / 4, 0, sampleRate, max_amplitude);
		break;
	case 7:
		value = sawOscillator(time, 300, max_amplitude / 4, 0, sampleRate, max_amplitude);
		break;
	default:
		value = noiseGenerator(max_amplitude / 2);
		break;
	}
	return value;
}
*/
Sequencer sequencer;

void test(float speed, float start, float sampleRate) {
	//sequencer.addNote(sampleRate * 0.1 * speed, 300, sampleRate * start + sampleRate * 0 * speed, 0.05, 1, -1, sequencer.getEnvelope(0, 0, 1, 0));
	//sequencer.addNote(sampleRate * 0.1 * speed, 300, sampleRate * start + sampleRate * 0.4 * speed, 0.05, 1, -1, sequencer.getEnvelope(0, 0, 1, 0));
	//sequencer.addNote(sampleRate * 0.1 * speed, 300, sampleRate * start + sampleRate * 0.6 * speed, 0.05, 1, -1, sequencer.getEnvelope(0, 0, 1, 0));
	//sequencer.addNote(sampleRate * 0.1 * speed, 300, sampleRate * start + sampleRate * 0.8 * speed, 0.05, 1, -1, sequencer.getEnvelope(0, 0, 1, 0));
}

int main()
{
	//wav properties
	constexpr double max_amplitude = 32760;  // "volume"
	int sampleRate = 44100;    // samples per second
	double seconds = 60;      // time
	double bitsPerSample = 32;

	//opening the file
	std::ofstream f("example.wav", std::ios::binary);

	// Write the file headers
	f << "RIFF----WAVEfmt ";     // (chunk size to be filled in later)
	write_word(f, 16, 4);  // no extension data
	write_word(f, 1, 2);  // PCM - integer samples
	write_word(f, 2, 2);  // two channels (stereo file)
	write_word(f, sampleRate, 4);  // samples per second (Hz)
	write_word(f, (int)((sampleRate*bitsPerSample * 2)/8), 4);  // (Sample Rate * BitsPerSample * Channels) / 8
	write_word(f, 4, 2);  // data block size (size of two integer samples, one for each channel, in bytes)
	write_word(f, 16, 2);  // number of bits per sample (use a multiple of 8)
	// Write the data chunk header
	size_t data_chunk_pos = f.tellp();
	f << "data----";  // (chunk size to be filled in later)
	int lastl = 0, lastr = 0;
	int N = sampleRate * seconds;  // total number of samples

	sequencer.setSampleFrequency(sampleRate);

	std::random_device dev;
	std::mt19937 rng(dev());
	std::uniform_int_distribution<std::mt19937::result_type> dist100(1, 30); // distribution in range [1, 6]

	//std::cout << dist6(rng) << std::endl;

	//sequencer.addNote(sampleRate * 10, 500, 0, 0.1, 0, -1, sequencer.getEnvelope(0, 0, 1, 0));
	float newFreq;
	float secondFreq;
	float currentTime = 0;
	int j = 0;
	int amount = 0;
	std::vector<int> newFreqs;

	float center = 200 * pow(1 / 0.9438746262083767, floor(dist100(rng) / 5));

	// sequencer.addNote(sampleRate * 16, 500, 0, 0.25, 0, 6, -1, sequencer.getEnvelope(sampleRate*0.05, 0, 1, sampleRate*0.05));
	sequencer.addNote(sampleRate * 16, 75, 0, 0.5, 0, 1, -1, sequencer.getEnvelope(sampleRate*0.01, 0, 1, sampleRate*0.01));




	for (int n = 0; n < N; n++)
	{
		//sequencer.run(n, sampleRate, max_amplitude);

		//---options---//
		bool switchChannelsEverySample = false;
		bool invertSamples = false;
		bool willRunTests = true;
		//-------------//

		//generating the sound
		int valuel = sequencer.run(n, sampleRate, max_amplitude);
		int valuer = sequencer.run(n, sampleRate, max_amplitude);

		//-----optional-manipulation----//
		//runs test looping through all forms of sound generation
		if (willRunTests) {
			//valuel += runTests(n, max_amplitude, sampleRate);
			//valuer += runTests(n, max_amplitude, sampleRate);
		}
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
		//------------------------------//

		//writing left and right channels
		write_word(f, valuel, 2);
		write_word(f, valuer, 2);
		
		lastl = valuel;
		lastr = valuer;
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