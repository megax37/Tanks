#ifndef _OBJECT_
#define _OBJECT_

class Object
{
public:

	void virtual update(int elapsedTime) = 0;
	void virtual move() = 0;
};

#endif