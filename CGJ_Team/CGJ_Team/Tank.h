#ifndef _TANK_
#define _TANK_

#include "SceneNode.h"

class Tank
{
public:
	Tank(SceneNode* tankBase, SceneNode* frontLeftWheel, SceneNode* frontRightWheel, SceneNode* backLeftWheel, SceneNode* backRightWheel, SceneNode* tankTurret);
	~Tank();

private:

	SceneNode* tankBase, *frontLeftWheel, *frontRightWheel, *backLeftWheel, *backRightWheel, *tankTurret;
};

#endif