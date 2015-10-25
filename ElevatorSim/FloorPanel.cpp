#include "FloorPanel.h"
#include "Elevator.h"

FloorPanel::FloorPanel(int floor_num, int max_floors, int y, int h, Elevator *_lift)
{
	numFloor = floor_num;
	maxFloors = max_floors;
	pos_y = y - 2;
	height = h - 4;
	pos_x = 600;
	width = 200;
	lift = _lift;

	if ((numFloor == 0) || (numFloor == max_floors-1))
	{
		if (numFloor == 0)
			Buttons.push_back(new FloorButton(numFloor, 1,pos_y,height)); // up
		else
			Buttons.push_back(new FloorButton(numFloor, 0, pos_y, height)); //down
	}
	else
	{
		for (int i = 0; i < 2; i++)
		{
			Buttons.push_back(new FloorButton(numFloor, i, pos_y, height));
		}
	}
}


FloorPanel::~FloorPanel()
{
}

void FloorPanel::update()
{
	for (std::vector<FloorButton*>::iterator iter = Buttons.begin(); iter != Buttons.end(); iter++)
	{
		(*iter)->update();
	}
}

void FloorPanel::draw()
{
	al_draw_filled_rectangle(pos_x, pos_y, pos_x + width, pos_y - height, al_map_rgb(0, 255, 0));
	for (std::vector<FloorButton*>::iterator iter = Buttons.begin(); iter != Buttons.end(); iter++)
	{
		(*iter)->draw();
	}
}


void FloorPanel::checkPressed()
{
	for (std::vector<FloorButton*>::iterator iter = Buttons.begin(); iter != Buttons.end(); iter++)
	{
		if((*iter)->checkPressed())
		{
			(*iter)->setLight(1);
			lift->addCall((*iter)->getFloorNum(), (*iter)->getDirection());
		}
		std::cout << "Checking Floor: " << numFloor << " Panel " << (*iter)->getDirection() << std::endl;
	}
}

void FloorPanel::clearButton()
{
	for (std::vector<FloorButton*>::iterator iter = Buttons.begin(); iter != Buttons.end(); iter++)
	{
		(*iter)->setLight(0);

	}
}