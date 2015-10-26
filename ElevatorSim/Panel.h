#ifndef PANEL_H
#define PANEL_H
#include <vector>
#include "Button.h"
#include "allegro5/allegro_primitives.h"
//#include "Elevator.h"

class Elevator; //Forward declaration

class Panel
{
private:
	int	numFloors;
	std::vector<Button*> Buttons;
	int panel_x = 100;
	int panel_y = 100;
	int panel_width = 300;
	int	panel_height = 400;
	Elevator *owner;
	ALLEGRO_FONT *font;
	int currentFloor = 0;
public:
	Panel(int floors);
	Panel(Elevator *elevator);
	~Panel();
	void draw();
	void update();
	void checkPressed();
	void clearButton(int floor_num);
};

#endif
