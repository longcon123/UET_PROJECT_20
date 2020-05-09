#pragma once
#pragma once
#ifndef GUN_H
#define GUN_H
#include "ObjectControl.h"
class Gun : public ObjectControl
{
public:
	int x_gun = 350;
	int y_gun = 330;
	int w_val = 25;
	int h_val = 80;
};
#endif