#include "FloorButton.h"

FloorButton::FloorButton(int floor_num, int dir, int y, int h)
{
	floorNumber = floor_num;
	direction = dir;
	pos_y = y - 2;
	height = h - 4;
	width = 50;
	pos_x = 620 + dir * 70;
}


FloorButton::~FloorButton()
{
}


void FloorButton::update()
{

}

void FloorButton::draw()
{

	if (lightOn == true)
		al_draw_filled_rectangle(pos_x, pos_y, pos_x + width, pos_y - height, al_map_rgb(255, 255, 255));
	else
		al_draw_filled_rectangle(pos_x, pos_y, pos_x + width, pos_y - height, al_map_rgb(0, 0, 255));


}

bool FloorButton::checkPressed()
{
	if (InputManager::getInstance().getMouseX() > pos_x &&
		InputManager::getInstance().getMouseX() < pos_x + width &&
		InputManager::getInstance().getMouseY() < pos_y &&
		InputManager::getInstance().getMouseY() > pos_y - height)
	{
		std::cout << "Floor " << floorNumber << " pressed "<< direction << std::endl;
		return !lightOn;
	}
	return false;
}

void FloorButton::setLight(int onOff)
{
	lightOn = onOff ? true : false;
}