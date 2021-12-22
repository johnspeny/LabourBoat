#ifndef __MOVEMENT_SYSTEM_H__
#define __MOVEMENT_SYSTEM_H__

#include "cocos2d.h"
#include "entityx/entityx.h"
#include "components.h"

using namespace entityx;

class MovementSystem : public System<MovementSystem>
{

public:
	MovementSystem();
	~MovementSystem();

	void configure(EventManager& event_manager);

	void update(EntityManager& es, EventManager& events, TimeDelta dt) override;

};

#endif // !__MOVEMENT_SYSTEM_H__
