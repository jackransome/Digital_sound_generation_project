#pragma once

struct LFO {
	LFO(float* _target, float _startPhase, float _frequency, int _waveForm, float _amplitude) {
		target = _target;
		startPhase = _startPhase;
		frequency = _frequency;
		waveForm = _waveForm;
		amplitude = _amplitude;
	}
	void setTarget(float* _target) {
		target = _target;
	}
	void setPhase(float _phase) {
		startPhase = _phase;
	}
	float * target;
	float startPhase;
	float frequency;
	int waveForm;
	float amplitude;
};