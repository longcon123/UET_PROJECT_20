#include "character.h"

void Character::setDest(int x, int y, int w, int h) {
	dest.x = x;
	dest.y = y;
	dest.w = w;
	dest.h = h;
}
void Character::setSource(int x, int y, int w, int h) {
	src.x = x;
	src.y = y;
	src.w = w;
	src.h = h;
}
void Character::setImage(string fileAnh, SDL_Renderer* ren) {
	SDL_Surface* surf = IMG_Load(fileAnh.c_str());
	tex = SDL_CreateTextureFromSurface(ren, surf);
}