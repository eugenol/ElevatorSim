#include "Elevator.h"
//#include "Panel.h"


Elevator::Elevator(int floors)
{
	numFloors = floors;
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
	al_draw_filled_rectangle(pos_x, pos_y, pos_x+width, pos_y+height, al_map_rgb(255, 0, 255));
}

void Elevator::update()
{
	//if (InputManager::getInstance().isMouseButtonPressed(0) && (InputManager::getInstance().getMouseX()))
	
	ElevatorPanel->update();
	
	pos_y += speed*direction;

	if (pos_y < 0)
		direction = 1;
	if (pos_y + height > 600)
		direction = -1;

	ElevatorPanel->

}


void Elevator::addDestination(int destFloor)
{
	upQueue.push_back(destFloor);
}
void  Elevator::checkButtons()
{
	ElevatorPanel->checkPressed();
	std::cout << "Checking Panel" << std::endl;
}