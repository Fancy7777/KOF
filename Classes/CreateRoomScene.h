//
//  CreateRoomScene.h
//  KOF
//
//  Created by Dongtao Yu on 25/08/2015.
//
//

#ifndef __KOF__CreateRoomScene__
#define __KOF__CreateRoomScene__

#include "PhotonMultiplayer.hpp"

#include <stdio.h>
#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "CocosGUI.h"

#include "Definitions.h"
#include "LoadingLayer.h"
#include "MultiplayerCallback.h"
#include "ChooseRoomScene.h"
#include "ChooseCharacterScene.h"


class CreateRoomScene : public cocos2d::Layer, public MultiplayerCallback
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // implement the "static create()" method manually
    CREATE_FUNC(CreateRoomScene);
private:
    Ref* backgroundSelected;
    
    void update(float);
    
    void CheckboxSelectedChanged(Ref*, cocos2d::ui::CheckBox::EventType);
    void GotoChooseRoomScene(Ref*, ui::Widget::TouchEventType);
    void RemoveSelectedBorder(Ref*);
    void ShowSelectedBorder(Ref*);
    void CreateRoom(Ref*, ui::Widget::TouchEventType);
    void BackgroundSelectedChanged(Ref*, ui::Widget::TouchEventType);
    
    
    void onCreateRoomDone();
};

#endif /* defined(__KOF__CreateRoomScene__) */
