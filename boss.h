#pragma once
#ifndef BOSS_H 
#define BOSS_H
#include "ObjectControl.h"
class Boss : public ObjectControl
{
public:
	Boss() { ; }
	~Boss() { ; }
	bool moveL = false;
	bool moveR = true;
	int x_pos = 2650;
	int y_pos = 370;
	int w_val = 170;
	int h_val = 200;
	int x_step = 0;
	int y_step = 0;
	int speed = 1;
	const int Move = 210;
	const int Idle = 0;
	const int Attack = 170;
	int blood = 500;
};
#endif // !BOSS_H 

