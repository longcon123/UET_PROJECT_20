#include "game.h"
int WIDTH = 1280;
int HEIGHT = 640;
Game::Game() {
	SDL_Init(0);
	SDL_CreateWindowAndRenderer(WIDTH, HEIGHT, 0, &window, &render);
	SDL_SetWindowTitle(window, "DEFEAT THE CORONA VIRUS!!!");
	running = true;
	count = 0;
	rick.setDest(rick.x_pos, rick.y_pos, 285, 370);
	rick.setSource(0, 0, 285, 370);
	rick.setImage("rickrun1.png",render);
	loopGame();
}
Game::~Game() {
	SDL_DestroyRenderer(render);
	SDL_DestroyWindow(window);
	SDL_Quit(); 
}
void Game::loopGame() {
	static int lastTime;
	while (running) {
		lastFrame = SDL_GetTicks();
		if (lastFrame >= (lastTime + 1000)) {
			lastTime = lastFrame;
		}
		renderGame();
		inputUser();
		updateGame();
	}
}
void Game::renderGame() {
	SDL_SetRenderDrawColor(render, 255, 0, 255, 255);
	SDL_Rect rect;
	rect.x = rect.y = 0;
	rect.w = 1280;
	rect.h = 640;
	SDL_RenderFillRect(render, &rect);
	drawObject(rick);
	rick.setDest(rick.x_pos, rick.y_pos, 285, 370);
	int timerFPS = SDL_GetTicks() - lastFrame;
	if (timerFPS < (1000 / 60)) {
		SDL_Delay((1000 / 60) - timerFPS);
	}
	SDL_RenderPresent(render);
}
void Game::drawObject(Character o) {
	SDL_Rect dest = o.getDest();
	SDL_Rect src = o.getSource();
	SDL_RenderCopyEx(render, o.getTex(), &src, &dest, 0, NULL, SDL_FLIP_NONE);
}
void Game::inputUser() {
	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_QUIT) { running = 0; cout << "QUIT GAME!" << endl; }
		if (e.type == SDL_KEYDOWN) {
			if (e.key.keysym.sym == SDLK_ESCAPE) running = false;
			if (e.key.keysym.sym == SDLK_d) rick.x_pos+=rick.step;
		}
		if (e.type == SDL_KEYUP) {
			if (e.key.keysym.sym == SDLK_d) rick.x_pos+=0;
		}
	}
}