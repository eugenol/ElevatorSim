#ifndef FLOOR_H
#define FLOOR_H

#include "allegro5/allegro_primitives.h"
#include "FloorPanel.h"

class Floor
{
private:
	int floorNum;
	int maxFloors;
	int pos_y;
	int height;
	FloorPanel Panel;
	Elevator *lift;
public:
	Floor(int floor_num, int max_floors, int y, int h, Elevator *lift);
	~Floor();
	
	void update();
	void draw();
	void checkPressed();
	void clearButton();
	int onFloor(int y1, int y2);
};

#endif /*FLOOR_H*/
