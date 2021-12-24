#ifndef __COLLISION_SYSTEM_H__
#define __COLLISION_SYSTEM_H__

#include "cocos2d.h"
#include "entityx/entityx.h"
#include "components.h"
#include "GameVars.h"
#include "b2WorldNode.h"

USING_NS_CC;
using namespace entityx;

class CollisionSystem : public entityx::System<CollisionSystem>, public Receiver<CollisionSystem>
{
private:
	b2WorldNode* _world;

public:
	void configure(EventManager& events);
	void receive(const ComponentAddedEvent<CollisionComponent>& collisionComponentAddedEvent);
	void update(EntityManager& es, EventManager& events, double dt) override;

};

#endif // !__COLLISION_SYSTEM_H__
