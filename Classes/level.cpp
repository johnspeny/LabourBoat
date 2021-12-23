#include "level.h"


Level::Level()
{
	// add render system
	systems.add<RenderSystem>();
	systems.add<InputSystem>();
	systems.add<MovementSystem>();

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
}

Entity Level::createPlayer()
{
	auto entity = entities.create();
	

	// add a sprite component on entity
	auto spriteComponent = entity.assign<SpriteComponent>("player.png");

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



	return entity;
}
