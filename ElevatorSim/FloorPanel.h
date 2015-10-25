#ifndef FLOORPANEL_H
#define FLOORPANEL_H

#include "FloorButton.h" 
#include <vector>
#include "allegro5/allegro_primitives.h"

class Elevator;

class FloorPanel
{
private:
	int numFloor;
	int maxFloors;
	std::vector<FloorButton*> Buttons;
	int pos_y;
	int pos_x;
	int width;
	int height;
	Elevator *lift;
public:
	FloorPanel(int floor_num, int max_floors, int y, int h, Elevator *_lift);
	~FloorPanel();
	void update();
	void draw();
	void checkPressed();
	void clearButton();
};

#endif /*FLOORPANEL_H*/
