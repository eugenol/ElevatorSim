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
	al_draw_filled_rectangle(pos_x, pos_y, pos_x+width, pos_y+height, al_map_rgb(255, 0, 255));
}