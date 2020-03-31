#pragma once
class Synthesizer{
public:
	// wave generators generate waveforms in the range of -1 to 1
	//sin wave generator
	float sinOscillator(int _time, float _frequency, float _phase, int _sampleFrequency);
	//saw wave generator
	float sawOscillator(int _time, float _frequency, float _phase, int _sampleFrequency);
	//triangle wave generator
	float triangleOscillator(int _time, float _frequency, float _phase, int _sampleFrequency);
	//square wave generator
	float squareOscillator(int _time, float _frequency, float _phase, int _sampleFrequency);
	//white noise generator
	float noiseGenerator();
	//dot generator
	float dotGenerator(int _time, int _startTime, int _duration, float _amplitude, int _maxAmplitude);
	//pwm generator
	float pwmGenerator(int _startTime, int _time, float _dutyCycle, float _frequency, float _phase, int _sampleFrequency);
private:
	float getNormalizedPlaceInWave(int _sampleFrequency, float _frequency, int _time, float _phase);
	int i;
};