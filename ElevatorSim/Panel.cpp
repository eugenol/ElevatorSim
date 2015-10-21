#include "Panel.h"


Panel::Panel(int floors)
{
	for (int i = 0; i < floors; i++)
		Buttons.push_back(new Button(i));
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
