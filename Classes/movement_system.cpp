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

		// boundary
		if (entity.has_component<BoundaryComponent>())
		{
			auto bounds = entity.component<BoundaryComponent>()->bound;
			auto contextS = sprite->getContentSize();
			bool boundLeftX = new_x < bounds.origin.x;
			bool boundRightX = new_x > bounds.size.width;

			bool boundBottomY = new_y - contextS.height / 3 < bounds.origin.y;
			bool boundTopY = new_y +  contextS.height / 3 > bounds.size.height;
			Vec2 newPos(new_x, new_y);

			if (boundLeftX || boundRightX)
			{
				newPos = Vec2(pos.x, new_y);
			}

			if (boundTopY || boundBottomY)
			{
				newPos = Vec2(new_x, pos.y);
			}

			sprite->setPosition(newPos);
		}
		else
		{
			sprite->setPosition(new_x, new_y);
		}

	}
}
