#include "Automater.h"

Automater::Automater(){
	hasFirstPoint = false;
}

Automater::~Automater(){
	deleteMemoryRecursion(start);
}

void Automater::deleteMemoryRecursion(Point* _point) {
	if (_point->next) {
		deleteMemoryRecursion(_point->next);
	}
	delete _point->next;
}


void Automater::addPoint(int _time, float _value){
	if (!hasFirstPoint) {
		start = new Point;
		start->time = _time;
		start->value = _value;
		start->next = nullptr;
		hasFirstPoint = true;
	}
	else {
		if (start->time > _time) {
			Point * newPoint = new Point;
			newPoint->time = _time;
			newPoint->value = _value;
			newPoint->next = start;
			start = newPoint;
		}
		else {
			Point * temp = start;
			while (temp->next && temp->next->time < _time) {
				temp = temp->next;
			}
			Point * newPoint = new Point;
			newPoint->time = _time;
			newPoint->value = _value;
			newPoint->next = temp->next;
			temp->next = newPoint;
		}
	}
}

float Automater::getValueAtTime(int _time)
{
	Point * temp = start;
	while (temp->next && temp->next->time < _time) {
		temp = temp->next;
	}
	if (temp->next) {
		float ratio = ((float)_time - (float)temp->time) / ((float)temp->next->time - (float)temp->time);
		float difference = temp->next->value - temp->value;
		return temp->value + ratio * difference;
	}
	else {
		return temp->value;
	}
}

void Automater::printPoints(){
	Point * temp = start;
	while (temp->next ) {
		printf("time: %d value: %f\n", temp->time, temp->value);
		temp = temp->next;
	}
	printf("time: %d value: %f\n", temp->time, temp->value);
}
