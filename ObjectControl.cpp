#include "ObjectControl.h"

ObjectControl::ObjectControl() {

}
ObjectControl::~ObjectControl() {
	SDL_DestroyTexture(tex);
}
void ObjectControl::move(int new_x, int new_y, int speed) {
	rect2.x += new_x * speed;
	rect2.y += new_y * speed;
}
void ObjectControl::setPos(int _x, int _y) {
	x_val = _x;
	y_val = _y;
}
void ObjectControl::update(int x_pos, int y_pos) {
	rect2.x = x_pos;
	rect2.y = y_pos;
}
void ObjectControl::setFlip(bool left, bool right) {
	if (left == true && right == false) flip_type = SDL_FLIP_HORIZONTAL;
	else if (left == false && right == true) flip_type = SDL_FLIP_NONE;
}
void ObjectControl::setImage(string filename, SDL_Renderer* ren) {
	SDL_Surface* sur = IMG_Load(filename.c_str());
	tex = SDL_CreateTextureFromSurface(ren, sur);
}
void ObjectControl::setRect1(int x, int y, int w, int h) {
	rect1.x = x;
	rect1.y = y;
	rect1.w = w;
	rect1.h = h;
}
void ObjectControl::setRect2(int w, int h) {
	rect2.x = x_val;
	rect2.y = y_val;
	rect2.w = w;
	rect2.h = h;
}
void ObjectControl::setSprite(int x_max, int x_step, bool rv) {
	if (rect1.x >= x_max) {
		if (rv) rect1.x = 0;
		else rect1.x = x_max;
	}
	else
	{
		f += animSpeed;
		if (f > fc) {
			f -= fc;
			rect1.x += x_step;
		}
	}
}
void ObjectControl::draw(SDL_Renderer* ren) {
	SDL_RenderCopyEx(ren, getTex(), &rect1, &rect2, 0, NULL, flip_type);

}
void ObjectControl::draw_with_angle(SDL_Renderer* ren) {
	SDL_RenderCopyEx(ren, getTex(), &rect1, &rect2, angle, NULL, flip_type);
}
void ObjectControl::getAngle(int x_mouse, int y_mouse) {
	int xc = rect2.x + rect2.w / 2;
	double param = (y_mouse - rect2.y) / sqrt((x_mouse - xc) * (x_mouse - xc) + (y_mouse - rect2.y) * (y_mouse - rect2.y));
	double angleHand = acos(param) * 180.0 / PI;
	if (rect2.x > x_mouse) angleHand += 180;
	else angleHand = 180 - angleHand;
	angle = angleHand;
}
bool ObjectControl::checkColli(SDL_Rect rectS2ofA, SDL_Rect rectS2ofB) {
	if (rectS2ofA.x + rectS2ofA.w > rectS2ofB.x &&
		rectS2ofB.x + rectS2ofB.w > rectS2ofA.x &&
		rectS2ofA.y + rectS2ofA.h > rectS2ofB.y &&
		rectS2ofB.h + rectS2ofB.y > rectS2ofA.y)
		return true;
	return false;
}
void ObjectControl::outScreen() {
	if (rect2.x > 1280 or rect2.x < 0 or rect2.y > 1020 or rect2.y < 0)
		is_alive = false;
}