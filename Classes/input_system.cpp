#include "input_system.h"

InputSystem::InputSystem()
{
}

InputSystem::~InputSystem()
{
}

void InputSystem::configure(EventManager& event_manager)
{
	// subscribe object to listen to events
	event_manager.subscribe<ComponentAddedEvent<InputComponent>>(*this);
	event_manager.subscribe<ComponentRemovedEvent<InputComponent>>(*this);

	//setup keyboard listener
	auto listener = EventListenerKeyboard::create();
	listener->onKeyPressed = CC_CALLBACK_2(InputSystem::keyPressed, this);
	listener->onKeyReleased = CC_CALLBACK_2(InputSystem::keyReleased, this);

	auto director = Director::getInstance();
	auto eventDispatcher = director->getEventDispatcher();
	eventDispatcher->addEventListenerWithFixedPriority(listener, 1);

	eventManager = &event_manager;

}

void InputSystem::receive(const ComponentAddedEvent<InputComponent>& inputComponentAddedEvent)
{
	players.push_back(inputComponentAddedEvent.entity);
}

void InputSystem::receive(const ComponentRemovedEvent<InputComponent>& inputComponentRemovedEvent)
{
	players.remove(inputComponentRemovedEvent.entity);
}

void InputSystem::update(EntityManager& es, EventManager& events, TimeDelta dt)
{
}

void InputSystem::keyPressed(EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
{
	for (entityx::Entity entity : players)
	{
		if (entity.has_component<SpriteComponent>() && entity.has_component<VelocityComponent>() && entity.has_component<PlayerComponent>()) 
		{
			auto ic = entity.component<InputComponent>();
			auto keyMap = ic->inputMap;
			float speed = entity.component<PlayerComponent>()->speed;
			Vec2 velocity = entity.component<VelocityComponent>()->velocity;

			if (keyCode == keyMap.at("up"))
			{
				velocity.y = speed;
				ic->keyPressedMap["up"] = true;
			}
			else if (keyCode == keyMap.at("left"))
			{
				velocity.x = -speed;
				ic->keyPressedMap["left"] = true;
			}
			else if (keyCode == keyMap.at("right"))
			{
				velocity.x = speed;
				ic->keyPressedMap["right"] = true;
			}
			else if (keyCode == keyMap.at("down"))
			{
				velocity.y = -speed;
				ic->keyPressedMap["down"] = true;
			}
			// unit vector (divide every component by a unit vector)
			velocity.normalize();

			entity.component<VelocityComponent>()->velocity = velocity * speed;

		}
		else
		{
			log("entity does not have those components");
		}
	}
}

void InputSystem::keyReleased(EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
{
	for (entityx::Entity entity : players)
	{
		if (entity.has_component<SpriteComponent>() && entity.has_component<VelocityComponent>() && entity.has_component<PlayerComponent>())
		{
			auto ic = entity.component<InputComponent>();
			auto keyMap = ic->inputMap;
			float speed = entity.component<PlayerComponent>()->speed;
			Vec2 velocity = entity.component<VelocityComponent>()->velocity;

			if (keyCode == keyMap.at("up"))
			{
				if (ic->keyPressedMap["down"])
				{
					velocity.y = -speed;
				}
				else
				{
					velocity.y = 0;
				}
				//velocity.y = 0;
				ic->keyPressedMap["up"] = false;
			}
			else if (keyCode == keyMap.at("left"))
			{
				if (ic->keyPressedMap["right"])
				{
					velocity.x = speed;
				}
				else
				{
					velocity.x = 0;
				}
				
				ic->keyPressedMap["left"] = false;
			}
			else if (keyCode == keyMap.at("right"))
			{
				if (ic->keyPressedMap["left"])
				{
					velocity.x = -speed;
				}
				else
				{
					velocity.x = 0;
				}

				ic->keyPressedMap["right"] = false;
			}
			else if (keyCode == keyMap.at("down"))
			{
				if (ic->keyPressedMap["up"])
				{
					velocity.y = speed;
				}
				else
				{
					velocity.y = 0;
				}
				ic->keyPressedMap["down"] = false;
			}
			// unit vector (divide every component by a unit vector)
			velocity.normalize();

			entity.component<VelocityComponent>()->velocity = velocity * speed;

		}
		else
		{
			log("entity does not have those components");
		}
	}
}

