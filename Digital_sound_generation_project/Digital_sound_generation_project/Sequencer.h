#pragma once
#include <vector>
#include "Note.h"
class Sequencer {
public:
	float run(int time);
private:
	float playNote(Note note, int time);
	float getEnvelopeAmplitude(Note note, int time);
	std::vector<Note> notes;
};