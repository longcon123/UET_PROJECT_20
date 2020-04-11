#pragma once
#ifndef CHARACTER_H
#define CHARACTER_H
#include <iostream>
#include <cstring>
using namespace std;
#include <SDL.h>
#include <SDL_image.h>
class  Character
{
private:
	SDL_Rect dest;
	SDL_Rect src;
	SDL_Texture* tex;
public:
	int x_pos = 30;
	int y_pos = 200;
	int step = 5;
	Character() {}
	SDL_Rect getDest() const { return dest; }
	SDL_Rect getSource() const { return src; }
	void setDest(int x, int y, int w, int h);
	void setSource(int x, int y, int w, int h);
	void setImage(string filename, SDL_Renderer* ren);
	SDL_Texture* getTex() const { return tex; }
};
#endif // !CHARACTER_H
