#pragma once
#ifndef HAND_H
#define HAND_H
#include "ObjectControl.h"
#include "player.h"
class Hand : public ObjectControl
{
public:
	Player player;
	int x_hand = player.x_pos+10;
	int y_hand = player.y_pos+40;
	int w_val = 8;
	int h_val = 40;
};
#endif
