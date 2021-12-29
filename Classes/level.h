#ifndef __LEVEL_H__
#define __LEVEL_H__

#include "cocos2d.h"
#include "entityx/entityx.h"
#include "render_system.h"
#include "input_system.h"
#include "movement_system.h"
//#include "collision_system.h"
#include "physics_system.h"
#include "MyBodyParser.h"
#include "bullet_system.h"
#include "weapon_system.h"
#include "energybar_system.h"


USING_NS_CC;
using namespace entityx;

class Level : public entityx::EntityX
{
private:
	Entity createPlayer();

	b2WorldNode* _world;

public:
	Level();
	~Level();

	void update(double dt);
};

#endif // !__LEVEL_H__
