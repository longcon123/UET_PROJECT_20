#include "map.h"
void Map::loadLevel(SDL_Renderer* render, int lv) {
	int brick_type;

	for (int i = 0; i < block_ref.max_w; i++) {
		for (int j = 0; j < block_ref.max_h; j++) {
			if (lv == 1) brick_type = lv1[i][j];
			else if (lv == 2) brick_type = lv2[i][j];
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
