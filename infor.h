#pragma once
#ifndef INFOR_H
#define INFOR_H
#include "ObjectControl.h"
class Infor : public ObjectControl {
public:
	Infor() { ; }
	~Infor() { ; }
	int w_val = 370;
	int h_val = 114;
	int x = 0;
	int y = 0;

};
#endif