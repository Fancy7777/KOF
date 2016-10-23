//
//  GameHelper.h
//  KOF
//
//  Created by Dongtao Yu on 6/09/2015.
//
//

#ifndef __KOF__GameHelper__
#define __KOF__GameHelper__

#include <stdio.h>
#include <math.h>
#include "cocos2d.h"

//#include "Fighter.h"

class GameHelper{
    
public:
    static std::vector<std::string> split(std::string, char);
    static std::string randomString(size_t);
    static std::string randomIntString(size_t);
    static double vectorToDegree(cocos2d::Point);
//    static cocos2d::Vec2 toBackgroundCoord(cocos2d::Sprite*, Fighter*);
    
};
#endif /* defined(__KOF__GameHelper__) */
