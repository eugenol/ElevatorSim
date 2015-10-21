#include "Elevator.h"


Elevator::Elevator(int floors)
{
	ElevatorPanel = new Panel(floors);
}


Elevator::~Elevator()
{
	delete ElevatorPanel;
	ElevatorPanel = nullptr;
}

void Elevator::draw()
{
	ElevatorPanel->draw();
	al_draw_filled_rectangle(pos_x, pos_y, pos_x+width, pos_y+height, al_map_rgb(255, 0, 255));
}

void Elevator::update()
{
	ElevatorPanel->update();
	pos_y += speed*direction;

	if (pos_y < 0)
		direction = 1;
	if (pos_y + height > 600)
		direction = -1;



}