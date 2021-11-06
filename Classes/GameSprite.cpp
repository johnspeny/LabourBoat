#include "GameSprite.h"

using namespace cocos2d;

GameSprite::~GameSprite() {

}

GameSprite::GameSprite() {
    _nextPosition = Vec2::ZERO;
    _movingVector = Vec2::ZERO;
    _touch = nullptr;
}

float GameSprite::getRadius() const {
    return this->getTexture()->getContentSize().width * 0.5f;
}

void GameSprite::setPosition(const cocos2d::Vec2 &position) {
    Sprite::setPosition(position);
    if (!_nextPosition.equals(position)){
        _nextPosition = position;
    }
}
