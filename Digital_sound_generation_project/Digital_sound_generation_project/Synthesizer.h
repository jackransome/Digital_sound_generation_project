#pragma once
class Synthesizer{
public:
	// wave generators generate waveforms in the range of - amplitude / 2 to amplitude / 2
	//sin wave generator
	float sinOscillator(int time, float frequency, float amplitude, float phase, int sampleFrequency, int maxAmplitude);
	//saw wave generator
	float sawOscillator(int time, float frequency, float amplitude, float phase, int sampleFrequency, int maxAmplitude);
	//triangle wave generator
	float triangleOscillator(int time, float frequency, float amplitude, float phase, int sampleFrequency, int maxAmplitude);
	//square wave generator
	float squareOscillator(int time, float frequency, float amplitude, float phase, int sampleFrequency, int maxAmplitude);
	//white noise generator
	int noiseGenerator(int amplitude);
private:
	int i;
};