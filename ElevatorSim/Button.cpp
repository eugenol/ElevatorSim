#include "Button.h"


Button::Button(int floor_number)
{
	floorNumber = floor_number;
	pos_x = 110 + (floorNumber % 3)*50;
	pos_y = 160 + (floorNumber / 3)*50;


}

Button::~Button()
{
}

void Button::update()
{

}

void Button::draw()
{
	if (lightOn == true)
		al_draw_filled_rectangle(pos_x, pos_y, pos_x+width, pos_y+height, al_map_rgb(255, 255, 255));
	else
		al_draw_filled_rectangle(pos_x, pos_y, pos_x + width, pos_y + height, al_map_rgb(255, 0, 255));
}

bool Button::isPressed()
{
	if (InputManager::getInstance().getMouseX() > pos_x &&
		InputManager::getInstance().getMouseX() < pos_x + width &&
		InputManager::getInstance().getMouseY() > pos_y &&
		InputManager::getInstance().getMouseY() < pos_y + width)
	{
		std::cout << "Floor " << floorNumber << " pressed" << std::endl;
		return !lightOn;
	}
	return false;
}

void Button::setLight(int onOff)
{
	lightOn = onOff ? true : false;
}