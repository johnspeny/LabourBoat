//
// Created by okker on 4/8/20.
//

#ifndef PROJ_ANDROID_GAMEVARS_H
#define PROJ_ANDROID_GAMEVARS_H

#include "cocos2d.h"
#include "box2d/box2d.h"

/* Turned on when debug is set to true */
//#if (CC_BOX2D_DEBUG)
//
//#endif

class GameVars {
public:
    // b2d world defaults
    static float PTM_Ratio;
    static float gravityX;
    static float gravityY;
    static float metersHeight;

    //b2d body defaults
    static b2BodyType defaultBody;
    static float defaultFriction;
    static float defaultRestitution;

    static void initVars();
};


#endif //PROJ_ANDROID_GAMEVARS_H
