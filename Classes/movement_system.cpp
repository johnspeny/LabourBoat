#include "movement_system.h"


void MovementSystem::configure(EventManager& event_manager)
{
}

void MovementSystem::update(EntityManager& es, EventManager& events, TimeDelta dt)
{
	ComponentHandle<SpriteComponent> spriteComponent;
	ComponentHandle<VelocityComponent> velocityComponent;

	for (entityx::Entity entity : es.entities_with_components(spriteComponent, velocityComponent))
	{
		auto sprite = spriteComponent->sprite;
		auto pos = sprite->getPosition();

		Vec2 velocity = velocityComponent->velocity;

		float new_x = pos.x + velocity.x * dt;
		float new_y = pos.y + velocity.y * dt;

		sprite->setPosition(new_x, new_y);
	}
}
