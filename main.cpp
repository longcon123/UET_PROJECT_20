#define SDL_MAIN_HANDLED
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <cstring>
#include <vector>
#include <cmath>
const int WIDTH = 800;
const int HEIGHT = 600;
const double PI = 3.14159265;
using namespace std;
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
	void setSprite(int x_max, int x_step);
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
void ObjectControl::setSprite(int x_max, int x_step) {
	if (rect1.x >= x_max) rect1.x = 0;
	else {
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
	double player_blood = 260;
};
Player::Player()
{

}
Player::~Player()
{

}

class Enemy : public ObjectControl
{
public:
	Enemy();
	~Enemy();
	bool moveL = false;
	bool moveR = true;
	int x_pos = 2400;
	int y_pos = 510;
	int w_val = 60;
	int h_val = 60;
	int x_step = 10;
	int y_step = 0;
	int speed = 1;
	int blood = 70;
	bool isAlive = true;
};
Enemy::Enemy()
{

}
Enemy::~Enemy()
{

}


class Hand : public ObjectControl
{
public:
	Player player;
	int x_hand = player.x_pos;
	int y_hand = player.y_pos + 50;
	int w_val = 14;
	int h_val = 70;
};

class Head : public ObjectControl
{
public:
	Player player;
	int x_head = player.x_pos;
	int y_head = player.y_pos;
	int w_val = 32;
	int h_val = 26;
};

class Gun : public ObjectControl
{
public:
	Player player;
	int x_gun = player.x_pos;
	int y_gun = player.y_pos;
	int w_val = 25;
	int h_val = 80;
};
class Lsb : public ObjectControl
{
public:
	Player player;
	int x_gun = player.x_pos;
	int y_gun = player.y_pos;
	int w_val = 10;
	int h_val = 300;
	bool lsb_on = false;
};




class Bullet : public ObjectControl
{
public:
	Bullet();
	~Bullet();
	Gun gun;
	bool isMove() const { return isShooting; }
	void set_is_move(bool isMove) { isShooting = isMove; }
	void update();
	int x_val = gun.x_val + 10;
	int y_val = gun.y_val - 5;
	int w_val = 5;
	int h_val = 30;
	int bullet_type1 = 50;
	int bullet_type2 = 100;
	int bullet_type3 = 150;
	bool isShooting;
	int speed = 1;
	double new_x, new_y;
private:
	const double DEGTORAD = 0.017453;
};
Bullet::Bullet()
{
}
Bullet::~Bullet()
{
}
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
class Block : public ObjectControl {
public:
	Block() { ; }
	~Block() { ; }
	int w_val = 40;
	int h_val = 30;
	const string grass = "grass.png";
	const string brick = "brick.png";
	const string water = "water.png";
	const string gai = "gai.png";
	const string door = "door.png";
	int max_w = 20;
	int max_h = 80;
	char block_type;
};

class Infor : public ObjectControl {
public:
	Infor() { ; }
	~Infor() { ; }
	int w_val = 370;
	int h_val = 114;
	int x = 0;
	int y = 0;

};
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

class Map {
public:
	Map() { ; }
	~Map() { ; }
	Block block_ref;
	void loadLevel(SDL_Renderer* render);
	void drawMap(SDL_Renderer* render);
	vector<Block*> blockVec;
private:
	int lv1[20][80]{
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{2,0,0,0,5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{2,0,0,1,1,1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4,0,0,0,0,0,0,0,2,2,2,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{2,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{2,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1,0,0,0,0,0,0,2,0,0,2,0,0,2,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,3,3,0,0,0,2,0,0,2,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,2,0,0,2,0,0,2,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2,2,2,2,2,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2,2,0,0,0,0,0,0,1,2,2,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{2,0,0,0,2,2,2,2,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,2,2,1,2,2,2,2,2,0,0,0,0,0,0,0,0,0,0,0},
		{2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0},
		{2,0,0,0,0,0,0,0,0,0,0,2,2,2,2,2,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0},
		{2,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,1,2,2,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0},
		{2,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0},
		{2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,3,3,3,3,3,1,3,3,3,3,3,1,3,3,3,3,3,3,3,1,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0},
	};
};
void Map::loadLevel(SDL_Renderer* render) {
	int brick_type;

	for (int i = 0; i < block_ref.max_w; i++) {
		for (int j = 0; j < block_ref.max_h; j++) {
			brick_type = lv1[i][j];
			if (brick_type != 0) {
				Block* block = new Block();
				block->rect2.x = j * 40;
				block->rect2.y = i * 30;
				switch (brick_type)
				{
				case 1:
					block->setPos(block->rect2.x, block->rect2.y);
					block->setRect1(0, 0, block->w_val, block->h_val);
					block->setRect2(block->w_val, block->h_val);
					block->setImage(block->grass, render);
					block->block_type = 'g';
					break;
				case 2:
					block->setPos(block->rect2.x, block->rect2.y);
					block->setRect1(0, 0, block->w_val, block->h_val);
					block->setRect2(block->w_val, block->h_val);
					block->setImage(block->brick, render);
					block->block_type = 'b';
					break;
				case 3:
					block->setPos(block->rect2.x, block->rect2.y);
					block->setRect1(0, 0, block->w_val, block->h_val);
					block->setRect2(block->w_val, block->h_val);
					block->setImage(block->water, render);
					block->block_type = 'w';
					break;
				case 4:
					block->setPos(block->rect2.x, block->rect2.y);
					block->setRect1(0, 0, block->w_val, block->h_val);
					block->setRect2(block->w_val, block->h_val);
					block->setImage(block->gai, render);
					block->block_type = 's';
					break;
				case 5:
					block->setPos(block->rect2.x, block->rect2.y);
					block->setRect1(0, 0, block->w_val, block->h_val);
					block->setRect2(block->w_val, block->h_val);
					block->setImage(block->door, render);
					block->block_type = 'd';
					break;
				default:
					break;
				}
				blockVec.push_back(block);
			}
		}
	}
}
void Map::drawMap(SDL_Renderer* render) {
	if (blockVec.size() > 0)
		for (int i = 0; i < blockVec.size(); i++)
			blockVec[i]->draw(render);
}


int main() {
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_Window* window;
	SDL_Renderer* render;
	SDL_Event e;
	SDL_CreateWindowAndRenderer(WIDTH, HEIGHT, 0, &window, &render);
	bool game_start = 0;
	bool isRunning = true;
	ObjectControl obj;
	obj.setPos(0, 0);
	obj.setRect1(0, 0, 900, 600);
	obj.setRect2(900, 600);
	obj.setImage("start.png", render);
	while (isRunning) {
		obj.draw(render);
		int x1, y1;
		SDL_RenderPresent(render);
		SDL_RenderClear(render);
		SDL_GetMouseState(&x1, &y1);
		while (SDL_PollEvent(&e)) {
			if (e.type == SDL_QUIT) isRunning = false;
			if (e.type == SDL_MOUSEBUTTONDOWN) {
				if (e.button.button == SDL_BUTTON_LEFT and 415 < x1 < 500 && 355 < y1 < 385) {
					game_start = 1;
				}
				if (e.button.button == SDL_BUTTON_LEFT and 415 < x1 < 515 && 490 < y1 < 455) {
					isRunning = false;
				}
			}
		}
		if (game_start == 1) {
			Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
			Mix_Chunk* sound_gun = Mix_LoadWAV("laser1.wav");
			Mix_Chunk* sound_jump = Mix_LoadWAV("jump.wav");
			Mix_Chunk* sound_reload = Mix_LoadWAV("reload.wav");
			Infor infor;
			infor.setPos(infor.x, infor.y);
			infor.setRect1(0, 0, infor.w_val, infor.h_val);
			infor.setRect2(infor.w_val, infor.h_val);
			infor.setImage("player_blood.png", render);
			Blood p_blood;
			p_blood.setPos(p_blood.x_p, p_blood.y_p);
			p_blood.setRect1(0, 0, p_blood.w_val_p, p_blood.h_val_p);
			p_blood.setRect2(p_blood.w_val_p, p_blood.h_val_p);
			p_blood.setImage("blood.png", render);
			Enemy enemy;
			enemy.setPos(enemy.x_pos, enemy.y_pos);
			enemy.setRect1(0, 0, enemy.w_val, enemy.h_val);
			enemy.setRect2(enemy.w_val, enemy.h_val);
			enemy.setImage("enemy.png", render);
			Blood e_blood;
			e_blood.setPos(enemy.x_pos - 5, enemy.y_pos - 20);
			e_blood.setRect1(0, 0, enemy.x_pos, enemy.y_pos);
			e_blood.setRect2(e_blood.w_val_e, e_blood.h_val_e);
			e_blood.setImage("enemy_blood.png", render);
			Player player;
			player.setPos(player.x_pos, player.y_pos);
			player.setRect1(0, 0, player.w_val, player.h_val);
			player.setRect2(player.w_val, player.h_val);
			player.setImage("nbdj1.png", render);
			Head head;
			head.setPos(player.x_pos + 13, player.y_pos - 15);
			head.setRect1(0, 0, head.w_val, head.h_val);
			head.setRect2(head.w_val, head.h_val);
			head.setImage("headnew.png", render);
			Hand hand;
			hand.setPos(hand.x_hand, hand.y_hand);
			hand.setRect1(0, 0, hand.w_val, hand.h_val);
			hand.setRect2(hand.w_val, hand.h_val);
			hand.setImage("handnew.png", render);
			/*Lsb gun;
			gun.setPos(gun.x_gun+10, gun.y_gun-100);
			gun.setRect1(0, 0, gun.w_val, gun.h_val);
			gun.setRect2(gun.w_val, gun.h_val);
			gun.setImage("lsbdai.png", render);*/
			Gun gun;
			gun.setPos(gun.x_gun + 10, gun.y_gun);
			gun.setRect1(0, 0, gun.w_val, gun.h_val);
			gun.setRect2(gun.w_val, gun.h_val);
			gun.setImage("gun.png", render);
			vector <Bullet*> bulletVec;
			//bullet.set_is_move(true);
			bool isRunning = true;
			const int fps = 100;
			const int frameDelay = 1000 / fps;
			int frameTime;
			Uint32 frameStart;
			Map map;
			map.loadLevel(render);
			//int temp;
			bool ong = true;
			bool cham_tuong = false;
			double tjump = 0;
			int bang_dan = 30;
			bool cham_t = false;
			bool duoi = false;
			int enemy_run_time = 0;
			while (player.is_alive && game_start) {
				map.drawMap(render);
				frameStart = SDL_GetTicks();
				SDL_SetRenderDrawColor(render, 155, 100, 100, SDL_ALPHA_OPAQUE);
				while (SDL_PollEvent(&e)) {
					if (e.type == SDL_QUIT) isRunning = false;
					if (e.type == SDL_MOUSEBUTTONDOWN) {
						if (e.button.button == SDL_BUTTON_LEFT and bang_dan > 0) {
							Bullet* bullet = new Bullet();
							bullet->setPos(hand.get_x() - 10, hand.get_y() + 5);
							bullet->setRect1(0, 0, bullet->w_val, bullet->h_val);
							bullet->setRect2(bullet->w_val, bullet->h_val);
							bullet->setImage("bullet1.png", render);
							bullet->isShooting = true;
							bulletVec.push_back(bullet);
							//gun.lsb_on = true;
							bang_dan -= 1;
							Mix_PlayChannel(-1, sound_gun, 0);
						}
						else if (e.button.button == SDL_BUTTON_LEFT and bang_dan == 0) {
							Mix_PlayChannel(-1, sound_reload, 0);
						}
					}
					if (e.type == SDL_KEYDOWN) {
						if (e.key.keysym.sym == SDLK_SPACE) {
							if (ong == true) {
								ong = false;
								player.y_step = -5;
								player.isJumping = true;
								Mix_PlayChannel(-1, sound_jump, 0);
								player.rect1.y = 0;
								player.rect1.x = 31;
							}
						}
						if (e.key.keysym.sym == SDLK_a) {
							player.x_step = -3;
							player.isMoving = true;
						}
						if (e.key.keysym.sym == SDLK_d) {
							player.x_step = 3;
							player.isMoving = true;
						}
						if (e.key.keysym.sym == SDLK_r && bang_dan < 30) {
							Mix_PlayChannel(-1, sound_reload, 0);
							bulletVec.clear();
							bang_dan = 30;
						}
					}
					if (e.type == SDL_KEYUP) {
						if (e.key.keysym.sym == SDLK_a) {
							player.x_step = 0;
							player.isMoving = false;
						}
						if (e.key.keysym.sym == SDLK_d) {
							player.x_step = 0;
							player.isMoving = false;
						}
					}
				}
				if (player.rect2.x < 400)
					player.rect2.x += player.x_step;
				if (player.rect2.y >= 600) player.player_blood = 0;
				for (int i = 0; i < map.blockVec.size(); i++) {
					map.blockVec[i]->rect2.x -= player.x_step;
					if (obj.checkColli(player.getRect2(), map.blockVec[i]->getRect2())) {
						if (player.x_step > 0) {
							player.rect2.x = map.blockVec[i]->rect2.x - player.rect2.w; cham_t = true;
						}
						if (player.x_step < 0) {
							player.rect2.x = map.blockVec[i]->rect2.x + map.blockVec[i]->rect2.w; cham_t = true;
						}
					}
				}
				//if (player.x_step == 0) cham_t = false;
				if ((!player.isJumping and !ong) || (!player.isJumping && !cham_tuong)) {
					player.rect1.x = 0;
					player.y_step = 10;
				}
				else {
					tjump += 0.05;

				}
				if (tjump >= 2 || cham_tuong || ong) {
					//player.rect1.y = player.Jump;
					tjump = 0; player.isJumping = false;
				}
				//if (player.y_step == 0) ong = false;
				player.rect2.y += player.y_step;
				for (int i = 0; i < map.blockVec.size(); i++) {
					if (obj.checkColli(player.getRect2(), map.blockVec[i]->getRect2())) {
						if (map.blockVec[i]->block_type == 'w') player.player_blood -= 1;
						else if (map.blockVec[i]->block_type == 's') player.player_blood -= 10;
						if (player.y_step > 0) { player.rect2.y = map.blockVec[i]->rect2.y - player.rect2.h; player.y_step = 0; cham_tuong = false; ong = true; }
						if (player.y_step < 0) { player.rect2.y = map.blockVec[i]->rect2.y + map.blockVec[i]->rect2.h; cham_tuong = true; ong = false; }
					}
				}
				int x, y;
				SDL_GetMouseState(&x, &y);
				if (x >= player.get_x())
				{
					player.moveL = false;
					player.moveR = true;
				}
				else
				{
					player.moveR = false;
					player.moveL = true;
				}
				player.setFlip(player.moveL, player.moveR);
				if (player.isMoving) {
					player.rect1.y = player.Move;
					player.setSprite(60, 31);
				}
				//else player.rect1.y = player.Idle;
				//if (gun.lsb_on) {
					//gun.setSprite();
				//}
				if (enemy.blood > 0) enemy.draw(render);
				enemy.rect2.x -= player.x_step;


				//if (abs(player.rect2.x - enemy.rect2.x) <= 10) duoi = 0;
				//else {
				enemy_run_time++;
				if (enemy_run_time >= 80) {
					enemy.rect2.x -= 3;
					if (enemy_run_time >= 160) enemy_run_time = 0;
				}
				else enemy.rect2.x += 3;
				//}
				p_blood.rect2.w = player.player_blood;
				if (player.player_blood <= 0) { player.is_alive = false; game_start = 1; }
				e_blood.rect2.w = enemy.blood;
				infor.draw(render);
				p_blood.draw(render);
				e_blood.draw(render);
				player.draw(render);
				head.getAngle(x, y);
				head.setFlip(player.moveL, player.moveR);
				head.draw_with_angle(render);
				hand.getAngle(x, y);
				hand.draw_with_angle(render);
				gun.getAngle(x, y);
				gun.setFlip(player.moveL, player.moveR);
				gun.draw_with_angle(render);
				//SDL_RenderDrawLine(render, gun.rect2.x, gun.rect2.y, x, y);
				for (int i = 0; i < bulletVec.size(); ++i) {
					if (bulletVec[i]->isShooting) {
						bulletVec[i]->getAngle(x, y);
					}
					bulletVec[i]->update();
					bulletVec[i]->move(bulletVec[i]->new_x, bulletVec[i]->new_y, 1);
					bulletVec[i]->setFlip(player.moveL, player.moveR);
					bulletVec[i]->draw_with_angle(render);
					bulletVec[i]->outScreen();
					if (obj.checkColli(enemy.getRect2(), bulletVec[i]->getRect2())) enemy.blood -= 1;
					bulletVec[i]->isShooting = false;
				}
				if (player.player_blood <= 0) {
					player.player_blood;
					player.is_alive = false;
					game_start = 0;
				}
				e_blood.update(enemy.rect2.x - 5, enemy.rect2.y - 20);
				gun.update(player.rect2.x, player.rect2.y - 20);
				hand.update(player.rect2.x, player.rect2.y - 10);
				head.update(player.rect2.x, player.rect2.y - 20);
				//cout << player.player_blood << endl;
				frameTime = SDL_GetTicks() - frameStart;
				if (frameDelay > frameTime)
					SDL_Delay(frameDelay - frameTime);
				SDL_RenderPresent(render);
				SDL_RenderClear(render);
			}

		}
	}
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}
