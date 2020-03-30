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

Sequencer sequencer;

int main()
{
	//wav properties
	constexpr double max_amplitude = 32760;  // "volume"
	int sampleRate = 44100;    // samples per second
	double seconds = 30;      // time
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
	int N = sampleRate *  seconds;  // total number of samples

	sequencer.setSampleFrequency(sampleRate);
	
	sequencer.addNote(sampleRate * 10, 75, 0, 0.5, 1, Envelope(sampleRate*0.01, 0, 1, sampleRate*0.01));

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
	int modifier = 30;
	int bpm = 130;
	int noteLength = (sampleRate / bpm)*60;

	sequencer.addNote(noteLength, 19 * modifier, noteLength * 0, 0.1,0, 0, -1, sequencer.getEnvelope(sampleRate*0.01, 0, 1, sampleRate*0.01));
	sequencer.addNote(noteLength, 13 * modifier, noteLength * 0, 0.1,0, 0, -1, sequencer.getEnvelope(sampleRate*0.01, 0, 1, sampleRate*0.01));
	//#
	sequencer.addNote(noteLength, 19 * modifier, noteLength * 1, 0.1,0, 0, -1, sequencer.getEnvelope(sampleRate*0.01, 0, 1, sampleRate*0.01));
	sequencer.addNote(noteLength, 13 * modifier, noteLength * 1, 0.1,0, 0, -1, sequencer.getEnvelope(sampleRate*0.01, 0, 1, sampleRate*0.01));
	//#
	sequencer.addNote(noteLength, 18 * modifier, noteLength * 2, 0.1,0, 0, -1, sequencer.getEnvelope(sampleRate*0.01, 0, 1, sampleRate*0.01));
	sequencer.addNote(noteLength, 12 * modifier, noteLength * 2, 0.1,0, 0, -1, sequencer.getEnvelope(sampleRate*0.01, 0, 1, sampleRate*0.01));
	//#
	sequencer.addNote(noteLength, 17 * modifier, noteLength * 3, 0.1,0, 0, -1, sequencer.getEnvelope(sampleRate*0.01, 0, 1, sampleRate*0.01));
	sequencer.addNote(noteLength, 11 * modifier, noteLength * 3, 0.1,0, 0, -1, sequencer.getEnvelope(sampleRate*0.01, 0, 1, sampleRate*0.01));
	//#
	sequencer.addNote(noteLength, 19 * modifier, noteLength * 4, 0.1,0, 0, -1, sequencer.getEnvelope(sampleRate*0.01, 0, 1, sampleRate*0.01));
	sequencer.addNote(noteLength, 12 * modifier, noteLength * 4, 0.1,0, 0, -1, sequencer.getEnvelope(sampleRate*0.01, 0, 1, sampleRate*0.01));
	//#
	sequencer.addNote(noteLength, 18 * modifier, noteLength * 5, 0.1,0, 0, -1, sequencer.getEnvelope(sampleRate*0.01, 0, 1, sampleRate*0.01));
	sequencer.addNote(noteLength, 12 * modifier, noteLength * 5, 0.1,0, 0, -1, sequencer.getEnvelope(sampleRate*0.01, 0, 1, sampleRate*0.01));
	//#
	sequencer.addNote(noteLength, 17 * modifier, noteLength * 6, 0.1,0, 0, -1, sequencer.getEnvelope(sampleRate*0.01, 0, 1, sampleRate*0.01));
	sequencer.addNote(noteLength, 12 * modifier, noteLength * 6, 0.1,0, 0, -1, sequencer.getEnvelope(sampleRate*0.01, 0, 1, sampleRate*0.01));
	//#
	sequencer.addNote(noteLength, 18 * modifier, noteLength * 7, 0.1,0, 0, -1, sequencer.getEnvelope(sampleRate*0.01, 0, 1, sampleRate*0.01));
	sequencer.addNote(noteLength, 12 * modifier, noteLength * 7, 0.1,0, 0, -1, sequencer.getEnvelope(sampleRate*0.01, 0, 1, sampleRate*0.01));
	//#
	sequencer.addNote(noteLength, 18 * modifier, noteLength * 8, 0.1,0, 0, -1, sequencer.getEnvelope(sampleRate*0.01, 0, 1, sampleRate*0.01));
	sequencer.addNote(noteLength, 12 * modifier, noteLength * 8, 0.1,0, 0, -1, sequencer.getEnvelope(sampleRate*0.01, 0, 1, sampleRate*0.01));
	//#
	sequencer.addNote(noteLength, 18 * modifier, noteLength * 9, 0.1,0, 0, -1, sequencer.getEnvelope(sampleRate*0.01, 0, 1, sampleRate*0.01));
	sequencer.addNote(noteLength, 12 * modifier, noteLength * 9, 0.1,0, 0, -1, sequencer.getEnvelope(sampleRate*0.01, 0, 1, sampleRate*0.01));
	//#
	sequencer.addNote(noteLength / 2, 17 * modifier, noteLength * 10, 0.1,0, 0, -1, sequencer.getEnvelope(sampleRate*0.01, 0, 1, sampleRate*0.01));
	sequencer.addNote(noteLength / 2, 16 * modifier, noteLength * 10.5, 0.1,0, 0, -1, sequencer.getEnvelope(sampleRate*0.01, 0, 1, sampleRate*0.01));
	sequencer.addNote(noteLength / 2, 11 * modifier, noteLength * 10, 0.1,0, 0, -1, sequencer.getEnvelope(sampleRate*0.01, 0, 1, sampleRate*0.01));
	sequencer.addNote(noteLength / 2, 12 * modifier, noteLength * 10.5, 0.1,0, 0, -1, sequencer.getEnvelope(sampleRate*0.01, 0, 1, sampleRate*0.01));
	//#
	sequencer.addNote(noteLength, 16 * modifier, noteLength * 11, 0.1,0, 0, -1, sequencer.getEnvelope(sampleRate*0.01, 0, 1, sampleRate*0.01));
	sequencer.addNote(noteLength / 4, 10 * modifier, noteLength * 11, 0.1,0, 0, -1, sequencer.getEnvelope(sampleRate*0.01, 0, 1, sampleRate*0.01));
	sequencer.addNote(noteLength / 4, 11 * modifier, noteLength * 11.25, 0.1,0, 0, -1, sequencer.getEnvelope(sampleRate*0.01, 0, 1, sampleRate*0.01));
	sequencer.addNote(noteLength / 4, 10 * modifier, noteLength * 11.5, 0.1,0, 0, -1, sequencer.getEnvelope(sampleRate*0.01, 0, 1, sampleRate*0.01));
	sequencer.addNote(noteLength / 4, 11 * modifier, noteLength * 11.75, 0.1,0, 0, -1, sequencer.getEnvelope(sampleRate*0.01, 0, 1, sampleRate*0.01));
	//#
	sequencer.addNote(noteLength, 16 * modifier, noteLength * 12, 0.1,0, 0, -1, sequencer.getEnvelope(sampleRate*0.01, 0, 1, sampleRate*0.01));
	sequencer.addNote(noteLength / 4, 11 * modifier, noteLength * 12, 0.1,0, 0, -1, sequencer.getEnvelope(sampleRate*0.01, 0, 1, sampleRate*0.01));
	sequencer.addNote(noteLength / 4, 10 * modifier, noteLength * 12.25, 0.1,0, 0, -1, sequencer.getEnvelope(sampleRate*0.01, 0, 1, sampleRate*0.01));
	sequencer.addNote(noteLength / 4, 11 * modifier, noteLength * 12.5, 0.1,0, 0, -1, sequencer.getEnvelope(sampleRate*0.01, 0, 1, sampleRate*0.01));
	sequencer.addNote(noteLength / 4, 10 * modifier, noteLength * 12.75, 0.1,0, 0, -1, sequencer.getEnvelope(sampleRate*0.01, 0, 1, sampleRate*0.01));
	//#
	sequencer.addNote(noteLength, 16 * modifier, noteLength * 13, 0.1,0, 0, -1, sequencer.getEnvelope(sampleRate*0.01, 0, 1, sampleRate*0.01));
	sequencer.addNote(noteLength, 11 * modifier, noteLength * 13, 0.1,0, 0, -1, sequencer.getEnvelope(sampleRate*0.01, 0, 1, sampleRate*0.01));
	//#
	sequencer.addNote(noteLength, 15 * modifier, noteLength * 14, 0.1,0, 0, -1, sequencer.getEnvelope(sampleRate*0.01, 0, 1, sampleRate*0.01));
	sequencer.addNote(noteLength, 12 * modifier, noteLength * 14, 0.1,0, 0, -1, sequencer.getEnvelope(sampleRate*0.01, 0, 1, sampleRate*0.01));
	//#
	sequencer.addNote(noteLength, 15 * modifier, noteLength * 15, 0.1,0, 0, -1, sequencer.getEnvelope(sampleRate*0.01, 0, 1, sampleRate*0.01));
	sequencer.addNote(noteLength, 11 * modifier, noteLength * 15, 0.1,0, 0, -1, sequencer.getEnvelope(sampleRate*0.01, 0, 1, sampleRate*0.01));
	//#
	sequencer.addNote(noteLength, 15 * modifier, noteLength * 16, 0.1,0, 0, -1, sequencer.getEnvelope(sampleRate*0.01, 0, 1, sampleRate*0.01));
	sequencer.addNote(noteLength, 10 * modifier, noteLength * 16, 0.1,0, 0, -1, sequencer.getEnvelope(sampleRate*0.01, 0, 1, sampleRate*0.01));
	//#
	sequencer.addNote(noteLength, 15 * modifier, noteLength * 17, 0.1,0, 0, -1, sequencer.getEnvelope(sampleRate*0.01, 0, 1, sampleRate*0.01));
	sequencer.addNote(noteLength, 10 * modifier, noteLength * 17, 0.1,0, 0, -1, sequencer.getEnvelope(sampleRate*0.01, 0, 1, sampleRate*0.01));
	//#
	sequencer.addNote(noteLength, 15 * modifier, noteLength * 18, 0.1,0, 0, -1, sequencer.getEnvelope(sampleRate*0.01, 0, 1, sampleRate*0.01));
	sequencer.addNote(noteLength, 10 * modifier, noteLength * 18, 0.1,0, 0, -1, sequencer.getEnvelope(sampleRate*0.01, 0, 1, sampleRate*0.01));
	//#19
	sequencer.addNote(noteLength, 15 * modifier, noteLength * 19, 0.1,0, 0, -1, sequencer.getEnvelope(sampleRate*0.01, 0, 1, sampleRate*0.01));
	sequencer.addNote(noteLength, 10 * modifier, noteLength * 19, 0.1,0, 0, -1, sequencer.getEnvelope(sampleRate*0.01, 0, 1, sampleRate*0.01));
	//#
	sequencer.addNote(noteLength, 14 * modifier, noteLength * 20, 0.1,0, 0, -1, sequencer.getEnvelope(sampleRate*0.01, 0, 1, sampleRate*0.01));
	sequencer.addNote(noteLength, 10 * modifier, noteLength * 20, 0.1,0, 0, -1, sequencer.getEnvelope(sampleRate*0.01, 0, 1, sampleRate*0.01));
	//#
	sequencer.addNote(noteLength, 13 * modifier, noteLength * 21, 0.1,0, 0, -1, sequencer.getEnvelope(sampleRate*0.01, 0, 1, sampleRate*0.01));
	sequencer.addNote(noteLength, 9 * modifier, noteLength * 21, 0.1,0, 0, -1, sequencer.getEnvelope(sampleRate*0.01, 0, 1, sampleRate*0.01));
	//#
	sequencer.addNote(noteLength, 12 * modifier, noteLength * 22, 0.1,0, 0, -1, sequencer.getEnvelope(sampleRate*0.01, 0, 1, sampleRate*0.01));
	sequencer.addNote(noteLength, 10 * modifier, noteLength * 22, 0.1,0, 0, -1, sequencer.getEnvelope(sampleRate*0.01, 0, 1, sampleRate*0.01));
	//#
	sequencer.addNote(noteLength / 2, 11.5 * modifier, noteLength * 23, 0.1,0, 0, -1, sequencer.getEnvelope(sampleRate*0.01, 0, 1, sampleRate*0.01));
	sequencer.addNote(noteLength / 2, 11 * modifier, noteLength * 23.5, 0.1,0, 0, -1, sequencer.getEnvelope(sampleRate*0.01, 0, 1, sampleRate*0.01));
	sequencer.addNote(noteLength / 2, 9.5 * modifier, noteLength * 23, 0.1,0, 0, -1, sequencer.getEnvelope(sampleRate*0.01, 0, 1, sampleRate*0.01));
	sequencer.addNote(noteLength / 2, 9 * modifier, noteLength * 23.5, 0.1,0, 0, -1, sequencer.getEnvelope(sampleRate*0.01, 0, 1, sampleRate*0.01));
	//#24
	sequencer.addNote(noteLength / 2, 10 * modifier, noteLength * 24, 0.1,0, 0, -1, sequencer.getEnvelope(sampleRate*0.01, 0, 1, sampleRate*0.01));
	sequencer.addNote(noteLength / 2, 9 * modifier, noteLength * 24.5, 0.1,0, 0, -1, sequencer.getEnvelope(sampleRate*0.01, 0, 1, sampleRate*0.01));
	sequencer.addNote(noteLength / 2, 8.5 * modifier, noteLength * 24, 0.1,0, 0, -1, sequencer.getEnvelope(sampleRate*0.01, 0, 1, sampleRate*0.01));
	sequencer.addNote(noteLength / 4, 8 * modifier, noteLength * 24.5, 0.1,0, 0, -1, sequencer.getEnvelope(sampleRate*0.01, 0, 1, sampleRate*0.01));
	sequencer.addNote(noteLength / 4, 9.5 * modifier, noteLength * 24.75, 0.1,0, 0, -1, sequencer.getEnvelope(sampleRate*0.01, 0, 1, sampleRate*0.01));
	//#
	sequencer.addNote(noteLength / 2, 9 * modifier, noteLength * 25, 0.1,0, 0, -1, sequencer.getEnvelope(sampleRate*0.01, 0, 1, sampleRate*0.01));
	sequencer.addNote(noteLength / 2, 8.5 * modifier, noteLength * 25.5, 0.1,0, 0, -1, sequencer.getEnvelope(sampleRate*0.01, 0, 1, sampleRate*0.01));
	sequencer.addNote(noteLength / 2, 8 * modifier, noteLength * 25, 0.1,0, 0, -1, sequencer.getEnvelope(sampleRate*0.01, 0, 1, sampleRate*0.01));
	sequencer.addNote(noteLength / 2, 7.5 * modifier, noteLength * 25.5, 0.1,0, 0, -1, sequencer.getEnvelope(sampleRate*0.01, 0, 1, sampleRate*0.01));
	//#26
	sequencer.addNote(noteLength, 8 * modifier, noteLength * 26, 0.1,0, 0, -1, sequencer.getEnvelope(sampleRate*0.01, 0, 1, sampleRate*0.01));
	sequencer.addNote(noteLength, 8 * modifier, noteLength * 26, 0.1,0, 0, -1, sequencer.getEnvelope(sampleRate*0.01, 0, 1, sampleRate*0.01));
	//#
	sequencer.addNote(noteLength, 8 * modifier, noteLength * 27, 0.1,0, 0, -1, sequencer.getEnvelope(sampleRate*0.01, 0, 1, sampleRate*0.01));
	sequencer.addNote(noteLength, 8 * modifier, noteLength * 27, 0.1,0, 0, -1, sequencer.getEnvelope(sampleRate*0.01, 0, 1, sampleRate*0.01));
	//#
	sequencer.addNote(noteLength, 9 * modifier, noteLength * 28, 0.1,0, 0, -1, sequencer.getEnvelope(sampleRate*0.01, 0, 1, sampleRate*0.01));
	sequencer.addNote(noteLength, 9 * modifier, noteLength * 28, 0.1,0, 0, -1, sequencer.getEnvelope(sampleRate*0.01, 0, 1, sampleRate*0.01));
	//#
	sequencer.addNote(noteLength, 11 * modifier, noteLength * 29, 0.1,0, 0, -1, sequencer.getEnvelope(sampleRate*0.01, 0, 1, sampleRate*0.01));
	sequencer.addNote(noteLength, 11 * modifier, noteLength * 29, 0.1,0, 0, -1, sequencer.getEnvelope(sampleRate*0.01, 0, 1, sampleRate*0.01));
	//#
	sequencer.addNote(noteLength, 15 * modifier, noteLength * 30, 0.1,0, 0, -1, sequencer.getEnvelope(sampleRate*0.01, 0, 1, sampleRate*0.01));
	sequencer.addNote(noteLength, 15 * modifier, noteLength * 30, 0.1,0, 0, -1, sequencer.getEnvelope(sampleRate*0.01, 0, 1, sampleRate*0.01));
	//#
	sequencer.addNote(noteLength, 23 * modifier, noteLength * 31, 0.1,0, 0, -1, sequencer.getEnvelope(sampleRate*0.01, 0, 1, sampleRate*0.01));
	sequencer.addNote(noteLength, 23 * modifier, noteLength * 31, 0.1,0, 0, -1, sequencer.getEnvelope(sampleRate*0.01, 0, 1, sampleRate*0.01));
	//#
	sequencer.addNote(noteLength, 39 * modifier, noteLength * 31, 0.1,0, 0, -1, sequencer.getEnvelope(sampleRate*0.01, 0, 1, sampleRate*0.01));
	sequencer.addNote(noteLength, 39 * modifier, noteLength * 31, 0.1,0, 0, -1, sequencer.getEnvelope(sampleRate*0.01, 0, 1, sampleRate*0.01));


	sequencer.addLFO(&sequencer.getLastNote()->volume, 0, 1, 1, 1);

	for (int n = 0; n < N; n++)
	{

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