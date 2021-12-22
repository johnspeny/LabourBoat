#ifndef __GAMELAYER_H__
#define __GAMELAYER_H__

#include "cocos2d.h"
#include "level.h"

USING_NS_CC;

class GameLayer : public cocos2d::Scene
{
private:
	Level* currentLevel = nullptr;
	void setupLevel(float);

public:
	virtual bool init() override;
	virtual void update(float dt) override;
};


#endif // !__GAMELAYER_H__
