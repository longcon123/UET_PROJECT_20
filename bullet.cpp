#include "bullet.h"
void Bullet::update() {
	new_x += sin(angle * DEGTORAD) * 20.0f;
	new_y += -cos(angle * DEGTORAD) * 20.0f;
	/*int maxSpeed = 15;
	double speed = sqrt(new_x * new_x + new_y * new_y);
	if (speed > maxSpeed) {
		new_x *= maxSpeed / speed;
		new_y *= maxSpeed / speed;
	}*/
}