#include "Floor.h"


Floor::Floor(int floor_num, int max_floors, int y, int h, Elevator *lift) : Panel(floor_num, max_floors, y, h, lift)
{
	floorNum = floor_num;
	maxFloors = max_floors;
	pos_y = y;
	height = h;
}


Floor::~Floor()
{
}

void Floor::update()
{
	Panel.update();
}


void Floor::draw()
{
	al_draw_line(400, pos_y, 800, pos_y, al_map_rgb(255, 0, 255), 2);
	Panel.draw();
}

void Floor::checkPressed()
{
	if (InputManager::getInstance().getMouseY() < pos_y &&
		InputManager::getInstance().getMouseY() > pos_y - height)
	{
		Panel.checkPressed();
	}
	
}