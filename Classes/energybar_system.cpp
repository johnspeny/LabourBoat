#include "energybar_system.h"

void EnergyBarSystem::configure(EventManager& events)
{
	events.subscribe<AttemptWeaponFireEvent>(*this);
	eventManager = &events;
}

void EnergyBarSystem::receive(const AttemptWeaponFireEvent& attemptWeaponFireEvent)
{
	// if the bar is not low emit allow weapon to fire(weapon event)
	//eventManager->emit<PlayerWeaponFiredEvent>(entity);
}

void EnergyBarSystem::update(EntityManager& es, EventManager& events, double dt)
{
}
