//
//  ChooseRoomScene.h
//  KOF
//
//  Created by Dongtao Yu on 16/08/2015.
//
//

#ifndef __KOF__ChooseRoomScene__
#define __KOF__ChooseRoomScene__

//#include <boost/format.hpp>
#include "MainMenuScene.h"
#include "format.h"

#include <stdio.h>
#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "CocosGUI.h"

#include "Definitions.h"
#include "CreateRoomScene.h"
#include "ChooseCharacterScene.h"
#include "MultiplayerCallback.h"


class ChooseRoomScene : public Layer, public MultiplayerCallback
{
public:
    
    
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();

    // implement the "static create()" method manually
    CREATE_FUNC(ChooseRoomScene);
    
private:
    
    bool isFirstTimeLaunch;
    
    void GotoMainMenuScene(Ref*, cocos2d::ui::Widget::TouchEventType);
    
    void GotoCreateRoomScene(Ref*, cocos2d::ui::Widget::TouchEventType);
    
    void OnSelectedItem(Ref* pSender, cocos2d::ui::Widget::TouchEventType);
    
    void buttonQuickJoinClicked(Ref* pSender, cocos2d::ui::Widget::TouchEventType);
    
    // RoomRequestListner
    void onRoomListUpdate();
    void createRoomListEntry(std::string roomId,
                             int nonUsers,
                             int maxUsers,
                             std::map<std::string, std::string> properties);
    
    void onJoinRoomDone();
    void onJoinRoomFailed();
    // Search Roomt
    void SearchRoom(Ref*, cocos2d::ui::Widget::TouchEventType);
    
    void update(float);

};

#endif /* defined(__KOF__ChooseRoomScene__) */
