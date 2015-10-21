#ifndef ELEVATOR_H
#define ELEVATOR_H
#include "Panel.h"
#include "InputManager.h"
#include <iostream>
//#include "ElevatorManager.h"
class Elevator
{
private:
	int numFloors;
	enum STATE{ MOVING_UP, MOVING_DOWN, STOPPED, WAITING };
	Panel *ElevatorPanel;

	int pos_x = 420;
	int pos_y = 0;
	int width = 50;
	int height = 50;
	int speed = 5;
	int direction = 1;
	int elevatorState;

public:
	Elevator(int floors);
	~Elevator();
	int getFloors() { return numFloors; }
	int getX() { return pos_x; }
	int getY() { return pos_y; }
	void move(int direction) { Elevator::direction = direction; }
	void stop() { direction = 0; }
	void draw();
	void update();
	void checkButtons();
};
#endif ELEVATOR_H

