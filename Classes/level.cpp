#include "level.h"


Level::Level()
{
	// add render system
	systems.add<RenderSystem>();
	systems.add<InputSystem>();
	systems.add<MovementSystem>();
	systems.add<CollisionSystem>();

	// configure all systems
	systems.configure();

	// create a player at start
	auto player = this->createPlayer();
}

Level::~Level()
{
}

void Level::update(double dt)
{
	systems.update<RenderSystem>(dt);
	systems.update<InputSystem>(dt);
	systems.update<MovementSystem>(dt);
	systems.update<CollisionSystem>(dt);
}

Entity Level::createPlayer()
{
	auto entity = entities.create();
	Size visibleSize = Director::getInstance()->getVisibleSize();
	auto spriteComponent = entity.assign<SpriteComponent>("player.png");
	auto sprite = spriteComponent->sprite;
	sprite->setPosition(Vec2(visibleSize.width * 0.5f, visibleSize.height * 1 / 3.f));
	sprite->setRotation(-90);

	// add an input component to this 
	InputMap keyMap;
	keyMap = {
		{ "up", EventKeyboard::KeyCode::KEY_W },
		{ "down", EventKeyboard::KeyCode::KEY_S },
		{ "left", EventKeyboard::KeyCode::KEY_A },
		{ "right", EventKeyboard::KeyCode::KEY_D }
	};
	entity.assign<InputComponent>(keyMap);

	// add a player component to player
	entity.assign<PlayerComponent>(300.0f);

	// add a velocity component
	entity.assign<VelocityComponent>();

	// add a boundary component
	entity.assign<BoundaryComponent>(Rect(0, 0, visibleSize.width, visibleSize.height));

	// add a physics body with collision component
	entity.assign<CollisionComponent>();

	return entity;
}
