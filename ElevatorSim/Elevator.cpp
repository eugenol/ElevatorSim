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
	
	//std::cout << "Current State: " << currentState << std::endl;
	//std::cout << "Current Floor: " << currentFloor << std::endl;
	//std::cout << "Target Floor: " << targetFloor << std::endl;

	if (currentState == MOVING_TO_DESTINATION)
	{
		if (currentFloor == -1)
		{
			pos_y += speed*direction;

			nextState = MOVING_TO_DESTINATION;

			if (pos_y - height < 0)
			{
				direction = DOWN;
				pos_y = 2 + height;
				nextState = MOVING_TO_DESTINATION;
				targetFloor = numFloors - 1;
			}

			if (pos_y > 600)
			{
				direction = UP;
				pos_y = 598;
				nextState = MOVING_TO_DESTINATION;
				targetFloor =0;
			}
		}
		else
		{
			int tempTarget;
			// check if queue has been updated
			// if there is a value greater than the current value, stop there.
			for (std::vector<int>::iterator iter = liftQueue.begin(); iter != liftQueue.end(); iter++)
			{
				if (*iter >= currentFloor)
				{
					int tempTarget = targetFloor;
					targetFloor = *iter;
					if (tempTarget == targetFloor)
					{
						liftQueue.erase(iter);
					}
					else
					{
						liftQueue.erase(iter);
						liftQueue.push_back(tempTarget);
						std::sort(liftQueue.begin(), liftQueue.end());
					}
					direction = UP;
					nextState = MOVING_TO_DESTINATION;
					break;
				}
			}


			if (currentFloor == targetFloor)
			{
				nextState = STOPPED_AT_DESTINATION;
				direction = 0;
			}
			else
			{
				pos_y += speed*direction;

				nextState = MOVING_TO_DESTINATION;

				if (pos_y - height < 0)
				{
					direction = DOWN;
					pos_y = 2 + height;
					nextState = MOVING_TO_DESTINATION;
					targetFloor = numFloors - 1;
				}

				if (pos_y > 600)
				{
					direction = UP;
					pos_y = 598;
					nextState = MOVING_TO_DESTINATION;
					targetFloor = 0;
				}
			}
		}

	}
	else if (currentState == STOPPED_AT_DESTINATION)
	{
		delayTime++;
		ElevatorPanel->clearButton(currentFloor);
		buildingPtr->clearFloorButton(currentFloor);

		if (delayTime == 120) //if (delayTime == 600)
		{
			delayTime = 0;

			if (currentFloor == 0)
			{
				nextState = WAITING_AT_GROUND;
				targetFloor = 0;
			}
			//find new target
			else if (liftQueue.empty())
			{
				nextState = MOVING_TO_DESTINATION;
				direction = DOWN;
				targetFloor = 0;
			}
			else
			{
				//find place in queue, check if there are higher floors, if so go there,
				// if not go lower
				bool destFlag = false;

				for (std::vector<int>::iterator iter = liftQueue.begin(); iter != liftQueue.end(); iter++)
				{
					if (*iter > currentFloor)
					{
						targetFloor = *iter;
						direction = UP;
						destFlag = true;
						liftQueue.erase(iter);
						nextState = MOVING_TO_DESTINATION;
						break;
					}
				}

				if (!destFlag)
				{
					std::vector<int>::iterator iter = liftQueue.end() - 1;
					targetFloor = *iter;
					liftQueue.erase(iter);
					direction = DOWN;
					nextState = MOVING_TO_DESTINATION;
				}
			}
		}
		else
		{
			nextState = STOPPED_AT_DESTINATION;
		}
	}
	else if (currentState == WAITING_AT_GROUND)
	{
		if (liftQueue.empty())
		{
			nextState = WAITING_AT_GROUND;
		}
		else
		{
			std::vector<int>::iterator iter = liftQueue.begin();
			targetFloor = *iter;
			liftQueue.erase(iter);
			direction = UP;
			nextState = MOVING_TO_DESTINATION;
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

	//for (const auto& i : liftQueue)
	//	std::cout << i << " ";
	//std::cout << "\n";
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