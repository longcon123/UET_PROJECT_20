#pragma once
#ifndef SOUND_H
#define SOUND_H
#include "ObjectControl.h"

class Sound: public ObjectControl {
public:
	Sound() { ; }
	~Sound() { ; }
	void update_volumn(bool increase) {
		if (increase) {
			rect2.w += step_volumn;
			rect1.w += step_volumn;
			volumn += step_volumn * 2;
		}
		else {
			rect2.w -= step_volumn;
			rect1.w -= step_volumn;
			volumn -= step_volumn * 2;
		}
		
	}
	int x = 700;
	int y = 20;
	int w_val = 70;
	int h_val = 24;
	int volumn = 100;
	int step_volumn = 10;
};
#endif