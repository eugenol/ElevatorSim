#ifndef BASEOBJECT_H
#define BASEOBJECT_H
class BaseObject
{
public:
	BaseObject();
	virtual ~BaseObject();
	virtual void update() = 0;
	virtual void draw() = 0;
};
#endif
