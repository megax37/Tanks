#include "HUD.h"
#include <iostream>
using namespace std;

HUD::HUD(SceneNode* bar1, SceneNode* bar2, SceneNode* bar3, Tank* tankObject)
{
	HUDBar1 = bar1;
	HUDBar2 = bar2;
	HUDBar3 = bar3;

	tank = tankObject;
}

HUD::~HUD()
{
}

void HUD::update()
{
	if (tank->getLife() == 2)
		HUDBar3->setVisible(false);

	if (tank->getLife() == 1) {
		HUDBar3->setVisible(false);
		HUDBar2->setVisible(false);
	}

	if (tank->getLife() == 0) {
		HUDBar3->setVisible(false);
		HUDBar2->setVisible(false);
		HUDBar1->setVisible(false);
	}
}

void HUD::reset()
{
	HUDBar1->setVisible(true);
	HUDBar2->setVisible(true);
	HUDBar3->setVisible(true);
}