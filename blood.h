#pragma once
#ifndef BLOOD_H
#define BLOOD_H
#include "ObjectControl.h"
class Blood : public ObjectControl {
public:
	Blood() { ; }
	~Blood() { ; }
	int w_val_p = 270;
	int h_val_p = 21;
	const int x_p = 98;
	const int y_p = 32;
	int w_val_e = 70;
	int h_val_e = 10;

};
#endif // !BLOOD_H