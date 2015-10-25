#ifndef BUILDING_H
#define BUILDING_H
#include "Floor.h"
#include <vector>
#include "Elevator.h"

class Building
{
private:
	int numFloors;
	Elevator *lift;
	std::vector<Floor*> Floors;

public:
	Building(int num_floors);
	~Building();
	
	void update();
	void draw();
	void checkPressed();
	void clearFloorButton(int floor);
};

#endif /*BUILDING_H*/