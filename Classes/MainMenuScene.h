//
//  MainMenuScene.h
//  KOF
//
//  Created by Dongtao Yu on 12/08/2015.
//
//

#ifndef __KOF__MainMenuScene__
#define __KOF__MainMenuScene__


#include "PhotonMultiplayer.hpp"


#include "cocos2d.h"

#include "SonarFrameworks.h"

#include "definitions.h"
#include "HelpScene.h"
#include "SettingScene.h"
#include "LoadingLayer.h"
#include "GameHelper.h"
#include "MultiplayerCallback.h"
#include "ChooseRoomScene.h"


class MainMenuScene : public cocos2d::Layer, public MultiplayerCallback
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    void update(float);
    
    // implement the "static create()" method manually
    CREATE_FUNC(MainMenuScene);
    
private:
    //og to choose room scene
    void GoToChooseRoomScene(cocos2d::Ref*, ui::Widget::TouchEventType type);
    
    //go to help scene
    void GoToHelpScene(cocos2d::Ref*, ui::Widget::TouchEventType type);
    
    //go to setting scene
    void GoToSettingScene(cocos2d::Ref*, ui::Widget::TouchEventType type);
    
    //go to leader board scene
    void GotoLeaderBoardScene(cocos2d::Ref*, ui::Widget::TouchEventType type);
    
    //make a facebook post
    void facebookClicked(cocos2d::Ref*, ui::Widget::TouchEventType type);
    
    //make a twitter post
    void twitterClicked(cocos2d::Ref*, ui::Widget::TouchEventType type);
    
    
    // ConnectionRequestListener
    void onConnectDone();
};

#endif /* defined(__KOF__MainMenuScene__) */
