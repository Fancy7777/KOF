//
//  SettingScene.h
//  KOF
//
//  Created by Dongtao Yu on 15/08/2015.
//
//

#ifndef __KOF__SettingScene__
#define __KOF__SettingScene__

#include "MainMenuScene.h"



#include <stdio.h>
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"
#include "Definitions.h"

// Scenes
//#include "MainMenuScene.h"

class SettingScene : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // implement the "static create()" method manually
    CREATE_FUNC(SettingScene);
    
private:
    
    void GotoMainMenuScene(Ref* pSender, cocos2d::ui::Widget::TouchEventType type);
    void updateMusicSlideBar(Ref* pSender, cocos2d::ui::Slider::EventType type);
    void updateEffectSlideBar(Ref* pSender, ui::Slider::EventType type);
    void updateCheckBox(Ref *pSender,cocos2d::ui::CheckBox::EventType type);
    
};


#endif /* defined(__KOF__SettingScene__) */
