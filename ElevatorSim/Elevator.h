#ifndef ELEVATOR_H
#define ELEVATOR_H
#include "InputManager.h"
#include <iostream>
#include "allegro5/allegro_primitives.h"
//#include "ElevatorManager.h"
#include "Panel.h"
#include <vector>
class Elevator
{
private:
	int numFloors;
	enum ELEVATOR_STATES{ MOVING_UP, MOVING_DOWN, STOPPED, WAITING };
	Panel *ElevatorPanel;

	int pos_x = 420;
	int pos_y = 0;
	int width = 50;
	int height = 50;
	int speed = 5;
	int direction = 1;
	int currentState;
	int nextState;
	int currentFloor;

	std::vector<int> upQueue;
	std::vector<int> downQueue;

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
	int getState();
	int getCurrentFloor();
	void addDestination(int destFloor);
	void checkButtons();
};
#endif ELEVATOR_H

