#ifndef __GAMELAYER_H__
#define __GAMELAYER_H__

#include "cocos2d.h"
#include "GameSprite.h"

#include "audio/include/AudioEngine.h"


typedef enum {
	kCreatureHealthBar,
	kBridgeHealthBar
};

typedef enum {
	kBackground,
	kMiddleground,
	kForeground
};

class GameLayer : public cocos2d::Scene
{
private:
	// math helpers
	cocos2d::Vec2 moveTowards(cocos2d::Vec2 current, cocos2d::Vec2 target, float maxDelta);
	float distanceBetween(cocos2d::Vec2 current, cocos2d::Vec2 target);

	// check if game is playing
	bool _playing;

	// screen size
	cocos2d::Size _screenSize;
	cocos2d::Vec2 _origin;

	// game batch
	cocos2d::SpriteBatchNode* _gameBatchNode;
	
	// CREATURE // ----------
	int _creatureIndexPool;
	int _fallCreatureIndex;
	cocos2d::Vector<cocos2d::Sprite*> _creaturePool;
	cocos2d::Vector<cocos2d::Sprite*> _fallingCreatures;
	float timeOfCreature, intervalOfCreature, speedOfCreature;
	void doGenerateNewCreature();
	void onFallingCreatureDone();
	bool isDoneGenerateNewCreature;
	float currentHealth;
	float totalHealth;

	// BOAT		// ------------
	GameSprite* _boat;

	// WATER    // ------------
	int _opacityWater;

	// WOOD		// ------------
	int _collidedWoodIndex;
	cocos2d::Vector<cocos2d::Sprite*> _woodCollided;
	cocos2d::Sprite* firstCollidedWood;
	int _woodIndexPool;
	int _fallWoodIndex;
	cocos2d::Sprite* _wood;
	cocos2d::Vector<cocos2d::Sprite*> _woodPool;
	cocos2d::Vector<cocos2d::Sprite*> _fallingWood;
	float timeOfWood, intervalOfWood, speedOfWood;
	void doGenerateNewWood();
	bool isDoneGenerateNewWood;

	cocos2d::Sprite* woodUI;
	cocos2d::Label* _scoreWood;
	int _woodIntscore;

	// BRIDGE		// ------------
	std::vector<cocos2d::Sprite*> _bridgePool;
	cocos2d::Sprite* bridge;

	// BRIDGE		// ------------
	cocos2d::Sprite* water;

	// POLLUTANT		// ------------
	int _pollutantIndexPool;
	int _fallPollutantIndex;
	int _collidedPollutantIndex;
	cocos2d::Sprite* _pollutant;
	cocos2d::Vector<cocos2d::Sprite*> _pollutantPool;
	cocos2d::Vector<cocos2d::Sprite*> _fallingPollutant;
	cocos2d::Vector<cocos2d::Sprite*> _pollutantCollided;
	cocos2d::Sprite* firstCollided;
	int loopCounter = 0;
	bool isAddToCollide;
	bool isNotAddToCollide;

	float timeOfPollutant, intervalOfPollutant, speedOfPollutant;
	void doGenerateNewPollutant();
	bool isDoneGenerateNewPollutant;
	float currentPHealth;
	float totalPHealth;


	// HUMAN		// ------------
	int _humanIndexPool;
	int _fallHumanIndex;
	int _collidedHumanIndex;
	cocos2d::Sprite* _human;
	cocos2d::Vector<cocos2d::Sprite*> _humanPool;
	cocos2d::Vector<cocos2d::Sprite*> _fallingHuman;
	cocos2d::Vector<cocos2d::Sprite*> _humanCollided;
	cocos2d::Sprite* firstCollidedHuman;

	float timeOfHuman, intervalOfHuman, speedOfHuman;
	void doGenerateNewHuman();
	bool isDoneGenerateNewHuman;

	cocos2d::Label* _scoreHuman;
	int _humanIntscore;
	
	// Status Label
	cocos2d::Label* _youWin;
	cocos2d::Label* _youGameOver;

	// game counter
	cocos2d::Label* _timerUI;
	int _initalGameTime;

	void updateTimer(float dt);


	void doResetGame();
	void doStopGame();
	void doIncreaseDifficulty();

public:
	virtual bool init();
	virtual void update(float dt);

	void doInitProperties();
	void doInitGraphics();
	void doInitEvents();
	void doInitAudios();

	bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
	void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event);
	void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);

	// handle clicks
	void onMouseBegan(cocos2d::Event* event);
	void onMouseMoved(cocos2d::Event* event);
	void onMouseEnded(cocos2d::Event* event);

	void menuCloseCallback(cocos2d::Ref* sender);
	void menuResetCallback(cocos2d::Ref* sender);

};


#endif // !__GAMELAYER_H__
