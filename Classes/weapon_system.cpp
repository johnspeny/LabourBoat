#include "weapon_system.h"

WeaponSystem::WeaponSystem(EntityManager& es)
{
	entityManager = &es;
}

void WeaponSystem::configure(EventManager& events)
{
	eventManager = &events;

	events.subscribe<PlayerWeaponFiredEvent>(*this);
}

void WeaponSystem::receive(const PlayerWeaponFiredEvent& weaponFiredEvent)
{

	log("weapon system");
}

void WeaponSystem::update(EntityManager& es, EventManager& events, double dt)
{
}
