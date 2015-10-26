#include "FloorButton.h"

FloorButton::FloorButton(int floor_num, int dir, int y, int h)
{
	floorNumber = floor_num;
	direction = dir;
	pos_y = y - 2;
	height = h - 4;
	width = 50;
	pos_x = 640 + dir * 70;
	font = al_load_ttf_font("Matchworks.ttf", 18, 0);
}


FloorButton::~FloorButton()
{
	al_destroy_font(font);
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

	if (direction == 0)
		al_draw_text(font, al_map_rgb(0, 0, 0), pos_x + width / 2, pos_y - height / 2, 0, "U");
	else
		al_draw_text(font, al_map_rgb(0, 0, 0), pos_x + width / 2, pos_y - height / 2, 0, "D");


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