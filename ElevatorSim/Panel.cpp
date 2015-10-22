#include "Panel.h"
#include "Elevator.h"


//Panel::Panel(int floors)
//{
//	for (int i = 0; i < floors; i++)
//		Buttons.push_back(new Button(i));
//}

Panel::Panel(Elevator *elevator)
{
	owner = elevator;
	numFloors = owner->getFloors();
	for (int i = 0; i < numFloors; i++)
		Buttons.push_back(new Button(i));
	//owner->addPanel(this);
}


Panel::~Panel()
{
	for (std::vector<Button*>::iterator iter = Buttons.begin(); iter != Buttons.end();iter++)
	{
		Button *tempPtr = *iter;
		delete tempPtr;
	}
	Buttons.clear();
}

void Panel::draw()
{
	al_draw_filled_rectangle(panel_x, panel_y, panel_width, panel_height, al_map_rgb(255, 0, 0));
	for (std::vector<Button*>::iterator iter = Buttons.begin(); iter != Buttons.end(); iter++)
	{
		(*iter)->draw();
	}
}

void Panel::update()
{
	for (std::vector<Button*>::iterator iter = Buttons.begin(); iter != Buttons.end(); iter++)
	{
		(*iter)->update();
	}
}

void Panel::checkPressed()
{
	for (std::vector<Button*>::iterator iter = Buttons.begin(); iter != Buttons.end(); iter++)
	{
		if ((*iter)->isPressed())
		{
			(*iter)->setLight(1);
			owner->addDestination((*iter)->getFloorNum());
		}
	}
}

void Panel::clearButton(int floor_num)
{
	Buttons[floor_num]->setLight(0);
}