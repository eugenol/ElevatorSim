#ifndef BUTTON_H
#define BUTTON_H
#include "allegro5/allegro_primitives.h"
#include "InputManager.h"
#include <iostream>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
//#include "Elevator.h"


class Button
{
private:
	ALLEGRO_FONT *font;
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
