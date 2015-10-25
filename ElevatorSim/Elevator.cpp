#include "Elevator.h"
#include "Building.h"
#include <algorithm>

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
	al_draw_filled_rectangle(pos_x, pos_y, pos_x+width, pos_y-height, al_map_rgb(255, 0, 255));
}

void Elevator::update()
{
	int nextStop = -1;

	ElevatorPanel->update();

	//currentState == nextState;
	currentFloor = buildingPtr->findFloor(pos_y, pos_y - height);

	//if (currentFloor != -1 && currentFloor!= )
	//{
	//	if
	//}

	if (currentState == WAITING)
	{
		if (liftQueue.empty())
			nextState = WAITING;
		else
			nextState = MOVING_UP;
	}
	else if (currentState == MOVING_UP || currentState == MOVING_DOWN)
	{
		if (currentFloor == -1)
		{
			pos_y += speed*direction;

			nextState = MOVING_UP;

			if (pos_y - height < 0)
			{
				direction = 0;
				pos_y = 2 + height;
				nextState = STOPPED;
			}

			if (pos_y > 600)
			{
				direction = 0;
				pos_y = 598;
				nextState = STOPPED;
			}
		}
		else
		{

		}

		
	}
	else if (currentState == STOPPED)
	{
		if (currentFloor == 0 && nextStop == -1)
		{
			nextState = MOVING_UP;
			direction = UP;
		}
		else if (currentFloor == numFloors-1)
		{
			nextState = MOVING_DOWN;
			direction = DOWN;
		}

	}

	currentState = nextState;
}


void Elevator::addDestination(int destFloor)
{
	liftQueue.push_back(destFloor);
	std::sort(liftQueue.begin(), liftQueue.end());

}

void Elevator::addCall(int destFloor, int dir)
{
	liftQueue.push_back(destFloor);
	std::sort(liftQueue.begin(), liftQueue.end());
	
	//std::vector<int>::iterator last = std::unique(liftQueue.begin(), liftQueue.end());
	//auto is quicker to type
	auto last = std::unique(liftQueue.begin(), liftQueue.end()); // In case of duplicate
	liftQueue.erase(last, liftQueue.end());						// In case of duplicate

	for (const auto& i : liftQueue)
		std::cout << i << " ";
	std::cout << "\n";
}

void  Elevator::checkButtons()
{
	ElevatorPanel->checkPressed();
	std::cout << "Checking Panel" << std::endl;
}

void Elevator::clearButtons(int floor)
{
	buildingPtr->clearFloorButton(floor);
	ElevatorPanel->clearButton(floor);
}