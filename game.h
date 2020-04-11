#pragma once
#ifndef GAME_H
#define GAME_H
#include <iostream>
#include <cstring>
using namespace std;
#include <SDL.h>
#include <SDL_image.h>
#include "character.h"

class Game {
public:
	Game();
	~Game();
	void loopGame();
	void updateGame() {};
	void inputUser();
	void renderGame();
	void drawObject(Character o);
private:
	SDL_Renderer* render;
	SDL_Window* window;
	bool running;
	int count;
	int timerFPS, lastFrame;
	Character rick;
};
#endif // !GAME_H
