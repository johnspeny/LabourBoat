#ifndef __RENDER_SYSTEM_H__
#define __RENDER_SYSTEM_H__

#include "cocos2d.h"
#include "entityx/entityx.h"
#include "components.h"

USING_NS_CC;
using namespace entityx;

// ---- systems implement behaviour of components
class RenderSystem : public System<RenderSystem>, public Receiver<RenderSystem>  
{
public:
	RenderSystem();
	~RenderSystem();

	void configure(EventManager &events);

	void receive(const ComponentAddedEvent<SpriteComponent>& spriteAddedEvent);
	void receive(const EntityDestroyedEvent& entityDestroyedEvent);

	void update(EntityManager &es, EventManager &events, TimeDelta dt) override;
};


#endif // !__RENDER_SYSTEM_H__
