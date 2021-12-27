#ifndef __PHYSICS_SYSTEM_H__
#define __PHYSICS_SYSTEM_H__

#include "cocos2d.h"
#include "entityx/entityx.h"
#include "components.h"
#include "GameVars.h"
#include "b2WorldNode.h"

USING_NS_CC;
using namespace entityx;

class PhysicsSystem : public entityx::System<PhysicsSystem>, public Receiver<PhysicsSystem>
{
private:
	b2WorldNode* _world;

public:
	PhysicsSystem(b2WorldNode* world);
	void configure(EventManager& events);
	void receive(const ComponentAddedEvent<PhysicsComponent>& collisionComponentAddedEvent);
	void update(EntityManager& es, EventManager& events, double dt) override;

};

#endif // !__PHYSICS_SYSTEM_H__
