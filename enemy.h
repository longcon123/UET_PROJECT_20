#pragma once
#ifndef ENEMY_H
#define ENEMY_H
#include "ObjectControl.h"
class Enemy : public ObjectControl
{
public:
	Enemy() { ; }
	~Enemy() { ; }
	bool moveL = false;
	bool moveR = true;
	int x_pos = 2400;
	int y_pos = 510;
	int w_val = 60;
	int h_val = 60;
	int x_step = 10;
	int y_step = 0;
	int speed = 1;
	int blood = 60;
	bool isAlive = true;
};
#endif