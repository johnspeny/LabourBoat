#include "physics_system.h"

PhysicsSystem::PhysicsSystem(b2WorldNode* world)
{
	_world = world;
}

void PhysicsSystem::configure(EventManager& events)
{
	events.subscribe<ComponentAddedEvent<PhysicsComponent>>(*this);

}

void PhysicsSystem::receive(const ComponentAddedEvent<PhysicsComponent>& collisionComponentAddedEvent)
{
	auto pEntity = collisionComponentAddedEvent.component;
	if (pEntity)
	{
		pEntity->self = collisionComponentAddedEvent.entity;
		if (pEntity->body)
		{
			pEntity->body->GetUserData().pointer = reinterpret_cast<uintptr_t>(&(pEntity->self));
		}
	}
}

void PhysicsSystem::update(EntityManager& es, EventManager& events, double dt)
{
	

	ComponentHandle<PhysicsComponent> physicsComponent;
	ComponentHandle<SpriteComponent> spriteComponent;
	ComponentHandle<VelocityComponent> velocityComponent;

	for (auto entity : es.entities_with_components(physicsComponent, spriteComponent, velocityComponent))
	{
		auto bodyPhyics = entity.component<PhysicsComponent>()->body;

		if (!bodyPhyics)
		{
			return;
		}
		auto pos = entity.component<SpriteComponent>()->sprite;
		bodyPhyics->SetTransform(b2Vec2(pos->getPositionX() / GameVars::PTM_Ratio, pos->getPositionY() / GameVars::PTM_Ratio), bodyPhyics->GetAngle());
	}

		//for (b2Body* body = _world->getb2World()->GetBodyList(); body != nullptr; body = body->GetNext()) {
		//	uintptr_t x = body->GetUserData().pointer;
		//	uintptr_t y = bodyPhyics->GetUserData().pointer;
		//	
		//	if (x == y) {
		//		CollidibleSprite* spr = spriteComponent->sprite;
		//		spr = (CollidibleSprite*)body->GetUserData().pointer;
		//		//CollidibleSprite* spr = (CollidibleSprite*)body->GetUserData().pointer;
		//		spr->setPosition(Vec2(body->GetPosition().x * GameVars::PTM_Ratio, body->GetPosition().y * GameVars::PTM_Ratio));
		//		//spr->setRotation(-1 * CC_RADIANS_TO_DEGREES(body->GetAngle()));
		//	}
		//}

		static int velocityIterations = 8;
		static int positionIterations = 1;

		_world->getb2World()->Step(dt, 6, 2);
	

		for (auto entity : es.entities_with_components(physicsComponent, spriteComponent, velocityComponent))
		{
			auto bodyPhyics = entity.component<PhysicsComponent>()->body;

			if (!bodyPhyics)
			{
				return;
			}
			auto sp = entity.component<SpriteComponent>()->sprite;
			sp->setPosition(Vec2(bodyPhyics->GetPosition().x * GameVars::PTM_Ratio, bodyPhyics->GetPosition().y * GameVars::PTM_Ratio));
			sp->setRotation(-1 * CC_RADIANS_TO_DEGREES(bodyPhyics->GetAngle()));

			//bodyPhyics->SetTransform(b2Vec2(pos->getPositionX() / GameVars::PTM_Ratio, pos->getPositionY() / GameVars::PTM_Ratio), bodyPhyics->GetAngle());
		}
}
