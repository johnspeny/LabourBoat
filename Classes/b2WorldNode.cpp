//
// Created by okker on 4/8/20.
//

#include "b2WorldNode.h"
#include "box2d/box2d.h"
#include "GameVars.h"

b2WorldNode::b2WorldNode():Node(){
    _world = nullptr;
    _debugDrawInst = nullptr;
    _PTM_Ratio = GameVars::PTM_Ratio;

    _velocityIterations = 3;
    _positionIterations = 3;
}


b2WorldNode::~b2WorldNode(){
    delete _world;
    _world = nullptr;
    delete _debugDrawInst;
    _debugDrawInst = nullptr;
}

bool b2WorldNode::init()
{
//#if (CC_BOX2D_DEBUG)
    _debugDrawInst = new CcxBox2dDebugDraw(_PTM_Ratio);

    uint32 flags = 0;
    flags += b2Draw::e_shapeBit;
//    flags += b2Draw::e_jointBit;
//    flags += b2Draw::e_aabbBit;
//    flags += b2Draw::e_pairBit;
    flags += b2Draw::e_centerOfMassBit;
    _debugDrawInst->SetFlags(flags);

   _world->SetDebugDraw(_debugDrawInst);

    return true;
}

bool b2WorldNode::init(float gravityX, float gravityY, float metersHeight) {
    _PTM_Ratio = Director::getInstance()->getVisibleSize().height / metersHeight;
    _world = new b2World(b2Vec2(gravityX, gravityY));

    // allow body to sleep
    _world->SetAllowSleeping(true);

    // turn on continuous physics testing
    _world->SetContinuousPhysics(true);

    return init();
}

b2WorldNode* b2WorldNode::create() {
    b2WorldNode* b2WorldNode1 = new (std::nothrow) b2WorldNode();
    if (b2WorldNode1 && b2WorldNode1->init(GameVars::gravityX, GameVars::gravityY, GameVars::PTM_Ratio)){
        b2WorldNode1->autorelease();
        return b2WorldNode1;
    }
    CC_SAFE_DELETE(b2WorldNode1);
    return nullptr;
}

b2WorldNode* b2WorldNode::create(float metersHeight) {
    b2WorldNode* b2WorldNode1 = new (std::nothrow) b2WorldNode();
    if (b2WorldNode1 && b2WorldNode1->init(GameVars::gravityX, GameVars::gravityY, metersHeight)){
        b2WorldNode1->autorelease();
        return b2WorldNode1;
    }
    CC_SAFE_DELETE(b2WorldNode1);
    return nullptr;
}

b2WorldNode* b2WorldNode::create(float gravityX, float gravityY) {
    b2WorldNode* b2WorldNode1 = new (std::nothrow) b2WorldNode();
    if (b2WorldNode1 && b2WorldNode1->init(gravityX, gravityY, GameVars::metersHeight)){
        b2WorldNode1->autorelease();
        return b2WorldNode1;
    }
    CC_SAFE_DELETE(b2WorldNode1);
    return nullptr;
}

b2WorldNode* b2WorldNode::create(float gravityX, float gravityY, float metersHeight) {
    b2WorldNode* b2WorldNode1 = new (std::nothrow) b2WorldNode();
    if (b2WorldNode1 && b2WorldNode1->init(gravityX, gravityY, metersHeight)){
        b2WorldNode1->autorelease();
        return b2WorldNode1;
    }
    CC_SAFE_DELETE(b2WorldNode1);
    return nullptr;
}

b2World* b2WorldNode::getb2World() {
    return _world;
}

float& b2WorldNode::getPTM() {
    return _PTM_Ratio;
}


//#if (CC_BOX2D_DEBUG)
void b2WorldNode::draw(cocos2d::Renderer *renderer, const cocos2d::Mat4 &transform, uint32_t parentFlags)
{
    Node::draw(renderer, transform, parentFlags);

    auto director = Director::getInstance();
    director->pushMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
    director->loadMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW, transform);

    _debugDrawInst->GetDrawNode()->clear();
    _world->DebugDraw();
    _debugDrawInst->GetDrawNode()->draw(renderer, transform, parentFlags);
    director->popMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
}
