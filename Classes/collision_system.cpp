#include "collision_system.h"

void CollisionSystem::configure(EventManager& events)
{
	events.subscribe<ComponentAddedEvent<CollisionComponent>>(*this);
	// game vars
	GameVars::initVars();
	// create a b2d world
	b2Vec2 gravity;
	gravity.Set(0.0f, 0.0f);

	// create the world
	_world = b2WorldNode::create(gravity.x, gravity.y, GameVars::metersHeight);
	auto currentScene = Director::getInstance()->getRunningScene();
	currentScene->addChild(_world, -1);
}

void CollisionSystem::receive(const ComponentAddedEvent<CollisionComponent>& collisionComponentAddedEvent)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	auto spriteEntity = collisionComponentAddedEvent.entity;
	
	if (!spriteEntity.has_component<SpriteComponent>())
	{
		// error
		log("No sprite component");
	}
	else
	{
		auto sprite = spriteEntity.component<SpriteComponent>()->sprite;


		//// bridge
		//b2BodyDef bridgeDef;
		//bridgeDef.type = b2_dynamicBody;
		//bridgeDef.position.Set(sprite->getPositionX() / GameVars::PTM_Ratio, sprite->getPositionY() / GameVars::PTM_Ratio);
		//
		//CollidibleSprite* actor = sprite;
		//bridgeDef.userData.pointer = reinterpret_cast<uintptr_t>(actor);
		//b2Body* bridgeBody = _world->getb2World()->CreateBody(&bridgeDef);

		//// bridge shape
		//b2PolygonShape bridgeShape;
		//bridgeShape.SetAsBox(0.5f, 0.5f);

		//// connect body to shape
		//bridgeBody->CreateFixture(&bridgeShape, 0.0f);




		b2BodyDef def;
		def.type = b2BodyType::b2_dynamicBody;
		def.position.Set(sprite->getPositionX() / GameVars::PTM_Ratio, sprite->getPositionY() / GameVars::PTM_Ratio);
		CollidibleSprite* actor = sprite;
		def.userData.pointer = reinterpret_cast<uintptr_t>(actor);

		auto body = _world->getb2World()->CreateBody(&def);
		b2PolygonShape shape;
		shape.SetAsBox(0.5, 0.5);
		body->CreateFixture(&shape, 1);
	}
	
}

void CollisionSystem::update(EntityManager& es, EventManager& events, double dt)
{
	_world->getb2World()->Step(dt, 6, 2);

	ComponentHandle<SpriteComponent> spriteComponent;
	for (auto entity : es.entities_with_components(spriteComponent))
	{
		auto sprite = spriteComponent->sprite;
		for (b2Body* body = _world->getb2World()->GetBodyList(); body != nullptr; body = body->GetNext()) {
			if (body->GetUserData().pointer == reinterpret_cast<uintptr_t>(sprite)) {
				CollidibleSprite* spr = (CollidibleSprite*)body->GetUserData().pointer;
				spr->setPosition(Vec2(body->GetPosition().x * GameVars::PTM_Ratio, body->GetPosition().y * GameVars::PTM_Ratio));
				spr->setRotation(-1 * CC_RADIANS_TO_DEGREES(body->GetAngle()));
			}
		}
	}


}
