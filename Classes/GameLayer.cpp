#include "GameLayer.h"
#include <iostream>
#include <string>

using namespace cocos2d;

USING_NS_CC;


Vec2 GameLayer::moveTowards(Vec2 current, Vec2 target, float maxDelta)
{
	Vec2 a = target - current;

	float magnitude = sqrt(a.x * a.x + a.y * a.y);

	if (magnitude <= maxDelta || maxDelta == 0.0f)
	{
		return target;
	}
	Vec2 directionToTarget = Vec2(a.x/magnitude, a.y/magnitude);
	return current + directionToTarget * maxDelta;
}

float GameLayer::distanceBetween(cocos2d::Vec2 current, cocos2d::Vec2 target)
{
	Vec2 a = target - current;

	float magnitude = sqrt(a.x * a.x + a.y * a.y);

	return magnitude;
}

void GameLayer::doGenerateNewCreature()
{
	if (_fallingCreatures.size() >= 1)
	{
		return;
	}

	// add creatures from pool to falling objects(creatures falling)
	auto creatureSprite = _creaturePool.at(_creatureIndexPool);
	_creatureIndexPool++;

	if (_creatureIndexPool == _creaturePool.size())
	{
		_creatureIndexPool = 0;
	}

	// stop all node actions
	creatureSprite->stopAllActions();

	// make visible creature
	creatureSprite->setVisible(true);

	// position of creatures
	creatureSprite->setPosition(Vec2(_origin.x + _screenSize.width * random<float>(0.1f, 0.9f), _screenSize.height));

	// move creature downwards

	//auto creatureMove = Sequence::create(MoveTo::create(speedOfCreature, Vec2(_boat->getPositionX(), _boat->getPositionY())), CallFunc::create(std::bind(&GameLayer::onFallingCreatureDone, this)), nullptr);
	//creatureSprite->runAction(creatureMove);

	// add the creatures to a falling creatures vector
	_fallingCreatures.pushBack(creatureSprite);

	isDoneGenerateNewCreature = true;
}

void GameLayer::onFallingCreatureDone()
{
	log("Creature Reached down");
}

void GameLayer::doResetGame()
{
	// creature
	currentHealth = 100.0f;
	totalHealth = 100.0f;
	speedOfCreature = 0.5f;
	intervalOfCreature = 3.0f;
	timeOfCreature = intervalOfCreature;

	//pollutant
	currentPHealth = 100.0f;
	totalPHealth = 100.0f;
	speedOfPollutant = 10.0f;
	intervalOfPollutant = 3.0f;
	timeOfPollutant = intervalOfPollutant;

	// wood
	speedOfWood = 9.0f;
	intervalOfWood = 9.0f;
	timeOfWood = intervalOfCreature;

	// Human
	speedOfHuman = 9.0f;
	intervalOfHuman = 10.0f;
	timeOfHuman = intervalOfHuman;

	

}

void GameLayer::doStopGame()
{
	
	_playing = false;

	// show gameOver label
	_youGameOver->setVisible(true);
}

void GameLayer::doGenerateNewWood()
{
	if (_fallingWood.size() >= 15)
	{
		return;
	}

	auto woodSprite = _woodPool.at(_woodIndexPool);
	_woodIndexPool++;

	if (_woodIndexPool == _woodPool.size())
	{
		_woodIndexPool = 0;
	}


	woodSprite->stopAllActions();
	woodSprite->setVisible(true);
	woodSprite->setPosition(Vec2(
		_origin.x + _screenSize.width * random<float>(0.1f, 0.9f),
		_screenSize.height + woodSprite->getContentSize().height * 0.5f));

	woodSprite->runAction(Sequence::create(
		MoveTo::create(speedOfWood, Vec2(_origin.x + _screenSize.width * random<float>(0.1f, 0.9f), bridge->getPositionY())),
		nullptr));

	_fallingWood.pushBack(woodSprite);

	isDoneGenerateNewWood = true;
}

void GameLayer::doIncreaseDifficulty()
{
}

bool GameLayer::init() {
	if (!Scene::init())
	{
		return false;
	}

	doInitProperties();
	doInitGraphics();
	doInitEvents();
	doInitAudios();

	return true;
}

void GameLayer::update(float dt)
{
	if (!_playing)
	{
		return;
	}

	// =========================
	// pollutant update
	// --------------
	timeOfPollutant -= dt;

	if (timeOfPollutant <= 0)
	{
		doGenerateNewPollutant();
		timeOfPollutant = intervalOfCreature + 6.0f;
	}


	// human update
	// --------------
	timeOfHuman -= dt;

	if (timeOfHuman <= 0)
	{
		doGenerateNewHuman();
		timeOfHuman = intervalOfHuman + 30.0f;
	}

	// wood update
	// --------------
	timeOfWood -= dt;

	if (timeOfWood <= 0)
	{
		doGenerateNewWood();
		timeOfWood = intervalOfWood + 10.0f;
	}


	// =========================
	// creature update
	// --------------
	timeOfCreature -= dt;
	
	if (timeOfCreature <= 0)
	{
		doGenerateNewCreature();
		timeOfCreature = intervalOfCreature + 20.0f;
	}

	// calulate health of creature
	

	if (isDoneGenerateNewCreature)
	{
		auto fC = _fallingCreatures.at(_fallCreatureIndex);
		_fallCreatureIndex++;
		if (_fallCreatureIndex == _fallingCreatures.size())
		{
			_fallCreatureIndex = 0;
		}
		
		// health bar for creature
		Vector<Node*> nodes = fC->getChildren();
		int nodesToDeleteInHealth = nodes.size() * (1.0f - (float)currentHealth / (float)totalHealth);

		float healthPercentage = ((float) currentHealth/(float)totalHealth) * 100;

		int stage = 0;

		// health stage
		if (healthPercentage > 75.0 && healthPercentage <= 100)
		{
			stage = 0;
		}

		else if (healthPercentage > 50.0 && healthPercentage <= 75.0)
		{
			stage = 1;
		}

		else if (healthPercentage > 25.0 && healthPercentage <= 50)
		{
			stage = 2;
		}
		
		else if (healthPercentage > 0.0 && healthPercentage <= 25.0)
		{
			stage = 3;
		}

		for (size_t i = 0; i < nodes.size(); i++)
		{
			Sprite* tmp = (Sprite*)nodes.at(i);
			switch (stage)
			{
			case 0:
				tmp->setColor(Color3B(200, 200, 200)); break;
			case 1:
				tmp->setColor(Color3B(150, 150, 150)); break;
			case 2:
				tmp->setColor(Color3B(50, 50, 50)); break;
			case 3:
				tmp->setColor(Color3B(255, 0, 0));
				//log("Game Over");
				//_playing= false;
				fC->setVisible(false);
				currentHealth = 100.0f;
				totalHealth = 100.0f;
				_youWin->setVisible(true);
				_youGameOver->setVisible(false);
				
				break;
			default:
				break;
			}
		}


		// creature hits bridge
		if (fC->getPositionY() <= bridge->getPositionY() && fC->isVisible())
		{
			//log("Pollutant hit bridge");
			//log("Pollutant pos %f", fC->getPositionY());
			//log("bridge pos %f", bridge->getPositionY());

			currentPHealth -= 20 * dt;

		}

		if (distanceBetween(fC->getPosition(), _boat->getPosition()) == 0){
			_boat->setVisible(false);
			fC->setVisible(false);
			doStopGame();
			AudioEngine::play2d("WAV_20211101_144219747.wav");
		}
		
		
		//_nextPosition = moveTowards(fC->getPosition(), _boat->getPosition(), 80.0f * dt);
		Vec2 toFollow;
		if (bridge->isVisible()){
			toFollow = distanceBetween(fC->getPosition(), bridge->getPosition()) <=
					   distanceBetween(fC->getPosition(), _boat->getPosition()) ? moveTowards(fC->getPosition(), bridge->getPosition(), 80.0f * dt) : moveTowards(fC->getPosition(), _boat->getPosition(), 80.0f * dt);

		}else{
			toFollow = moveTowards(fC->getPosition(), _boat->getPosition(), 80.0f * dt);

		}
//		Vec2 toFollow = distanceBetween(fC->getPosition(), bridge->getPosition()) <=
//			distanceBetween(fC->getPosition(), _boat->getPosition()) ? moveTowards(fC->getPosition(), bridge->getPosition(), 80.0f * dt) : moveTowards(fC->getPosition(), _boat->getPosition(), 80.0f * dt);

		fC->setPosition(toFollow);

		float boatSize = fC->getContentSize().width * 0.5f - _boat->getContentSize().width;
		//log("Boat Size == %f", boatSize);
		if (fC->getPositionY() - fC->getContentSize().height * 0.5f < _boat->getPositionY() + _boat->getContentSize().height * 0.5f &&
			fC->getPositionY() + fC->getContentSize().height * 0.5f > _boat->getPositionY() - _boat->getContentSize().height * 0.5f &&
			fC->getPositionX() + fC->getContentSize().width * 0.5f > _boat->getPositionX() - _boat->getContentSize().width * 0.5f &&
			fC->getPositionX() - fC->getContentSize().width * 0.5f < _boat->getPositionX() + _boat->getContentSize().width * 0.5f
			) {

			//_boat->setColor(Color3B(100, 100, 100));
			//_boat->setOpacity(90);
			currentHealth -= 12 * dt;
			//log("Creature Health === %f", currentHealth);
			AudioEngine::play2d("WAV_20211101_144158718.wav");

		}
		else
		{
			//_boat->setOpacity(100);
			//_boat->setColor(Color3B(160, 156, 38));
		}

		// bridge 
		
	}

		
	// collision of bridge with boat
	if (_boat->getPositionY() - _boat->getContentSize().height * 0.5f < bridge->getPositionY())
	{
		//log("reached");
		_boat->setPositionY(bridge->getPositionY() + _boat->getContentSize().height * 0.5f);
	}

	// health for bridge
		// health bar for creature
	Vector<Node*> nodesP = bridge->getChildren();
	int nodesToDeleteInHealthP = nodesP.size() * (1.0f - (float)currentPHealth / (float)totalPHealth);

	float healthPercentageP = ((float)currentPHealth / (float)totalPHealth) * 100;

	//log("health =========%f", healthPercentageP);

	int stageP = 0;

	// health stage
	if (healthPercentageP > 75.0 && healthPercentageP <= 100)
	{
		stageP = 0;
	}

	else if (healthPercentageP > 50.0 && healthPercentageP <= 75.0)
	{
		stageP = 1;
	}

	else if (healthPercentageP > 25.0 && healthPercentageP <= 50)
	{
		stageP = 2;
	}

	else if (healthPercentageP > 0.0 && healthPercentageP <= 25.0)
	{
		stageP = 3;
	}

	for (size_t i = 0; i < nodesP.size(); i++)
	{
		Sprite* tmpP = (Sprite*)nodesP.at(i);
		switch (stageP)
		{
		case 0:
			tmpP->setColor(Color3B(200, 200, 200)); break;
		case 1:
			tmpP->setColor(Color3B(150, 150, 150)); break;
		case 2:
			tmpP->setColor(Color3B(50, 50, 50)); break;
		case 3:
			tmpP->setColor(Color3B(255, 0, 0));
			bridge->setVisible(false);
			//log("Game Over");
			break;
		default:
			break;
		}
	}

	// check to see if pollutants hit the bridge
	if (_pollutantPool.size() > 0 && isDoneGenerateNewPollutant==true)
	{
		auto fP = _fallingPollutant.at(_fallPollutantIndex);
		_fallPollutantIndex++;

		if (_fallPollutantIndex == _fallingPollutant.size())
		{
			_fallPollutantIndex = 0;
		}

		if (fP->isVisible())
		{

			if (fP->getPositionY() <= bridge->getPositionY() && bridge->isVisible())
			{
//				log("Pollutant hit bridge");
//				log("Pollutant pos %f", fP->getPositionY());
//				log("bridge pos %f", bridge->getPositionY());


				currentPHealth -= 5 * dt;


				firstCollided = fP;
				// create a new array and erase all those that have collided
				fP->setVisible(false);
				_pollutantCollided.pushBack(firstCollided);
	
			}else if (fP->getPositionY() <= bridge->getPositionY() && !bridge->isVisible()){
				firstCollided = fP;
				// create a new array and erase all those that have collided
				fP->setVisible(false);
				_pollutantCollided.pushBack(firstCollided);
				_opacityWater -= 5;
				log("water ==== %d", _opacityWater);
			}
		}	
		
	}


	if (_pollutantCollided.size() > 0)
	{

		//log("Deleted reached ========== ");
		
		//_pollutantCollided.eraseObject(pC);
		auto x =_pollutantCollided.at(_collidedPollutantIndex);
		_collidedPollutantIndex++;
		if (_collidedPollutantIndex == _pollutantCollided.size())
		{
			_collidedPollutantIndex = 0;
		}
		_pollutantCollided.eraseObject(x);
		_gameBatchNode->removeChild(x, true);

	}

	//log("Pollunatn size ======== %d", _pollutantCollided.size());


	// Human code ============================

	// check to see if human hit the bridge
	if (_humanPool.size() > 0 && isDoneGenerateNewHuman == true)
	{
		auto fH = _fallingHuman.at(_fallHumanIndex);
		_fallHumanIndex++;

		if (_fallHumanIndex == _fallingHuman.size())
		{
			_fallHumanIndex = 0;
		}

		if (fH->isVisible())
		{

			if (fH->getPositionY() - fH->getContentSize().height * 0.5f <= bridge->getPositionY())
			{
				//log("Human hit bridge");

				
				firstCollided = fH;
				// create a new array and erase all those that have collided
				fH->setVisible(false);
				_humanCollided.pushBack(firstCollided);

			}


			// if human hit boat
			if (fH->getPositionY() - fH->getContentSize().height * 0.5f < _boat->getPositionY() + _boat->getContentSize().height * 0.5f &&
				fH->getPositionY() + fH->getContentSize().height * 0.5f > _boat->getPositionY() - _boat->getContentSize().height * 0.5f &&
				fH->getPositionX() + fH->getContentSize().width * 0.5f > _boat->getPositionX() - _boat->getContentSize().width * 0.5f &&
				fH->getPositionX() - fH->getContentSize().width * 0.5f < _boat->getPositionX() + _boat->getContentSize().width * 0.5f
				)
			{
				//log("Collision with boatttttttttttttttttt");
				_humanIntscore += 1;
				_scoreHuman->setString(StringUtils::toString<int>(_humanIntscore));


				fH->setVisible(false);
				_humanCollided.eraseObject(fH);
				_gameBatchNode->removeChild(fH, true);
			}
		}

	}


	if (_humanCollided.size() > 0)
	{

		//log("Deleted reached ========== ");

		//_pollutantCollided.eraseObject(pC);
		auto x = _humanCollided.at(_collidedHumanIndex);
		_collidedHumanIndex++;
		if (_collidedHumanIndex == _humanCollided.size())
		{
			_collidedHumanIndex = 0;
		}
		_humanCollided.eraseObject(x);
		_gameBatchNode->removeChild(x, true);

	}

	//log("Human size ======== %d", _humanCollided.size());




	// Wood code ============================

	// check to see if human hit the bridge
	if (_woodPool.size() > 0 && isDoneGenerateNewWood == true)
	{
		auto fW = _fallingWood.at(_fallWoodIndex);
		_fallWoodIndex++;

		if (_fallWoodIndex == _fallingWood.size())
		{
			_fallWoodIndex = 0;
		}

		if (fW->isVisible())
		{

			if (fW->getPositionY() - fW->getContentSize().height * 0.5f <= bridge->getPositionY())
			{
				//log("Wood hit bridge");


				firstCollided = fW;
				// create a new array and erase all those that have collided
				fW->setVisible(false);
				//_humanCollided.pushBack(firstCollided);
				_woodCollided.eraseObject(fW);
				_gameBatchNode->removeChild(fW, true);

			}


			// if human hit boat
			if (fW->getPositionY() - fW->getContentSize().height * 0.5f < _boat->getPositionY() + _boat->getContentSize().height * 0.5f &&
				fW->getPositionY() + fW->getContentSize().height * 0.5f > _boat->getPositionY() - _boat->getContentSize().height * 0.5f &&
				fW->getPositionX() + fW->getContentSize().width * 0.5f > _boat->getPositionX() - _boat->getContentSize().width * 0.5f &&
				fW->getPositionX() - fW->getContentSize().width * 0.5f < _boat->getPositionX() + _boat->getContentSize().width * 0.5f
				)
			{
				//log("Wood Collision with boatttttttttttttttttt");

				_woodIntscore += 1;
				_scoreWood->setString(StringUtils::toString<int>(_woodIntscore));

				fW->setVisible(false);
				_woodCollided.eraseObject(fW);
				_gameBatchNode->removeChild(fW, true);
			}
		}

	}

	// update boat position
	//_boat->setPosition(_boat->getNextPosition());

	// water update
	if (water->getOpacity() < 50){
		doStopGame();
	}

	water->setOpacity(_opacityWater);

}

void GameLayer::doInitProperties()
{
	// load art into memory
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("sprite_sheet.plist");

	// sprite batch to access the spritesheet
	_gameBatchNode = SpriteBatchNode::create("sprite_sheet.png");
	this->addChild(_gameBatchNode, 1);

	// screen size
	_screenSize = Director::getInstance()->getVisibleSize();
	_origin = Director::getInstance()->getVisibleOrigin();

	_playing = false;

	_collidedPollutantIndex = 0;


	_humanIndexPool = 0;
	_fallHumanIndex = 0;
	_collidedHumanIndex = 0;

	_woodIndexPool = 0;
	_fallWoodIndex = 0;
	_collidedWoodIndex = 0;


	_woodIntscore = 0;
	_humanIntscore = 0;

	currentHealth = 100.0f;

	_opacityWater = 100;
	
}

void GameLayer::doInitGraphics()
{

	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto origin      = Director::getInstance()->getVisibleOrigin();
	auto safeArea = Director::getInstance()->getSafeAreaRect();
	auto safeOrigin = safeArea.origin;
	auto closeItem = MenuItemImage::create("CloseNormal.png", "CloseSelected.png",
										   CC_CALLBACK_1(GameLayer::menuCloseCallback, this));

	if (closeItem == nullptr || closeItem->getContentSize().width <= 0 || closeItem->getContentSize().height <= 0)
	{
		//problemLoading("'CloseNormal.png' and 'CloseSelected.png'");
	}
	else
	{
		float x = safeOrigin.x + safeArea.size.width - closeItem->getContentSize().width / 2;
		float y = safeOrigin.y + closeItem->getContentSize().height / 2;
		closeItem->setPosition(Vec2(x, y));
	}

	auto menu = Menu::create(closeItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);


	// ===========================================
	// Background image
	// ----------
	auto bg = Sprite::create("bg.png");
	//auto bg = Sprite::create("bg.png");
	bg->setPosition(Vec2(_origin.x + _screenSize.width * 0.5f, _screenSize.height * 0.5f));
	bg->setContentSize(Size(_screenSize.width, _screenSize.height));
	this->addChild(bg, -10);


	// ===========================================
	// To bush image
	// ----------
	auto bushLeft = Sprite::createWithSpriteFrameName("sidebush.png");
	bushLeft->setAnchorPoint(Vec2(0.5f, 0.0f));
	bushLeft->setPosition(Vec2(_origin.x + bushLeft->getContentSize().width * 1/8.0f, 0.0f));
	bushLeft->setContentSize(Size(bushLeft->getContentSize().width, _screenSize.height));
	this->addChild(bushLeft, -5);

	auto bushRight = Sprite::createWithSpriteFrameName("sidebush.png");
	bushRight->setAnchorPoint(Vec2(0.5f, 0.0f));
	bushRight->setFlippedX(true);
	bushRight->setPosition(Vec2(_origin.x + _screenSize.width - bushRight->getContentSize().width * 1 / 8.0f, 0.0f));
	bushRight->setContentSize(Size(bushRight->getContentSize().width, _screenSize.height));
	this->addChild(bushRight, -5);


	// ===========================================
	// Sample image
	// ----------
	//auto sg = Sprite::create("froggy.png");
	////auto bg = Sprite::create("bg.png");
	//sg->setPosition(Vec2(_origin.x + _screenSize.width * 0.5f, _screenSize.height * 0.5f));
	//this->addChild(sg, -10);
	

	// ===========================================
	// Creature
	// ----------

	_creatureIndexPool = 0;
	_fallCreatureIndex = 0;



	for (size_t i = 0; i < 1; i++)
	{
		auto creature = Sprite::createWithSpriteFrameName("froggy.png");
		//creature->setTextureRect(Rect(0, 0, 40, 40));
		//creature->setColor(Color3B(88, 211, 16));
		creature->setVisible(false);
		_gameBatchNode->addChild(creature,kMiddleground);
		_creaturePool.pushBack(creature);

		auto size = creature->getContentSize();

		for (size_t i = 0; i < 24; i++)
		{
			auto healthBar = Sprite::createWithSpriteFrameName("box.png");
			healthBar->setTextureRect(Rect({ 57,0 }, { 10,10 }));
			healthBar->setColor(Color3B(50, 50, 50));
			healthBar->setPosition(Vec2(size.width * 0.5f, size.height * 1.0f + healthBar->getContentSize().height));
			creature->addChild(healthBar, 10, kCreatureHealthBar);
		}
	}

	// ===========================================
	 

	// ===========================================
	// Boat
	// -----------
	_boat = (GameSprite*)GameSprite::createWithSpriteFrameName("boat.png");
	_boat->setVisible(true);
	//_boat->setTextureRect(Rect(0, 0, 30, 30));
	//_boat->setColor(Color3B(160, 156, 38));
	//_boat->setOpacity(100);
	_boat->setPosition(Vec2(_origin.x + _screenSize.width * 0.5f, _screenSize.height * 0.25f));
	_gameBatchNode->addChild(_boat, kForeground);


	// ===========================================

	// ===========================================
	// Bridge
	// ----------
	bridge = Sprite::createWithSpriteFrameName("woodbridge.png");
	//bridge->setTextureRect(Rect(0, 0, _screenSize.width, 20));
	//bridge->setColor(Color3B(255, 0, 0));
	bridge->setPosition(Vec2(_origin.x + _screenSize.width * 0.5f, _screenSize.height * 0.2f));
	bridge->setAnchorPoint(Vec2(0.5f, 1.0f));
	bridge->setVisible(false);
	_gameBatchNode->addChild(bridge, kMiddleground);

	auto size = bridge->getContentSize();

	for (size_t i = 0; i < 24; i++)
	{
		auto bridgehealthBar = Sprite::createWithSpriteFrameName("box.png");
		bridgehealthBar->setTextureRect(Rect({ 57,0 }, { 10,10 }));
		bridgehealthBar->setColor(Color3B(50, 250, 50));
		bridgehealthBar->setPosition(Vec2(size.width * 0.9f, size.height * 1.0f + bridgehealthBar->getContentSize().height));
		bridge->addChild(bridgehealthBar, 10, kBridgeHealthBar);
	}

	// =============================================
	
	// ===========================================
	// Pollutants
	// ----------
	
	_pollutantIndexPool = 0;
	_fallPollutantIndex = 0;

	for (size_t i = 0; i < 50; i++)
	{
		auto pollutant = Sprite::createWithSpriteFrameName("dirty.png");
		//pollutant->setTextureRect(Rect(0, 0, 15, 15));
		//pollutant->setColor(Color3B(0, 255, 0));
		pollutant->setVisible(false);
		pollutant->setAnchorPoint(Vec2(0.5f, 0.0f));
		_gameBatchNode->addChild(pollutant, kMiddleground);
		_pollutantPool.pushBack(pollutant);
	}

	// =============================================


	// ===========================================
	// Human
	// ----------
	for (size_t i = 0; i < 10; i++)
	{
		auto human = Sprite::createWithSpriteFrameName("man.png");
		//human->setTextureRect(Rect(0, 0, 25, 25));
		//human->setColor(Color3B(183, 193, 178));
		human->setVisible(false);
		_gameBatchNode->addChild(human, kMiddleground);
		_humanPool.pushBack(human);
	}


	// ===========================================
	// Wood
	// ----------
	for (size_t i = 0; i < 20; i++)
	{
		auto wood = Sprite::createWithSpriteFrameName("woodtimber.png");
		//wood->setTextureRect(Rect(0, 0, 25, 25));
		//wood->setColor(Color3B(127, 69, 26));

		wood->setVisible(false);
		_gameBatchNode->addChild(wood, kMiddleground);
		_woodPool.pushBack(wood);
	}


	// ===========================================
	// water
	// ----------
	water = Sprite::createWithSpriteFrameName("water.png");
	//water->setTextureRect(Rect(0, 0, _screenSize.width, 100));
	//water->setColor(Color3B(10, 255, 226));
	water->setPosition(Vec2(_origin.x + _screenSize.width * 0.5f, _screenSize.height * 0.2f));
	water->setAnchorPoint(Vec2(0.5f, 1.0f));
	water->setVisible(true);
	water->setOpacity(_opacityWater);
	_gameBatchNode->addChild(water, kBackground);

	// ===========================================
	// wood collected
	// ----------
	woodUI = Sprite::createWithSpriteFrameName("box.png");
	woodUI->setTextureRect(Rect({ 57,0 }, { 20,20 }));
	//woodUI->setColor(Color3B(160, 89, 38));
	woodUI->setPosition(Vec2(_origin.x + _screenSize.width * 0.2f + woodUI->getContentSize().width, _origin.y +_screenSize.height * 0.99f - woodUI->getContentSize().height));
	woodUI->setVisible(true);
	_gameBatchNode->addChild(woodUI, kForeground);


	_scoreWood = Label::createWithBMFont("font.fnt", "0");
	_scoreWood->setPosition(Vec2(woodUI->getPositionX(), _screenSize.height * 0.9f - _scoreWood->getContentSize().height));
	this->addChild(_scoreWood, 111);

	// ===========================================
	// human collected
	// ----------
	auto humanUI = Sprite::createWithSpriteFrameName("box.png");
	humanUI->setTextureRect(Rect({ 57,0 }, { 20,20 }));
	//humanUI->setColor(Color3B(183, 193, 178));
	humanUI->setPosition(Vec2(_origin.x + _screenSize.width * 0.15f, _screenSize.height * 0.99f - humanUI->getContentSize().height));
	humanUI->setVisible(true);
	_gameBatchNode->addChild(humanUI, kForeground);


	_scoreHuman = Label::createWithBMFont("font.fnt", "0");
	_scoreHuman->setPosition(Vec2(humanUI->getPositionX(), _screenSize.height * 0.9f - _scoreHuman->getContentSize().height));
	this->addChild(_scoreHuman, 111);



	// gameover
	_youGameOver = Label::createWithTTF("Game Over", "fonts/Marker Felt.ttf", 24);
	_youGameOver->setVisible(false);
	_youGameOver->setPosition(
			Vec2(_origin.x + _screenSize.width / 2, _origin.y + _screenSize.height * 0.5f - _youGameOver->getContentSize().height));
	// add the label as a child to this layer
	this->addChild(_youGameOver, 200);


	_youWin = Label::createWithTTF("You Win!", "fonts/Marker Felt.ttf", 24);
	_youWin->setVisible(false);
	_youWin->setPosition(
			Vec2(_origin.x + _screenSize.width / 2, _origin.y + _screenSize.height * 0.5f - _youWin->getContentSize().height));
	// add the label as a child to this layer
	this->addChild(_youWin, 200);


	// add reset button
	auto resetItem = MenuItemImage::create("return.png", "CloseSelected.png",
										   CC_CALLBACK_1(GameLayer::menuResetCallback, this));

	if (resetItem == nullptr || resetItem->getContentSize().width <= 0 || resetItem->getContentSize().height <= 0)
	{
		//problemLoading("'CloseNormal.png' and 'CloseSelected.png'");
	}
	else
	{
		float x = safeOrigin.x + safeArea.size.width - resetItem->getContentSize().width / 2;
		float y = safeOrigin.y + safeArea.size.height - resetItem->getContentSize().height / 2;
		resetItem->setPosition(Vec2(x, y));
	}

	auto menuR = Menu::create(resetItem, NULL);
	menuR->setPosition(Vec2::ZERO);
	this->addChild(menuR, 1);



}

void GameLayer::doInitEvents()
{
	// ===========================================
	// Mouse event
	// -----------
	auto _mouseListener = EventListenerMouse::create();

	_mouseListener->onMouseDown = CC_CALLBACK_1(GameLayer::onMouseBegan, this);
	_mouseListener->onMouseMove = CC_CALLBACK_1(GameLayer::onMouseMoved, this);
	_mouseListener->onMouseUp = CC_CALLBACK_1(GameLayer::onMouseEnded, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(_mouseListener, this);
	
	// ===========================================


	// ===========================================
	// Touch event
	// -----------
	auto _touchListenerP = EventListenerTouchOneByOne::create();

	_touchListenerP->onTouchBegan = CC_CALLBACK_2(GameLayer::onTouchBegan, this);
	_touchListenerP->onTouchMoved = CC_CALLBACK_2(GameLayer::onTouchMoved, this);
	_touchListenerP->onTouchEnded = CC_CALLBACK_2(GameLayer::onTouchEnded, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(_touchListenerP, this);

	// ===========================================


	this->scheduleUpdate();


}

void GameLayer::doInitAudios()
{
}

bool GameLayer::onTouchBegan(Touch* touch, cocos2d::Event* event)
{
	// start the game after clicking
	if (!_playing)
	{
		if (_youWin->isVisible())
		{
			_youWin->setVisible(false);
		}

		if (_youGameOver->isVisible())
		{
			_youGameOver->setVisible(false);
		}

		// reset game
		doResetGame();
		_playing = true;

		// log
		log("Playing");
	}

	if(_boat->getBoundingBox().containsPoint(touch->getLocation())){
		return true;
	}

	// click label
	if (std::stoi(_scoreWood->getString()) >= 1) {
		if (woodUI->getBoundingBox().containsPoint(touch->getLocation())) {
			bridge->setVisible(true);
			log("WWWWWWWWWWWWWWWWWWWWWWWWWWWW");
			_woodIntscore -= 1;
			_scoreWood->setString(StringUtils::toString<int>(_woodIntscore));
			currentPHealth = 100.0f;
			totalPHealth = 100.0f;
		}
	}

	return false;
}

void GameLayer::onTouchMoved(Touch* touch, cocos2d::Event* event)
{
	_boat->setPosition(_boat->getPosition() + touch->getDelta());
}

void GameLayer::onTouchEnded(Touch* touch, cocos2d::Event* event)
{

}



void GameLayer::onMouseBegan(cocos2d::Event* event)
{
	// start the game after clicking
	if (!_playing)
	{

		if (_youWin->isVisible())
		{
			_youWin->setVisible(false);
		}

		if (_youGameOver->isVisible())
		{
			_youGameOver->setVisible(false);
		}


		// reset game
		doResetGame();
		_playing = true;

		// log
		log("Playing");
	}
	else
	{
		
	}
		
}

void GameLayer::onMouseMoved(cocos2d::Event* event)
{
	
		// touch the boat and control it
		EventMouse* e = (EventMouse*)event;

		Point tap(e->getCursorX(), e->getCursorY());

		if (_boat->getBoundingBox().containsPoint(tap))
		{
			_boat->setPosition(tap);

		}

	
}

void GameLayer::onMouseEnded(cocos2d::Event* event)
{

}

void GameLayer::doGenerateNewPollutant()
{

	if (_fallingPollutant.size() >= 20)
	{
		return;
	}

	auto pollutantSprite = _pollutantPool.at(_pollutantIndexPool);
	_pollutantIndexPool++;

	if (_pollutantIndexPool == _pollutantPool.size())
	{
		_pollutantIndexPool = 0;
	}


	pollutantSprite->stopAllActions();
	pollutantSprite->setVisible(true);
	pollutantSprite->setPosition(Vec2(
		_origin.x + _screenSize.width * random<float>(0.1f, 0.9f),
		_screenSize.height + pollutantSprite->getContentSize().height * 0.5f));

	pollutantSprite->runAction(Sequence::create(
		MoveTo::create(speedOfPollutant, Vec2(_origin.x + _screenSize.width * random<float>(0.1f, 0.9f), _origin.y+ bridge->getPositionY())),
		nullptr));

	_fallingPollutant.pushBack(pollutantSprite);

	isDoneGenerateNewPollutant = true;
}


void GameLayer::doGenerateNewHuman()
{

	if (_fallingHuman.size() >= 3)
	{
		return;
	}

	auto humanSprite = _humanPool.at(_humanIndexPool);
	_humanIndexPool++;

	if (_humanIndexPool == _humanPool.size())
	{
		_humanIndexPool = 0;
	}


	humanSprite->stopAllActions();
	humanSprite->setVisible(true);
	humanSprite->setPosition(Vec2(
		_origin.x + _screenSize.width * random<float>(0.1f, 0.9f),
		_screenSize.height + humanSprite->getContentSize().height * 0.5f));

	humanSprite->runAction(Sequence::create(
		MoveTo::create(speedOfHuman, Vec2(_origin.x + _screenSize.width * random<float>(0.1f, 0.9f), bridge->getPositionY())),
		nullptr));

	_fallingHuman.pushBack(humanSprite);

	isDoneGenerateNewHuman = true;

}




void GameLayer::menuCloseCallback(Ref* sender)
{
	// Close the cocos2d-x game scene and quit the application
	Director::getInstance()->end();

	/*To navigate back to native iOS screen(if present) without quitting the application  ,do not use
     * Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm
     * as below*/

	// EventCustom customEndEvent("game_scene_close_event");
	//_eventDispatcher->dispatchEvent(&customEndEvent);
}


void GameLayer::menuResetCallback(Ref* sender)
{
	auto scene = utils::createInstance<GameLayer>();
	Director::getInstance()->replaceScene(scene);
}