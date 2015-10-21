#ifndef BUTTON_H
#define BUTTON_H
#include "allegro5/allegro_primitives.h"
#include "InputManager.h"
#include <iostream>

class Button
{
private:
	int floorNumber;
	int pos_x;
	int pos_y;
	int width = 40;
	int height = 40;
	bool lightOn = false;

public:
	Button(int floor_num);
	~Button();
	void update();
	void draw();
	void isPressed();
};

#endif
