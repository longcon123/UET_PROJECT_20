#pragma once
#ifndef HEAD_H
#define HEAD_H
#include "ObjectControl.h"
#include "player.h"
class Head : public ObjectControl
{
public:
	Player player;
	int x_head = player.x_pos;
	int y_head = player.y_pos;
	int w_val = 32;
	int h_val = 26;
};
#endif