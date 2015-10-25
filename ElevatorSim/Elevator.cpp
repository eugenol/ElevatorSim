#include "Elevator.h"
#include "Building.h"


Elevator::Elevator(int floors, Building *_buildingPtr)
{
	numFloors = floors;
	buildingPtr = _buildingPtr;
	ElevatorPanel = new Panel(this);
}


Elevator::~Elevator()
{
	delete ElevatorPanel;
	ElevatorPanel = nullptr;
}

void Elevator::draw()
{
	ElevatorPanel->draw();
	al_draw_filled_rectangle(pos_x, pos_y, pos_x+width, pos_y+height, al_map_rgb(255, 0, 255));
}

void Elevator::update()
{
	
	ElevatorPanel->update();

	//Find current floor
	currentFloor = calcCurrentFloor();
	
	if (currentState == WAITING && !upQueue.empty())
	{
		nextState = MOVING_UP;

	}
	else if (currentState == MOVING_UP)
	{
		pos_y += speed*direction;

		if (pos_y < 0)
			direction = 1;
		if (pos_y + height > 600)
			direction = -1;
	}


	//ElevatorPanel->
	currentState = nextState;
}


void Elevator::addDestination(int destFloor)
{
	upQueue.push_back(destFloor);
}

void Elevator::addCall(int destFloor, int dir)
{
	//upQueue.push_back(destFloor);
}

void  Elevator::checkButtons()
{
	ElevatorPanel->checkPressed();
	std::cout << "Checking Panel" << std::endl;
}

int  Elevator::calcCurrentFloor()
{
	return 0;
}

void Elevator::clearButtons(int floor)
{
	buildingPtr->clearFloorButton(floor);
	ElevatorPanel->clearButton(floor);
}