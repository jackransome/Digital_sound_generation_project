#include "Sequencer.h"

//gets the output a a specific point in time
float Sequencer::run(int time)
{
	int output = 0;
	for (int i = 0; i < notes.size(); i++) {
		//deletes a note if it's already been played
		if (notes[i].getTotalDuration() + notes[i].startTime > time) {
			//notes.erase(notes.begin() + i);
			//i--;
		}
		else {
			//adds the displacement from the note at the current time to the final sequencer output
			output += playNote(notes[i], time);
		}
	}
	return output;
}

float Sequencer::playNote(Note note, int time)
{
	//getting the apmlitude of the envelope at this point in time
	float envelopeAmplitude = getEnvelopeAmplitude(note, time);
	//0: sin, 1: saw, 2: triangle, 3: square, 4: noise
	switch (note.generationType) {
	case 0:
		break;
	case 1:
		break;
	case 2:
		break;
	case 3:
		break;
	case 4:
		break;
	}
	return 0.0f;
}

//getting a value between 0 and 1 to be multiplied by the notes amplitude to implement the envelope
float Sequencer::getEnvelopeAmplitude(Note note, int time)
{
	float envelopeAmplitude;
	//if still in the attack section of the envelope
	if (time > note.startTime && time < note.startTime + note.envelope.attack) {

	}
	//if still in the decay section of the envelope
	else if (time > note.startTime + note.envelope.attack && time < time + note.startTime + note.envelope.attack + note.envelope.decay) {

	}
	//if still in the sustain section of the envelope
	else if (time > note.startTime + note.envelope.attack + note.envelope.decay && time < time + note.duration) {

	}
	//if still in the release section of the envelope
	else if (time > note.startTime + note.duration && time < time + note.startTime + note.envelope.release) {

	}
	return envelopeAmplitude;
}
