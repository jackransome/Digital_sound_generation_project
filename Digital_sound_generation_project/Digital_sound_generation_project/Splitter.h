#pragma once
#include <vector>

struct Splitter {
	void set(float value) {
		for (int i = 0; i < targets.size(); i++) {
			*targets[i] = value;
		}
	}
	void addTarget(float * _target) {
		targets.push_back(_target);
	}
	void clearTargets() {
		targets.clear();
	}
	std::vector<float*> targets;
};