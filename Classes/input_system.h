#ifndef __INPUT_SYSTEM_H__
#define __INPUT_SYSTEM_H__

#include "cocos2d.h"
#include "entityx/entityx.h"
#include "components.h"

USING_NS_CC;
using namespace entityx;

class InputSystem : public System<InputSystem>, public Receiver<InputSystem>
{

public:
	InputSystem();
	~InputSystem();

	void configure(EventManager& event_manager);
	void receive(const ComponentAddedEvent<InputComponent>& inputComponentAddedEvent);
	void receive(const ComponentRemovedEvent<InputComponent>& inputComponentRemovedEvent);

	void update(EntityManager& es, EventManager& events, TimeDelta dt) override;

private:
	//used for processing keyboard events
	void keyPressed(EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
	void keyReleased(EventKeyboard::KeyCode keyCode, cocos2d::Event* event);

	std::list<entityx::Entity> players;
	EventManager* eventManager = nullptr;

};


#endif // !__INPUT_SYSTEM_H__