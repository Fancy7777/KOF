//
//  Fighter.h
//  KOF
//
//  Created by Dongtao Yu on 11/09/2015.
//
//

#ifndef __KOF__Fighter__
#define __KOF__Fighter__

#include <stdio.h>
#include "cocos2d.h"
#include "Definitions.h"
#include "CocosGUI.h"
#include "format.h"
#include "GameHelper.h"
#include "SimpleAudioEngine.h"

class Fighter
{
    
public:
    Fighter(cocos2d::Sprite*, cocos2d::ui::LoadingBar*, std::string, bool);
    
    CC_SYNTHESIZE(cocos2d::Sprite*, sprite, Sprite);
    CC_SYNTHESIZE(Fighter*, opponent, Opponent);
    CC_SYNTHESIZE(std::string, name, Name);
    CC_SYNTHESIZE(cocos2d::ui::LoadingBar*, health, health);
    CC_SYNTHESIZE(bool, isLeft, IsLeft);
    CC_SYNTHESIZE(bool, isDie, IsDie);
    CC_SYNTHESIZE(bool, isHealthChanged, IsHealthChanged);
    
    void processCommand(command_t);
    void squat();
    void squat_down();
    void squat_hit();
    void squat_moveback();
    void squat_moveforward();
    void squat_up();
    
    void stand();
    void stand_hit();
    void stand_jump(int);
    void stand_moveback();
    void stand_moveforward();
    
    void start();
    void win();
    void die();
    
    
    void kick1();
    void kick2();
    
    void punch1();
    void punch2();
    
    void setHealthPercentage(float);
    float getHealthPercentage();
    
    void update(float);
    
    
    void setPosition(cocos2d::Vec2);
    cocos2d::Vec2 getPosition();
    
    cocos2d::Vec2 getScreenPosition();
    cocos2d::Rect getBoundingBox();
    cocos2d::Node* getParent();
    
    
    bool isStand();
    bool isSquat();
    bool isActionStoppable();
    bool isHit();
    
    bool isNextAction();
    bool checkBoundary(cocos2d::Vec2);
    
    
};


#endif /* defined(__KOF__Fighter__) */