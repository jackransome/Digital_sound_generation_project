#pragma once
class Synthesizer{
public:
	// wave generators generate waveforms in the range of - amplitude / 2 to amplitude / 2
	//sin wave generator
	float sinOscillator(int time, float frequency, float phase, int sampleFrequency, float min, float max);
	//saw wave generator
	float sawOscillator(int time, float frequency, float phase, int sampleFrequency, float min, float max);
	//triangle wave generator
	float triangleOscillator(int time, float frequency, float phase, int sampleFrequency, float min, float max);
	//square wave generator
	float squareOscillator(int time, float frequency, float phase, int sampleFrequency, float min, float max);
	//white noise generator
	float noiseGenerator(float amplitude);
	//dot generator
	float dotGenerator(int time, int startTime, int duration, float amplitude, int maxAmplitude);
	//pwm generator
	float pwmGenerator(int startTime, int time, float dutyCycle, float frequency, float phase, int sampleFrequency, float min, float max);
private:
	int i;
};