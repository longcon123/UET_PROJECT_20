#define SDL_MAIN_HANDLED
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <cstring>
#include <vector>
#include <cmath>
constexpr auto PI = 3.14159265;
using namespace std;
class Gravity {
public:
	int v0fall = 10;
	int v0jump = 10;
	int vjump = 0;
	int vfall = 0;
	double gjump = 1.8;
	double gfall = 9.8;
	double tjump = 0;
	double tfall = 0;
	bool setGravity(int& y, int ground);
	bool setJump(int& y, int jumps);
};
bool Gravity::setGravity(int& y, int ground)
{
	if (y <= ground) {
		y += vfall;
		tfall += 0.005;
		vfall = v0fall + gfall * tfall;
		v0fall = vfall;
		return false;
	}
	else {
		tfall = 0;
		y = ground;
		return true;
	}
}
bool Gravity::setJump(int& y, int jumps)
{
	if (y >= jumps) {
		y -= vjump;
		tjump += 0.005;
		vjump = v0jump + gjump * tjump;
		v0jump = vjump;
		return false;
	}
	else {
		tjump = 0;
		y = jumps;
		return true;
	}
}
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
	void setSprite();
	void move(int new_x, int new_y, int speed);
	void getAngle(int x_mouse, int y_mouse);
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
	int x_val, y_val;
	double angle;
	double gravity;
	int animSpeed = 5, f = 0, fc = 30;
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
void ObjectControl::setSprite() {
	f += animSpeed;
	if (f > fc) {
		f -= fc;
		rect1.x += 60;
	}
	if (rect1.x >= 250) rect1.x = 60;
}
void ObjectControl::draw(SDL_Renderer* ren) {
	SDL_RenderCopyEx(ren, getTex(), &rect1, &rect2, 0, NULL, flip_type);

}
void ObjectControl::draw_with_angle(SDL_Renderer* ren) {
	SDL_RenderCopyEx(ren, getTex(), &rect1, &rect2, angle, NULL, SDL_FLIP_NONE);
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
	if (rect2.x > 1280 or rect2.x < 0 or rect2.y > 720 or rect2.y < 0)
		is_alive = false;
}
class Audio {
public:
	~Audio();
	void load(const char* filename);
	void play();
private:
	SDL_AudioSpec wavSpec;
	Uint32 wavLength;
	Uint8* wavBuffer;
	SDL_AudioDeviceID deviceId;
};
Audio::~Audio() {
	SDL_CloseAudioDevice(deviceId);
	SDL_FreeWAV(wavBuffer);
}
void Audio::load(const char* filename) {
	SDL_LoadWAV(filename, &wavSpec, &wavBuffer, &wavLength);
	deviceId = SDL_OpenAudioDevice(NULL, 0, &wavSpec, NULL, 0);
}
void Audio::play() {
	SDL_QueueAudio(deviceId, wavBuffer, wavLength);
	SDL_PauseAudioDevice(deviceId, 0);
}
class Player : public ObjectControl
{
public:
	Player();
	~Player();
	void idle();
	void jump(double gravity);
	int get_typeWeapon() { return weapon_on; };
	bool moveL = false;
	bool moveR = true;
	bool isMoving = false;
	bool isJumping = false;
	bool jump_done = false;
	int weapon_on;
	int x_pos = 640;
	int y_pos = 400;
	int w_val = 60;
	int h_val = 70;
	int x_step = 0;
	int y_step = 0;
	int jump_step = 10;
	int speed = 1;
	const string fileMove = "move.png";
	const string fileIdle = "idle.png";
	const string fileJump = "jump.png";
	const string fileMoveGun1 = "moveG1.png";
	const string fileIdleGun1 = "idleG1.png";
	const string fileMoveGun2 = "moveG2.png";
	const string fileIdleGun2 = "idleG2.png";
	const string fileMoveGun3 = "moveG3.png";
	const string fileIdleGun3 = "idleG3.png";
};
Player::Player()
{

}
Player::~Player()
{

}
void Player::idle() {
	isMoving = false;
}
void Player::jump(double gravity) {
	y_val += jump_step * gravity;
}
class Hand : public ObjectControl
{
public:
	Player player;
	int x_val = player.x_pos + 20, y_val = player.y_pos + 15;
	int w_val = 15;
	int h_val = 45;
};
class Bullet : public ObjectControl
{
public:
	Bullet();
	~Bullet();
	Hand hand;
	bool isMove() const { return isShooting; }
	void set_is_move(bool isMove) { isShooting = isMove; }
	void update();
	int x_val = hand.x_val;
	int y_val = hand.y_val;
	int w_val = 50;
	int h_val = 50;
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
	int maxSpeed = 15;
	double speed = sqrt(new_x * new_x + new_y * new_y);
	if (speed > maxSpeed) {
		new_x *= maxSpeed / speed;
		new_y *= maxSpeed / speed;
	}
}

int main() {
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_Window* window;
	SDL_Renderer* render;
	SDL_Event e;
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) == -1)
	{
		printf("%s", Mix_GetError());
	}
	Mix_Chunk* effect = NULL;
	effect = Mix_LoadWAV("laser1.wav");
	SDL_CreateWindowAndRenderer(1280, 720, 0, &window, &render);
	Player player;
	player.setPos(player.x_pos, player.y_pos);
	player.setRect1(0, 0, player.w_val, player.h_val);
	player.setRect2(player.w_val, player.h_val);
	player.setImage("runtest.png", render);
	Hand hand;
	hand.setPos(hand.x_val, hand.y_val);
	hand.setRect1(0, 0, hand.w_val, hand.h_val);
	hand.setRect2(hand.w_val, hand.h_val);
	hand.setImage("hand.png", render);
	vector<Bullet*> bulletVec;
	//bullet.set_is_move(true);
	bool isRunning = true;
	const int fps = 60;
	const int frameDelay = 1000 / fps;
	int frameTime;
	Uint32 frameStart;
	Gravity g;
	while (isRunning) {
		frameStart = SDL_GetTicks();
		while (SDL_PollEvent(&e)) {
			if (e.type == SDL_QUIT) isRunning = false;
			else if (e.type == SDL_MOUSEBUTTONDOWN and bulletVec.size() <= 30) {
				if (e.button.button == SDL_BUTTON_LEFT) {
					Bullet* bullet = new Bullet();
					bullet->setPos(hand.get_x() + 5, hand.get_y());
					bullet->setRect1(bullet->bullet_type1, 0, bullet->w_val, bullet->h_val);
					bullet->setRect2(bullet->w_val, bullet->h_val);
					bullet->setImage("type_A.png", render);
					bullet->isShooting = true;
					bulletVec.push_back(bullet);
				}
			}
			else if (e.type == SDL_KEYDOWN) {
				if (e.key.keysym.sym == SDLK_SPACE) {
					player.isJumping = true;
				}
				if (e.key.keysym.sym == SDLK_a and player.moveL == false) {
					player.x_step = -1;
					player.isMoving = true;
				}
				else if (e.key.keysym.sym == SDLK_a and player.moveL == true) {
					player.x_step = -6;
					player.isMoving = true;
				}
				else if (e.key.keysym.sym == SDLK_d and player.moveR == true) {
					player.x_step = 6;
					player.isMoving = true;
				}
				else if (e.key.keysym.sym == SDLK_d and player.moveR == false) {
					player.x_step = 1;
					player.isMoving = true;
				}
				if (bulletVec.size() >= 30 and e.key.keysym.sym == SDLK_r) {
					bulletVec.clear();
				}
			}
			if (e.type == SDL_KEYUP) {
				if (e.key.keysym.sym == SDLK_a) {
					player.x_step = 0;
					player.isMoving = false;
				}
				else if (e.key.keysym.sym == SDLK_d) {
					player.x_step = 0;
					player.isMoving = false;
				}
				if (e.key.keysym.sym == SDLK_SPACE) {
					//player.isJumping = false;
				}
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
		player.move(player.x_step, player.y_step, player.speed);
		player.setFlip(player.moveL, player.moveR);
		if (player.isMoving)
			player.setSprite();
		player.draw(render);
		hand.getAngle(x, y);
		hand.move(player.x_step, player.y_step, player.speed);
		hand.draw_with_angle(render);
		for (int i = 0; i < bulletVec.size(); ++i) {
			if (bulletVec[i]->isShooting) {
				bulletVec[i]->getAngle(x, y);
				Mix_PlayChannel(-1, effect, 0);
			}
			bulletVec[i]->update();
			bulletVec[i]->move(bulletVec[i]->new_x, bulletVec[i]->new_y, 1);
			bulletVec[i]->setFlip(player.moveL, player.moveR);
			bulletVec[i]->draw(render);
			bulletVec[i]->outScreen();

			//if (bulletVec[i]->is_alive == false and bulletVec.size() >= 1)  bulletVec.erase(bulletVec.begin() + i);
			//bulletVec.back() += 1;
			bulletVec[i]->isShooting = false;
		}
		if (player.isJumping == true and player.jump_done == false)
			if (g.setJump(player.rect2.y, 500) == true) player.jump_done = true;
			else player.jump_done = false;
		else if (player.jump_done == true)
			if (g.setGravity(player.rect2.y, 630) == true) {
				player.isJumping = false;
				player.jump_done = false;
			}
		cout << g.tfall << endl;
		if (player.rect2.y >= 650) player.rect2.y = 650;
		hand.rect2.y = player.rect2.y;
		frameTime = SDL_GetTicks() - frameStart;
		if (frameDelay > frameTime)
			SDL_Delay(frameDelay - frameTime);
		SDL_RenderPresent(render);
		SDL_RenderClear(render);
	}
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}