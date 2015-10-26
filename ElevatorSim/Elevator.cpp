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
	if (doorsOpen)
	{
		al_draw_filled_rectangle(pos_x, pos_y, pos_x + width, pos_y - height, al_map_rgb(255, 255, 255));
		al_draw_filled_rectangle(pos_x-15, pos_y, pos_x-15 + width/2, pos_y - height, al_map_rgb(255, 0, 255));
		al_draw_filled_rectangle(pos_x + 15 + width / 2, pos_y, pos_x + 15 + width , pos_y - height, al_map_rgb(255, 0, 255));
	}
	else
		al_draw_filled_rectangle(pos_x, pos_y, pos_x + width, pos_y - height, al_map_rgb(255, 0, 255));
}

void Elevator::update()
{
	//int nextStop = -1;

	ElevatorPanel->update();

	//currentState == nextState;
	currentFloor = buildingPtr->findFloor(pos_y, pos_y - height);
	
	//std::cout << "Current State: " << currentState << std::endl;
	//std::cout << "Current Floor: " << currentFloor << std::endl;
	//std::cout << "Target Floor: " << targetFloor << std::endl;

	if (currentState == MOVING_UP || currentState == MOVING_DOWN)
	{
		if (currentFloor == -1)
		{
			pos_y += speed*direction;

			nextState = currentState;

			if (pos_y - height < 0)
			{
				direction = DOWN;
				pos_y = 2 + height;
				nextState = MOVING_DOWN;
				targetFloor = numFloors - 1;
			}

			if (pos_y > 600)
			{
				direction = UP;
				pos_y = 598;
				nextState = MOVING_UP;
				targetFloor = 0;
			}
		}
		else
		{
			//Divide liftQueue Between upQueue & downQueue
			for (std::vector<int>::iterator iter = liftQueue.begin(); iter != liftQueue.end(); iter++)
			{
				if (*iter > currentFloor)
				{
					upQueue.push_back(*iter);
				}
				else if (*iter < currentFloor)
				{
					downQueue.push_back(*iter);
				}
				//std::sort(upQueue.begin(), upQueue.end());		// ascending
				//std::sort(downQueue.rbegin(), downQueue.rend()); // reverse sort ... descending
				upQueue.sort();
				downQueue.sort();
				downQueue.reverse();
			}
			liftQueue.clear();


			// check if queue has been updated
			// if there is a value greater than the current value, stop there.

			if (currentState == MOVING_UP)
			{
				if (!upQueue.empty()) //up list not empty, keep moving up
				{
					std::list <int>::iterator iter = upQueue.begin();
					targetFloor = *iter;
					//upQueue.pop_front();
					direction = UP;
					nextState = currentState;
				}
				else
				{
					if (!downQueue.empty()) //up list not empty, keep moving up
					{
						std::list <int>::iterator iter = downQueue.begin();
						targetFloor = *iter;
						//downQueue.pop_front();
						direction = DOWN;
						nextState = MOVING_DOWN;
					}
					else
					{
						//both Queues empty
						//go to ground floor
						targetFloor = 0;
						direction = DOWN;
						nextState = MOVING_DOWN;
					}
				}

			}
			else if (currentState == MOVING_DOWN)
			{
				// if moving down && nothing below, move up
				// if moving down && something below, move down
				if (!downQueue.empty()) //down list not empty, keep moving down
				{
					std::list <int>::iterator iter = downQueue.begin();
					targetFloor = *iter;
					//downQueue.pop_front();
					direction = DOWN;
					nextState = currentState;
				}
				else
				{
					if (!upQueue.empty()) //up list not empty, keep moving up
					{
						std::list <int>::iterator iter = upQueue.begin();
						targetFloor = *iter;
						//upQueue.pop_front();
						direction = UP;
						nextState = MOVING_UP;
					}
					else
					{
						//both Queues empty
						//go to ground floor
						targetFloor = 0;
						direction = DOWN;
						nextState = MOVING_DOWN;
					}
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

				nextState = currentState;

				if (pos_y - height < 0)
				{
					direction = DOWN;
					pos_y = 2 + height;
					nextState = MOVING_DOWN;
					targetFloor = numFloors - 1;
				}

				if (pos_y > 600)
				{
					direction = UP;
					pos_y = 598;
					nextState = MOVING_UP;
					targetFloor = 0;
				}
			}
		}

	}
	else if (currentState == STOPPED_AT_DESTINATION)
	{
		if (delayTime == 0)
		{
			tempState = prevState;
			doorsOpen = true;
		}

		delayTime++;
		ElevatorPanel->clearButton(currentFloor);
		buildingPtr->clearFloorButton(currentFloor);

		//std::vector<int>::iterator iter = liftQueue.begin();
		// remove current floor in case it was pressed again
		//while (iter != liftQueue.end() && *iter == currentFloor)
		//{
		//	iter = liftQueue.erase(iter);
		//	//iter--;
		//}

		for (std::vector<int>::iterator iter = liftQueue.begin(); iter != liftQueue.end(); iter++)
		{
			if (*iter > currentFloor)
			{
				upQueue.push_back(*iter);
			}
			else if (*iter < currentFloor)
			{
				downQueue.push_back(*iter);
			}
			//std::sort(upQueue.begin(), upQueue.end());		// ascending
			//std::sort(downQueue.rbegin(), downQueue.rend()); // reverse sort ... descending
			upQueue.sort();
			downQueue.sort();
			downQueue.reverse();
		}
		liftQueue.clear();

		if (delayTime == 120) //if (delayTime == 600)
		{
			delayTime = 0;
			doorsOpen = false;
			prevState = tempState;

			if (currentFloor == 0)
			{
				nextState = WAITING_AT_GROUND;
				targetFloor = 0;
				//if (prevState ==)
			}
			//find new target
			else if (upQueue.empty() && downQueue.empty())
			{
				nextState = MOVING_DOWN;
				direction = DOWN;
				targetFloor = 0;
			}
			else
			{
				//find place in queue, check if there are higher floors, if so go there,
				// if not go lower

				if (prevState == MOVING_UP)
				{
					if (!upQueue.empty()) //up list not empty, keep moving up
					{
						upQueue.pop_front();
						if (!upQueue.empty())
						{
							std::list <int>::iterator iter = upQueue.begin();
							targetFloor = *iter;
							direction = UP;
							nextState = MOVING_UP;
						}
						else if (!downQueue.empty()) //up list not empty, keep moving up
						{
							std::list <int>::iterator iter = downQueue.begin();
							targetFloor = *iter;
							direction = DOWN;
							nextState = MOVING_DOWN;
						}
						else
						{
							//both Queues empty
							//go to ground floor
							targetFloor = 0;
							direction = DOWN;
							nextState = MOVING_DOWN;
						}
					}
					else
					{
						if (!downQueue.empty()) //up list not empty, keep moving up
						{
							std::list <int>::iterator iter = downQueue.begin();
							targetFloor = *iter;
							direction = DOWN;
							nextState = MOVING_DOWN;
						}
						else
						{
							//both Queues empty
							//go to ground floor
							targetFloor = 0;
							direction = DOWN;
							nextState = MOVING_DOWN;
						}
					}
				}
				else if (prevState == MOVING_DOWN)
				{
					if (!downQueue.empty()) //down list not empty, keep moving down
					{
						downQueue.pop_front();
						if (!downQueue.empty())
						{
							std::list <int>::iterator iter = downQueue.begin();
							targetFloor = *iter;
							direction = DOWN;
							nextState = MOVING_DOWN;
						}
						else if (!upQueue.empty()) //up list not empty, keep moving up
						{
							std::list <int>::iterator iter = upQueue.begin();
							targetFloor = *iter;
							direction = UP;
							nextState = MOVING_UP;
						}
						else
						{
							//both Queues empty
							//go to ground floor
							targetFloor = 0;
							direction = DOWN;
							nextState = MOVING_DOWN;
						}

					}
					else
					{
						if (!upQueue.empty()) //up list not empty, keep moving up
						{
							std::list <int>::iterator iter = upQueue.begin();
							targetFloor = *iter;
							direction = UP;
							nextState = MOVING_UP;
						}
						else
						{
							//both Queues empty
							//go to ground floor
							targetFloor = 0;
							direction = DOWN;
							nextState = MOVING_DOWN;
						}
					}

				}
				//std::vector<int>::iterator iter = liftQueue.begin();
				//while ( iter != liftQueue.end())
				//{
				//	// remove current floor in case it was pressed again
				//	while (iter != liftQueue.end() && *iter == currentFloor)
				//	{
				//		iter = liftQueue.erase(iter);
				//		//iter--;
				//	}

				//	if (iter != liftQueue.end() && *iter > currentFloor)
				//	{
				//		targetFloor = *iter;
				//		direction = UP;
				//		destFlag = true;
				//		liftQueue.erase(iter);
				//		nextState = MOVING_TO_DESTINATION;
				//		break;
				//	}
				//	else
				//	{
				//		nextState = MOVING_TO_DESTINATION;
				//		direction = DOWN;
				//		targetFloor = 0;
				//		destFlag = true;
				//		break;
				//	}
				//	iter++;
				//}

			}
		}
		else
		{
			nextState = STOPPED_AT_DESTINATION;
		}
	}
	else if (currentState == WAITING_AT_GROUND)
	{

		for (std::vector<int>::iterator iter = liftQueue.begin(); iter != liftQueue.end(); iter++)
		{
			upQueue.push_back(*iter);
			upQueue.sort();
		}
		liftQueue.clear();

		if (upQueue.empty())
		{
			nextState = WAITING_AT_GROUND;
		}
		else
		{
			std::list<int>::iterator iter = upQueue.begin();
			targetFloor = *iter;
			direction = UP;
			nextState = MOVING_UP;
		}
	}

	prevState = currentState;
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

int Elevator::getCurrentFloor( )
{
	return currentFloor;
}