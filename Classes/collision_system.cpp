#include "collision_system.h"

void CollisionSystem::configure(EventManager& events)
{
	events.subscribe<ComponentAddedEvent<CollisionComponent>>(*this);
	// game vars
	GameVars::initVars();
	// create a b2d world
	b2Vec2 gravity;
	gravity.Set(0.0f, -9.8f);

	// create the world
	_world = b2WorldNode::create(gravity.x, gravity.y, GameVars::metersHeight);
	auto currentScene = Director::getInstance()->getRunningScene();
	currentScene->addChild(_world, -1);
}

void CollisionSystem::receive(const ComponentAddedEvent<CollisionComponent>& collisionComponentAddedEvent)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	// bridge
	b2BodyDef bridgeDef;
	bridgeDef.type = b2_staticBody;
	bridgeDef.position.Set(visibleSize.width * 0.5f / GameVars::PTM_Ratio, visibleSize.height * 0.1f / GameVars::PTM_Ratio);
	b2Body* bridgeBody = _world->getb2World()->CreateBody(&bridgeDef);

	// bridge shape
	b2PolygonShape bridgeShape;
	bridgeShape.SetAsBox(0.5f, 0.5f);

	// connect body to shape
	bridgeBody->CreateFixture(&bridgeShape, 0.0f);
}

void CollisionSystem::update(EntityManager& es, EventManager& events, double dt)
{
	_world->getb2World()->Step(dt, 6, 2);
}
