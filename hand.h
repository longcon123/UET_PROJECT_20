#pragma once
#ifndef HAND_H
#define HAND_H
#include "ObjectControl.h"
#include "player.h"
class Hand : public ObjectControl
{
public:
	Player player;
	int x_hand = player.x_pos;
	int y_hand = player.y_pos + 50;
	int w_val = 14;
	int h_val = 70;
};
#endif
