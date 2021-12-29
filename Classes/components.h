#ifndef __COMPONENTS_H__
#define __COMPONENTS_H__

#include "entityx/entityx.h"
#include "cocos2d.h"
#include "box2d/box2d.h"

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

	inline void setEntity(entityx::Entity new_entity)
	{
		entity = new_entity;
	}

	entityx::Entity getEntity() const
	{
		return entity;
	}
};


struct SpriteComponent : public entityx::Component<SpriteComponent>
{
	SpriteComponent(const std::string& new_filename)
	{
		sprite = CollidibleSprite::createWithSpriteFrameName(new_filename);
		sprite->setName("player");
	}

	SpriteComponent(std::string& new_filename)
	{
		sprite = CollidibleSprite::createWithSpriteFrameName(new_filename);
		sprite->setName("player");
	}

	SpriteComponent()
	{
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

struct PlayerComponent : public entityx::Component<PlayerComponent>
{
	PlayerComponent(float new_speed) : speed(new_speed) {}
	PlayerComponent() : speed(0.0f) {}

	float speed;
};


typedef std::map<const std::string, cocos2d::EventKeyboard::KeyCode> InputMap;
typedef std::map<const std::string, bool> InputKeyPressedMap;
typedef std::pair<const std::string, bool> PairKeynBool;

struct InputComponent : public entityx::Component<InputComponent>
{

	//InputComponent(){}
	InputComponent(InputMap keyMap) : InputComponent()
	{
		for (auto&  e: keyMap)
		{
			inputMap.insert(e);
		}
	}

	InputComponent()
	{
		keyPressedMap.insert(PairKeynBool("up", false));
		keyPressedMap.insert(PairKeynBool("down", false));
		keyPressedMap.insert(PairKeynBool("left", false));
		keyPressedMap.insert(PairKeynBool("right", false));
		keyPressedMap.insert(PairKeynBool("fire", false));
	}

	InputMap inputMap;

	InputKeyPressedMap keyPressedMap;
};


struct BoundaryComponent : public entityx::Component<BoundaryComponent>
{
	BoundaryComponent(cocos2d::Rect new_bound) : bound(new_bound){}
	BoundaryComponent() : bound(cocos2d::Rect(0, 0, 1, 1)){}

	cocos2d::Rect bound;
};

struct CollisionComponent : public entityx::Component<CollisionComponent>
{

};

struct PhysicsComponent : public entityx::Component<PhysicsComponent>
{
	PhysicsComponent(b2Body* body) :body(body)
	{}

	b2Body* body;

	entityx::Entity self;//
};


enum class BulletType
{
	SMALL_SHOT,
	MEDIUM_SHOT,
	LARGE_SHOT,
	PLAYER_MISSILE,
	PLAYER_LASER,
	NO_BULLET_TYPE
};

inline const std::string bulletToString(BulletType type)
{
	switch (type)
	{
	case BulletType::SMALL_SHOT:
		return "smallshot1.png";
	case BulletType::MEDIUM_SHOT:
		return "mediumshot1.png";
	case BulletType::LARGE_SHOT:
		return "largeshot1.png";
	case BulletType::PLAYER_MISSILE:
		return "playermissile.png";
	case BulletType::PLAYER_LASER:
		return "playerlaser1.png";
	default:
		//need better error handling here
		CCLOG("[!] attempted to query string for undefined bullet type.");
		return "err";
		break;
	}
}


struct BulletComponent : entityx::Component < BulletComponent >
{
	BulletComponent(BulletType new_type, float new_power) : type(new_type), power(new_power) {}
	BulletComponent() : type(BulletType::NO_BULLET_TYPE), power(1.f) {};

	BulletType					type;
	float                       power;
};


struct WeaponComponent : entityx::Component < WeaponComponent >
{

	WeaponComponent(){}

};


struct EnergyBarComponent : entityx::Component < EnergyBarComponent >
{

	EnergyBarComponent() {}

};


#endif // !__COMPONENTS_H__
