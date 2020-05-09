
#ifndef OBJECTCONTROL_H
#define OBJECTCONTROL_H
#include <iostream>
#include <cstring>
#include<SDL.h>
#include<SDL_image.h>
#include<SDL_mixer.h>
#include<vector>
using namespace std;
const double PI = 3.14159265;

class ObjectControl {
public:
	ObjectControl();
	~ObjectControl();
	void setImage(string filename, SDL_Renderer* ren);
	void setPos(int x, int y);
	void setRect1(int x, int y, int w, int h);
	void setRect2(int w, int h);
	void setFlip(bool left, bool right);
	void draw(SDL_Renderer* ren);
	void draw_with_angle(SDL_Renderer* ren);
	void setSprite(int x_max, int x_step, bool rv);
	void move(int new_x, int new_y, int speed);
	void getAngle(int x_mouse, int y_mouse);
	void update(int x_pos, int y_pos);
	int get_x() { return rect2.x; }
	int get_y() { return rect2.y; }
	void outScreen();
	//void setGravity()
	bool checkColli(SDL_Rect rectofA, SDL_Rect rectofB);
	//double getGravity() { return gravity; }
	SDL_Rect getRect1() { return rect1; }
	SDL_Rect getRect2() { return rect2; }
	SDL_Texture* getTex() { return tex; };
	SDL_Rect rect1;
	SDL_Rect rect2;
	SDL_Texture* tex;
	SDL_RendererFlip flip_type;
	bool is_alive = true;
	int x_val;
	int y_val;
	double angle;
	double gravity;
	int animSpeed = 3, f = 0, fc = 30;
};
#endif // !OBJECTCONTROL_H
