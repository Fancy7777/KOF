//
//  GameHelper.cpp
//  KOF
//
//  Created by Dongtao Yu on 6/09/2015.
//
//

#include "GameHelper.h"

USING_NS_CC;

std::vector<std::string> GameHelper::split(std::string str, char delimiter) {
    std::vector<std::string> internal;
    std::stringstream ss(str); // Turn the string into a stream.
    std::string tok;
    
    while(getline(ss, tok, delimiter)) {
        internal.push_back(tok);
    }
    
    return internal;
}


std::string GameHelper::randomString( size_t length )
{
    srand((unsigned)time(0));
    auto randchar = []() -> char
    {
        const char charset[] =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";
        const size_t max_index = (sizeof(charset) - 1);
        return charset[ rand() % max_index ];
    };
    std::string str(length,0);
    std::generate_n( str.begin(), length, randchar );
    return str;
}

std::string GameHelper::randomIntString( size_t length )
{
    srand((unsigned)time(0));
    auto randchar = []() -> char
    {
        const char charset[] =
        "0123456789";
        const size_t max_index = (sizeof(charset) - 1);
        return charset[ rand() % max_index ];
    };
    std::string str(length,0);
    std::generate_n( str.begin(), length, randchar );
    return str;
}

double GameHelper::vectorToDegree(cocos2d::Point point)
{
    auto angle = std::atan(point.y/point.x);
    
    if (angle > 0)
    {
        if (point.y < 0)
            angle = angle + M_PI;
    }
    else
    {
        if (point.x < 0)
            angle = angle + M_PI;
        else
            angle = angle + M_PI * 2;
    }
    
    return MATH_RAD_TO_DEG(angle);
}

