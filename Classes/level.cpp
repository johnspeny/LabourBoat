#include "level.h"


Level::Level()
{
	// add render system
	systems.add<RenderSystem>();

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
}

Entity Level::createPlayer()
{
	auto entity = entities.create();
	

	// add a sprite component on entity
	auto spriteComponent = entity.assign<SpriteComponent>("player.png");

	// add a velocity component
	entity.assign<VelocityComponent>(300.0f);

	return entity;
}
