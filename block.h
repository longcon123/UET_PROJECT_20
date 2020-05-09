#pragma once
#ifndef BLOCK_H
#define BLOCK_H
#include "ObjectControl.h"
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
#endif