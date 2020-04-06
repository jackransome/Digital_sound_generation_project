#pragma once
#include <stdio.h>
struct Point {
	int time;
	float value;
	Point* next;
};

class Automater{
public:
	void addPoint(int _time, float _value);
	float getValueAtTime(int _time);
	void printPoints();
private:
	Point *start;
	bool hasFirstPoint = false;
};