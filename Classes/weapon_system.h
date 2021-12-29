#ifndef __WEAPON_SYSTEM_H__
#define __WEAPON_SYSTEM_H__

#include "cocos2d.h"
#include "entityx/entityx.h"
#include "components.h"

USING_NS_CC;
using namespace entityx;

struct PlayerWeaponFiredEvent : public entityx::Event<PlayerWeaponFiredEvent>
{
	
};


class WeaponSystem : public entityx::System<WeaponSystem>, public entityx::Receiver<WeaponSystem>
{
public:
	WeaponSystem(EntityManager& es);

	void configure(EventManager& events);

	void receive(const PlayerWeaponFiredEvent& weaponFiredEvent);

	void update(EntityManager& es, EventManager& events, double dt);

private:
	
	// reference to the entity system for creating entities outside of update method.
	EntityManager* entityManager;
	EventManager* eventManager;
};

#endif // !__WEAPON_SYSTEM_H__
