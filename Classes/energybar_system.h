#ifndef __ENERGYBAR_SYSTEM_H__
#define __ENERGYBAR_SYSTEM_H__

#include "cocos2d.h"
#include "entityx/entityx.h"
#include "components.h"
#include "weapon_system.h"

USING_NS_CC;
using namespace entityx;


struct AttemptWeaponFireEvent : public entityx::Event < AttemptWeaponFireEvent >
{
	AttemptWeaponFireEvent(Entity new_entity) : entity(new_entity){}
	entityx::Entity entity;
};



class EnergyBarSystem : public entityx::System<EnergyBarSystem>, public entityx::Receiver<EnergyBarSystem>
{
public:

	void configure(EventManager& events);

	void receive(const AttemptWeaponFireEvent& attemptWeaponFireEvent);

		
	void update(EntityManager& es, EventManager& events, double dt);

private:
	EventManager* eventManager;

};

#endif // !__WEAPON_SYSTEM_H__
