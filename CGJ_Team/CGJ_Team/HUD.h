#ifndef _HUD_
#define _HUD_

#include "SceneNode.h"
#include "Tank.h"

class HUD
{
public:
	HUD(SceneNode* bar1, SceneNode* bar2, SceneNode* bar3, Tank* tankObject);
	~HUD();

	void update();
	void reset();

	
private:

	SceneNode* HUDBar1, *HUDBar2, *HUDBar3;
	Tank* tank;
};

#endif