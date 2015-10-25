#ifndef FLOORBUTTON_H
#define FLOORBUTTON_H

#include <allegro5/allegro_primitives.h>
#include "InputManager.h"
#include <iostream>

class FloorButton
{
private:
	int floorNumber;
	int direction;
	int pos_y;
	int pos_x;
	int height;
	int width;
	bool lightOn = false;

public:
	FloorButton(int floor_num, int dir, int y, int h);
	~FloorButton();
	void update();
	void draw();
	bool checkPressed();
	int getDirection(){ return direction; }
	int getFloorNum(){ return floorNumber; }
	void setLight(int onOff);
};

#endif FLOORBUTTON_H