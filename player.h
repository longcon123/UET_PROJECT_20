#pragma once
#ifndef PLAYER_H
#define PLAYER_H
#include "ObjectControl.h"
class Player : public ObjectControl
{
public:
	Player();
	~Player();
	int get_typeWeapon() { return weapon_on; };
	bool moveL = false;
	bool moveR = true;
	bool isMoving = false;
	bool isJumping = false;
	bool jump_done = false;
	int weapon_on;
	int x_pos = 300;
	int y_pos = 100;
	int w_val = 32;
	int h_val = 84;
	int x_step = 0;
	int y_step = 0;
	int jump_step = 10;
	int speed = 1;
	const int Move = 90;
	const int Idle = 0;
	const int Jump = 0;
	int player_blood = 260;
	bool get_key = false;
};
#endif // !PLAYER_H
