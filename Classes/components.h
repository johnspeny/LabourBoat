#ifndef __COMPONENTS_H__
#define __COMPONENTS_H__

#include "entityx/entityx.h"
#include "cocos2d.h"

USING_NS_CC;
using namespace entityx;

class CollidibleSprite : public cocos2d::Sprite
{
private:
	entityx::Entity entity; // entity created here
public:
	CollidibleSprite(){}

	static CollidibleSprite* createWithSpriteFrameName(const std::string& filename)
	{
		CollidibleSprite* spriteObj = new CollidibleSprite();
		if (spriteObj && spriteObj->initWithSpriteFrameName(filename))
		{
			spriteObj->autorelease();
			return spriteObj;
		}
		CC_SAFE_DELETE(spriteObj);
		return nullptr;
	}

	inline void setEntity(entityx::Entity new_entity) {
		entity = new_entity;
	}

	entityx::Entity getEntity() const {
		return entity;
	}
};


struct SpriteComponent : public entityx::Component<SpriteComponent>
{
	SpriteComponent(const std::string& new_filename){
		sprite = CollidibleSprite::createWithSpriteFrameName(new_filename);
	}

	SpriteComponent(std::string& new_filename) {
		sprite = CollidibleSprite::createWithSpriteFrameName(new_filename);
	}

	SpriteComponent() {
		sprite = (CollidibleSprite*)CollidibleSprite::create();
	}

	CollidibleSprite* sprite;
};


struct VelocityComponent : public entityx::Component<VelocityComponent>
{
	VelocityComponent(float x, float y) :  velocity(Vec2(x, y)){}
	VelocityComponent(Vec2 new_velocity) : velocity(new_velocity) {}
	VelocityComponent() : velocity(Vec2(0.0f, 0.0f)) {}
	Vec2 velocity;
};

struct InputComponent : public entityx::Component<InputComponent>
{


};

struct PlayerComponent : public entityx::Component<PlayerComponent>
{
	PlayerComponent(float new_speed) : speed(new_speed) {}
	PlayerComponent() : speed(0.0f) {}

	float speed;
};

#endif // !__COMPONENTS_H__
