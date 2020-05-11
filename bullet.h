#pragma once
#ifndef BULLET_H
#define BULLET_H
#include "ObjectControl.h"
#include "gun.h"
class Bullet : public ObjectControl
{
public:
	Bullet() { ; }
	~Bullet() { ; }
	Gun gun;
	bool isMove() const { return isShooting; }
	void update();
	int x_val = gun.x_val + 10;
	int y_val = gun.y_val - 5;
	int w_val = 5;
	int h_val = 30;
	int b_w_val = 70;
	int b_h_val = 40;
	bool isShooting;
	int speed = 1;
	double new_x, new_y;
private:
	const double DEGTORAD = 0.017453;
};
#endif