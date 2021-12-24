//
// Created by okker on 4/8/20.
//

//#ifndef PROJ_ANDROID_BOX2DDEBUGDRAW_H
//#define PROJ_ANDROID_BOX2DDEBUGDRAW_H
#pragma once

#include "box2d/box2d.h"
#include "cocos2d.h"

using namespace cocos2d;

class CcxBox2dDebugDraw : public b2Draw {
public:
    CcxBox2dDebugDraw();
    CcxBox2dDebugDraw(float ratio);
    virtual ~CcxBox2dDebugDraw();

    void DrawPolygon(const b2Vec2* vertices, int vertexCount, const b2Color& color) override;
    void DrawSolidPolygon(const b2Vec2* vertices, int vertexCount, const b2Color& color) override;
    void DrawCircle(const b2Vec2& center, float radius, const b2Color& color) override;
    void DrawSolidCircle(const b2Vec2& center, float radius, const b2Vec2& axis, const b2Color& color) override;
    void DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color) override;
    void DrawTransform(const b2Transform& xf) override;
    void DrawPoint(const b2Vec2& p, float size, const b2Color& color) override;

    void setRatio(float ratio) { _ratio = ratio; }

    cocos2d::DrawNode* GetDrawNode() const { return _drawNode; }

protected:
    float _ratio;

    cocos2d::DrawNode* _drawNode = nullptr;

};


//#endif //PROJ_ANDROID_BOX2DDEBUGDRAW_H
