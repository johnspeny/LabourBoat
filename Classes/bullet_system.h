#ifndef __BULLET_SYSTEM_H__
#define __BULLET_SYSTEM_H__

#include "cocos2d.h"
#include "entityx/entityx.h"
#include "components.h"

USING_NS_CC;
using namespace entityx;


//this is the event which will be emitted when any entity wants to fire a bullet
struct BulletFiredEvent : public entityx::Event < BulletFiredEvent >
{
	BulletFiredEvent(cocos2d::Vec2 new_startPosition, cocos2d::Vec2 new_velocity, BulletType new_bulletType, float new_power)
		: startPosition(new_startPosition), velocity(new_velocity), bulletType(new_bulletType), power(new_power) {}

	Vec2				startPosition,
		velocity;
	BulletType			bulletType;
	float               power;
};


class BulletSystem : public entityx::System<BulletSystem>, public entityx::Receiver<BulletSystem>
{
public:
	BulletSystem(EntityManager& es);

	void configure(EventManager &events);

	void receive(const BulletFiredEvent& bulletEvent);

	void update(EntityManager &es, EventManager& events, double dt);

private:
	// create new bullets whenever an event is fired(Bullet fired event) and return its entity id
	entityx::Entity configureBullet(cocos2d::Vec2 startPosition, cocos2d::Vec2 projection, BulletType type, float power);

	// reference to the entity system for creating entities outside of update method.
	EntityManager* entityManager;

};

#endif // !__BULLET_SYSTEM_H__
