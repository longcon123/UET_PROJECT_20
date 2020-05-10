#pragma once
#ifndef LSB_H
#define LSB_H
#include "ObjectControl.h"
class Lsb : public ObjectControl
{
public:
	Lsb() { ; }
	~Lsb() { ; }
	int x_gun = 20;
	int y_gun = 155;
	int w_val = 10;
	int h_val = 171;
	bool lsb_on = false;
};
#endif