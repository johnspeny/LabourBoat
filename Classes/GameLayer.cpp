#include "GameLayer.h"


bool GameLayer::init()
{
	if (!Scene::init())
	{
		return false;
	}

	auto spriteBatch = SpriteBatchNode::create("data/mainsheet.png");
	spriteBatch->setTag(1000);
	this->addChild(spriteBatch);
	
	auto cache = SpriteFrameCache::getInstance();
	cache->addSpriteFramesWithFile("data/mainsheet.plist");

	this->scheduleOnce(CC_SCHEDULE_SELECTOR(GameLayer::setupLevel), 0);

	return true;
}

void GameLayer::update(float dt)
{
	currentLevel->update(dt);
}

void GameLayer::setupLevel(float)
{
	currentLevel = new Level();
	this->scheduleUpdate();
}

