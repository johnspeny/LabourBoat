#include "bullet_system.h"

BulletSystem::BulletSystem(EntityManager& es)
{
	entityManager = &es;
}

void BulletSystem::configure(EventManager& events)
{
	events.subscribe<BulletFiredEvent>(*this);
}

void BulletSystem::receive(const BulletFiredEvent& bulletEvent)
{
	log("bullet fired event recieved");
	this->configureBullet(bulletEvent.startPosition, bulletEvent.velocity, bulletEvent.bulletType, bulletEvent.power);

}

void BulletSystem::update(EntityManager& es, EventManager& events, double dt)
{
}

entityx::Entity BulletSystem::configureBullet(cocos2d::Vec2 startPosition, cocos2d::Vec2 projection, BulletType type, float power)
{
	auto newBullet = entityManager->create();

	newBullet.assign<BulletComponent>(type, power);
	
	return newBullet;
}
