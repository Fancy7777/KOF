//
//  GamePlayScene.h
//  KOF
//
//  Created by Dongtao Yu on 6/09/2015.
//
//

#ifndef __KOF__GamePlayScene__
#define __KOF__GamePlayScene__

#include "PhotonMultiplayer.hpp"

#include <stdio.h>
#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "CocosGUI.h"


#include "Definitions.h"
#include "LoadingLayer.h"
#include "MultiplayerCallback.h"
#include "Fighter.h"
#include "Camera2d.h"

#include "ChooseRoomScene.h"

#include "SneakyJoystick.h"
#include "SneakyJoystickSkinnedBase.h"
#include "SneakyButton.h"
#include "SneakyButtonSkinnedBase.h"


class GamePlayScene : public cocos2d::Layer, public MultiplayerCallback
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // implement the "static create()" method manually
    CREATE_FUNC(GamePlayScene);
    
    CC_SYNTHESIZE(std::string, playerCharacter, PlayerCharacter);
    CC_SYNTHESIZE(std::string, opponentCharacter, OpponentCharacter);
    
    CC_SYNTHESIZE(Fighter*, player, Player);
    CC_SYNTHESIZE(Fighter*, opponent, Opponent);
    CC_SYNTHESIZE(cocos2d::Sprite*, background, Background);
    
    
    CC_SYNTHESIZE(SneakyButton*, buttonA, ButtonA);
    CC_SYNTHESIZE(SneakyButton*, buttonB, ButtonB);
    CC_SYNTHESIZE(SneakyButton*, buttonC, ButtonC);
    CC_SYNTHESIZE(SneakyButton*, buttonD, ButtonD);
    CC_SYNTHESIZE(int, accumilatedTime, AccumilatedTime);
    CC_SYNTHESIZE(int, prevOperation, PrevOperation);
    CC_SYNTHESIZE(cocos2d::PhysicsWorld*, world, World);
    CC_SYNTHESIZE(bool, isGameOver, isGameOver);
    
    unsigned long lockstepId;
    int gameFrame;
    command_t prevCommand;
    std::deque<command_t> currentCommands;
    std::deque<command_t> nextCommands;
    std::deque<command_t> nextnextCommands;
    
private:
    Camera2d* camera;
    bool isCountDownStart;
    
    
    SneakyJoystick* joystick;
    
    void startGame();
    void PauseClicked(Ref*, ui::Widget::TouchEventType);
    void ResumeClicked(Ref*, ui::Widget::TouchEventType);
    void MenuClicked(Ref*, ui::Widget::TouchEventType);
    
    void createJoystick();
    
    SneakyButton* createButtons(std::string, std::string, Vec2);
    
    void createBackgroundAnimation();
    
    
    void startCountDown();
    void countDownTask(float);
    void endCountDown();
    
    
    void update(float);
    void gameFrameTurn();
    void processCommand(command_t);
    bool lockStepTurn();
    command_t processInput();
    
    
    void onLeaveRoomDone();
    void leaveRoomEventAction();
    void customEventAction(command_t);
    
    void updateMusicSlideBar(Ref* pSender, cocos2d::ui::Slider::EventType type);
    void updateEffectSlideBar(Ref* pSender, ui::Slider::EventType type);
    void updateCheckBox(Ref *pSender,cocos2d::ui::CheckBox::EventType type);
    
    void gameOver(float);
    
};


#endif /* defined(__KOF__GamePlayScene__) */
