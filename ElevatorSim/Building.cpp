#include "Building.h"


Building::Building(int num_floors)
{
	lift = new Elevator(num_floors, this);

	int height = 600 / num_floors;

	numFloors = num_floors;

	for (int i = 0; i < num_floors; i++)
	{
		Floors.push_back(new Floor(i, num_floors, 600-i*height, height, lift));
	}

}


Building::~Building()
{

}


void Building::update()
{
	lift->update();

	for (std::vector<Floor*>::iterator iter = Floors.begin(); iter != Floors.end(); iter++)
	{
		(*iter)->update();
	}
}

void Building::draw()
{
	lift->draw();

	for (std::vector<Floor*>::iterator iter = Floors.begin(); iter != Floors.end(); iter++)
	{
		(*iter)->draw();
	}
}

void Building::checkPressed()
{
	if (InputManager::getInstance().getMouseX() < 400)
	{
		lift->checkButtons();
	}
	else
	{
		for (std::vector<Floor*>::iterator iter = Floors.begin(); iter != Floors.end(); iter++)
		{
			(*iter)->checkPressed();
		}
	}

}

void Building::clearFloorButton(int floor)
{
	Floors[floor]->clearButton();
}

int Building::findFloor(int y1, int y2)
{
	int validFloor = -1;

	for (std::vector<Floor*>::iterator iter = Floors.begin(); iter != Floors.end(); iter++)
	{
		validFloor = (*iter)->onFloor(y1,y2);
		if (validFloor != -1)
			return validFloor;
	}
	return validFloor;
}