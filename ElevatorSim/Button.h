#ifndef BUTTON_H
#define BUTTON_H
#include "allegro5/allegro_primitives.h"
#include "InputManager.h"
#include <iostream>
//#include "Elevator.h"


class Button
{
private:
	int floorNumber;
	int pos_x;
	int pos_y;
	int width = 40;
	int height = 40;
	bool lightOn = false;
	//Elevator *owner;

public:
	Button(int floor_num);
	~Button();
	void update();
	void draw();
	bool isPressed();
	void setLight(int onOff);
	int getFloorNum(){ return floorNumber; }
};

#endif
