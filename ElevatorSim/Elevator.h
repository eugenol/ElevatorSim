#ifndef ELEVATOR_H
#define ELEVATOR_H
#include "Panel.h"
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

public:
	Elevator(int floors);
	~Elevator();
	void draw();
	void update();
};
#endif ELEVATOR_H

