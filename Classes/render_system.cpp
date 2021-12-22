#include "render_system.h"

RenderSystem::RenderSystem()
{
}

RenderSystem::~RenderSystem()
{
}

void RenderSystem::configure(EventManager& events)
{
	// objects interested in receiving [component/obj(event) info] can subscribe to the component event
	// obj that has been emitted is an event
	//event_manager.subscribe<"Component/Obj that has been emitted">("the listener");
	events.subscribe<ComponentAddedEvent<SpriteComponent>>(*this);
	events.subscribe<EntityDestroyedEvent>(*this);
}

void RenderSystem::receive(const ComponentAddedEvent<SpriteComponent>& spriteAddedEvent)
{
	auto sprite = spriteAddedEvent.component->sprite;
	auto currentScene = Director::getInstance()->getRunningScene();
	auto gameLayer = currentScene;

	if (gameLayer)
	{
		auto gameBatchNode = gameLayer->getChildByTag(1000);
		if (gameBatchNode)
		{
			sprite->setEntity(spriteAddedEvent.entity);
			gameBatchNode->addChild(sprite);
		}
		else
		{
			CCLOG("wrong gameBatchNode tag");
		}

	}
	else
	{
		CCLOG("NULL reference currently running scene");
	}
}

void RenderSystem::receive(const EntityDestroyedEvent& entityDestroyedEvent)
{
	auto entity = entityDestroyedEvent.entity;
	if (entity.has_component<SpriteComponent>())
	{
		auto currentScene = Director::getInstance()->getRunningScene();
		auto gameLayer = currentScene;
		
		if (gameLayer)
		{
			if (entity.has_component<SpriteComponent>()) {
				auto spriteComponent = entity.component<SpriteComponent>();
				auto sprite = spriteComponent->sprite;

				auto gameBatch = gameLayer->getChildByTag(1000);
				if (gameBatch)
				{
					gameBatch->removeChild(sprite);
				}
				else
				{
					CCLOG("invalid game batch tag");
				}

			}
		}
		else
		{
			CCLOG("current scene null ref");
		}
	}
}


void RenderSystem::update(EntityManager& es, EventManager& events, TimeDelta dt)
{
}
