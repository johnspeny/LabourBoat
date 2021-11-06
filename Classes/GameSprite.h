#ifndef __GAMESPRITE_H__
#define __GAMESPRITE_H__

#include "cocos2d.h"

class GameSprite : public cocos2d::Sprite
{
public:
    CC_SYNTHESIZE(cocos2d::Vec2, _nextPosition, NextPosition);
    CC_SYNTHESIZE(cocos2d::Vec2, _movingVector, MovingVector);

    cocos2d::Touch* _touch;

    //void setTouch(cocos2d::Touch* _touch);



    GameSprite();
    ~GameSprite();

    void setPosition(const cocos2d::Vec2& position) override;

    float getRadius() const;
};


#endif // !__GAMESPRITE_H__
