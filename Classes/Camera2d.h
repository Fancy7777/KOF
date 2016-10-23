//
//  Camera.h
//  KOF
//
//  Created by Dongtao Yu on 11/09/2015.
//
//

#ifndef __KOF__Camera__
#define __KOF__Camera__
#include "Fighter.h"
#include "cocos2d.h"

#include "Definitions.h"
#include "GameHelper.h"
#include <stdio.h>

#include <cmath>


class Camera2d
{
    
public:
    Camera2d(Fighter* player, Fighter* oppponent, cocos2d::Sprite* background);
    void update(float);
    
    
private:
    
    CC_SYNTHESIZE(Fighter*, player, Player);
    CC_SYNTHESIZE(Fighter*, opponent, Opponent);
    CC_SYNTHESIZE(cocos2d::Sprite*, background, Background);
    
    CC_SYNTHESIZE(cocos2d::Vec2, playerScreenPos, PlayerScreenPos);
    CC_SYNTHESIZE(cocos2d::Vec2, opponentScreenPos, OpponentScreenPos);
    
    void moveBackground(float);
    
};


#endif /* defined(__KOF__Camera__) */
