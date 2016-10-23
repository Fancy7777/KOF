//
//  Camera.cpp
//  KOF
//
//  Created by Dongtao Yu on 11/09/2015.
//
//

#include "Camera2d.h"

USING_NS_CC;

Camera2d::Camera2d(Fighter* player, Fighter* opponent, Sprite* background)
{
    this->player = player;
    this->opponent = opponent;
    this->background = background;
    
    
}

void Camera2d::update(float dt)
{
    this->playerScreenPos = player->getScreenPosition();
    this->opponentScreenPos = opponent->getScreenPosition();

    Size visibleSize = Director::getInstance()->getWinSize();
    
    //get mid poisiton
    auto mid = background->convertToNodeSpace(Vec2(visibleSize.width / 2, visibleSize.height / 2));
    
    auto toPlayer = mid.x - player->getPosition().x;
    auto toOpponent = mid.x - opponent->getPosition().x;
    
    //move background image when the position between two characters is smaller than screen width
    //not move background when the position between two characters is same as the screen width
    if(std::signbit(toPlayer) != std::signbit(toOpponent))
    {
        auto displacement = (toPlayer + toOpponent) / 2;
        if (player->getPosition().x < opponent->getPosition().x)
        {
            if(toPlayer > toOpponent)
                moveBackground(displacement*this->background->getScaleX());
            else if(toPlayer < toOpponent)
                moveBackground(-displacement*this->background->getScaleX());
        }
        else
        {
            if(toPlayer > toOpponent)
                moveBackground(-displacement*this->background->getScaleX());
            else if(toPlayer < toOpponent)
                moveBackground(+displacement*this->background->getScaleX());
        }
    }
    else
    {
        auto displacement = std::abs(toPlayer + toOpponent) / 2;
        if(std::signbit(toPlayer))
        {
            moveBackground(-displacement*this->background->getScaleX());
        }else
        {
            moveBackground(+displacement*this->background->getScaleX());
        }
    }
}

void Camera2d::moveBackground(float displacement)
{
    auto visibleSize = Director::getInstance()->getWinSize();
    auto box = background->getBoundingBox();
    if (box.origin.x + displacement > 0 || box.origin.x + displacement + box.size.width < visibleSize.width){
        return;
    }
    
    Vec2 currentPosition = background->getPosition();
    Vec2 newPosition = Vec2(currentPosition.x + displacement, currentPosition.y);
    background->setPosition(newPosition);
    
}

