#ifndef ELEVATOR_H
#define ELEVATOR_H
#include "InputManager.h"
#include <iostream>
#include "allegro5/allegro_primitives.h"
//#include "ElevatorManager.h"
#include "Panel.h"
#include <vector>

class Building;

class Elevator
{
private:
	int numFloors;
	enum ELEVATOR_STATES{ MOVING_UP, MOVING_DOWN, STOPPED, WAITING };
	enum DIRECTION{ UP = -1, DOWN = 1 };
	Panel *ElevatorPanel;

	int pos_x = 420;
	int pos_y = 598;
	int width = 50;
	int height = 50;
	int speed = 3;
	int direction = UP;
	int currentState = WAITING;
	int nextState = WAITING;
	int currentFloor = 0;
	int targetFloor = 0;

	std::vector<int> callQueue;
	//std::vector<int> destQueue;
	std::vector<int> liftQueue;

	Building *buildingPtr;

public:
	//Elevator(int floors);
	Elevator(int floors, Building *_buildingPtr);
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
	void addCall(int destFloor, int dir);
	void checkButtons();
	void clearButtons(int floor);
};
#endif ELEVATOR_H

