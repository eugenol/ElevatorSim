#ifndef BUILDING_H
#define BUILDING_H

class Building
{
private:
	int numFloors;
public:
	Building(int num_floors);
	~Building();
	
	void update();
	void draw();
};

#endif /*BUILDING_H*/