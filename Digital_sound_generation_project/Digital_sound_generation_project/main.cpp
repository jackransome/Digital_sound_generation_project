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
	int N = sampleRate * seconds;  // total number of samples

	sequencer.setSampleFrequency(sampleRate);
	
	sequencer.addNote(sampleRate * 10, 75, 0, 0.5, 1, Envelope(sampleRate*0.01, 0, 1, sampleRate*0.01));

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