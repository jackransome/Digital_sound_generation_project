#include <cmath>
#include <fstream>
#include <iostream>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

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
	sequencer.addNote(sampleRate * 0.1 * speed, 300, sampleRate * start + sampleRate * 0 * speed, 0.05, 1, -1, sequencer.getEnvelope(0, 0, 1, 0));
	sequencer.addNote(sampleRate * 0.1 * speed, 300, sampleRate * start + sampleRate * 0.4 * speed, 0.05, 1, -1, sequencer.getEnvelope(0, 0, 1, 0));
	sequencer.addNote(sampleRate * 0.1 * speed, 300, sampleRate * start + sampleRate * 0.6 * speed, 0.05, 1, -1, sequencer.getEnvelope(0, 0, 1, 0));
	sequencer.addNote(sampleRate * 0.1 * speed, 300, sampleRate * start + sampleRate * 0.8 * speed, 0.05, 1, -1, sequencer.getEnvelope(0, 0, 1, 0));
}

int main()
{
	//wav properties
	constexpr double max_amplitude = 32760;  // "volume"
	int sampleRate = 44100;    // samples per second
	double seconds = 20;      // time
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

	sequencer.addNote(sampleRate * 8, 300, 0, 0.5, 0, -1, sequencer.getEnvelope(0, 0, 1, 0));
	sequencer.addNote(sampleRate * 8, 300 * 2, 0, 0.1*0.8, 2, -1, sequencer.getEnvelope(0, 0, 1, 0));
	sequencer.addNote(sampleRate * 8, 300 * 4, 0, 0.1*0.6, 2, -1, sequencer.getEnvelope(0, 0, 1, 0));

	//sequencer.addNote(sampleRate * 8, 300 * 4, 0, 0.1*0.4, 2, -1, sequencer.getEnvelope(0, 0, 1, 0));
	//sequencer.addNote(sampleRate * 8, 300 * 8, 0, 0.1*0.4, 2, -1, sequencer.getEnvelope(0, 0, 1, 0));
	//sequencer.addNote(sampleRate * 8, 300 * 16, 0, 0.1*0.2, 2, -1, sequencer.getEnvelope(0, 0, 1, 0));
	//sequencer.addNote(sampleRate * 8, 300 * 32, 0, 0.1*0.5, 2, -1, sequencer.getEnvelope(0, 0, 1, 0));

	/*sequencer.addNote(sampleRate * 8, 300, sampleRate * 8, 0.1, 2, -1, sequencer.getEnvelope(0, 0, 1, 0));
	sequencer.addNote(sampleRate * 8, 300 * 2, sampleRate * 8, 0.1, 2, -1, sequencer.getEnvelope(0, 0, 1, 0));
	sequencer.addNote(sampleRate * 8, 300 * 4, sampleRate * 8, 0.1, 2, -1, sequencer.getEnvelope(0, 0, 1, 0));
	sequencer.addNote(sampleRate * 8, 300 * 8, sampleRate * 8, 0.1, 2, -1, sequencer.getEnvelope(0, 0, 1, 0));
	sequencer.addNote(sampleRate * 8, 300 * 16, sampleRate * 8, 0.1, 2, -1, sequencer.getEnvelope(0, 0, 1, 0));
	sequencer.addNote(sampleRate * 8, 300 * 32, sampleRate * 8, 0.1, 2, -1, sequencer.getEnvelope(0, 0, 1, 0));*/

	/*
	sequencer.addNote(sampleRate * 0.1, 400, sampleRate * 1, 0.1, 2, -1, sequencer.getEnvelope(0.1*sampleRate, 0, 1, 0 * sampleRate));
	sequencer.addNote(sampleRate * 0.1, 400 * 1.3, sampleRate * 1.1, 0.1, 2, -1, sequencer.getEnvelope(0.1*sampleRate, 0, 1, 0 * sampleRate));
	sequencer.addNote(sampleRate * 0.1, 400 * 1.3*1.3, sampleRate * 1.2, 0.1, 2, -1, sequencer.getEnvelope(0.1*sampleRate, 0, 1, 0 * sampleRate));
	sequencer.addNote(sampleRate * 0.1, 400 * 1.3*1.3*1.3, sampleRate * 1.3, 0.1, 2, -1, sequencer.getEnvelope(0.1*sampleRate, 0, 1, 0 * sampleRate));
	sequencer.addNote(sampleRate * 0.1, 400, sampleRate * 1.4, 0.1, 2, -1, sequencer.getEnvelope(0.1*sampleRate, 0, 1, 0 * sampleRate));
	sequencer.addNote(sampleRate * 0.1, 400 * 1.4, sampleRate * 1.5, 0.1, 2, -1, sequencer.getEnvelope(0.1*sampleRate, 0, 1, 0 * sampleRate));
	sequencer.addNote(sampleRate * 0.1, 400 * 1.4 * 1.4, sampleRate * 1.6, 0.1, 2, -1, sequencer.getEnvelope(0.1*sampleRate, 0, 1, 0 * sampleRate));
	sequencer.addNote(sampleRate * 0.1, 400 * 1.4 * 1.4 * 1.4, sampleRate * 1.7, 0.1, 2, -1, sequencer.getEnvelope(0.1*sampleRate, 0, 1, 0 * sampleRate));
	
	//sequencer.addNote(sampleRate * 1, 300, sampleRate * 1, 0.1, 2, -1, sequencer.getEnvelope(0.1*sampleRate, 0, 1, 0 * sampleRate));
	for (int i = 0; i < 70; i++) {
		sequencer.addNote(sampleRate * 0.3, 100 + (float)i/5.0f, sampleRate * (i * 0.3), 0.02, 1, -1, sequencer.getEnvelope(0.1*sampleRate, 0, 1, 0 * sampleRate));
		for (int j = 0; j < 3; j++) {
			sequencer.addNote(sampleRate * 0.1, 400*pow(1.0f+(float)i/50.0f,j), sampleRate * ( i * 0.3 + j * 0.1), 0.1, 2, -1, sequencer.getEnvelope(0.1*sampleRate, 0, 1, 0 * sampleRate));
		}
	}*/
	
	for (int i = 0; i < 10; i++) {
		//sequencer.addNote(sampleRate * 1, 300, sampleRate * 2 * i, 0.1, 2, -1, sequencer.getEnvelope(0.1*sampleRate, 0, 1, 0 * sampleRate));
	}


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

		//int valuel = sinOscillator(n, 200, amplitude / 2, sinOscillator(n, pow(n, 2) / (float)10000000000, 2, 0, hz, 1), hz, max_amplitude);
		//int valuer = sinOscillator(n, 200, amplitude / 2, sinOscillator(n, pow(n, 2) / (float)10000000000, 2, 0, hz, 1), hz, max_amplitude);

		//valuel += sinOscillator(n, 301, max_amplitude / 4, 0, sampleRate, max_amplitude);
		//valuer += sinOscillator(n, 301, max_amplitude / 4, 0, sampleRate, max_amplitude);

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

		//correcting the range from +=ampltude/2 to 0 to amplitude
		//valuel += max_amplitude / 2;
		//valuer += max_amplitude / 2;
		
		if (fmod(n,1000) < 500 ) {
			//valuel = lastl;
			//valuer = lastr;
		}
		if (fmod(n, 2000) > n/150) {
			//valuel = triangleOscillator(n, 120, max_amplitude / 3, 0, sampleRate, max_amplitude);
			//valuer = triangleOscillator(n, 120, max_amplitude / 3, 0, sampleRate, max_amplitude);
		}

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