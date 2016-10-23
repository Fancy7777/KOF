//
//  SettingScene.cpp
//  KOF
//
//  Created by Dongtao Yu on 15/08/2015.
//
//

#include "SettingScene.h"

Scene* SettingScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = SettingScene::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool SettingScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        //unit test
        assert(Layer::init() == false);
        return false;
    }
    
    cocos2d::Size visibleSize = cocos2d::Director::getInstance()->getWinSize();
    cocos2d::Vec2 origin = cocos2d::Director::getInstance()->getVisibleOrigin();
    
    
    //TODO: help text
    auto node = CSLoader::createNode("Setting.csb");
    //unit test
    assert(node);
    ui::Button* buttonBack =  static_cast<ui::Button*>(node->getChildByName("buttonBack"));
    //unit test
    assert(buttonBack);
    
    buttonBack->addTouchEventListener(CC_CALLBACK_2(SettingScene::GotoMainMenuScene, this));
    this->addChild(node);
    
    //get the node of music slide bar
    ui::Slider* musicSlideBar = static_cast<ui::Slider*>(this->getChildByName("SettingScene")->getChildByName("sound_slidebar"));
    //unit test
    assert(musicSlideBar);
    
    
    //add event listener to call back the function
    musicSlideBar->addEventListener(CC_CALLBACK_2(SettingScene::updateMusicSlideBar, this));
    //save the status of current music bar
    musicSlideBar->setPercent(CocosDenshion::SimpleAudioEngine::getInstance()->getBackgroundMusicVolume()/SETTING_SCENE_PERCENTAGE);
    
    //get the node of effect slide bar
    ui::Slider* effectSlidebar = static_cast<ui::Slider*>(this->getChildByName("SettingScene")->getChildByName("Effect_slidebar"));
    //unit test
    assert(effectSlidebar);
    
    //add event listener to call back the function
    effectSlidebar->addEventListener(CC_CALLBACK_2(SettingScene::updateEffectSlideBar, this));
    //save the status of current sound effect bar
    effectSlidebar->setPercent(CocosDenshion::SimpleAudioEngine::getInstance()->getEffectsVolume()/SETTING_SCENE_PERCENTAGE);
    
    
    
    
    //get the node of checkbox
    cocos2d::ui::CheckBox* musicCheckBox = static_cast<cocos2d::ui::CheckBox*>(this->getChildByName("SettingScene")->getChildByName("check_box"));
    //unit test
    assert(musicCheckBox);
    
    
    if ( CocosDenshion::SimpleAudioEngine::getInstance()->getBackgroundMusicVolume()==GAME_PLAY_SCENE_SOUND_VOLUME_EMPTY)
    {
        musicCheckBox->setSelected(true);
    }
    musicCheckBox->addEventListener(CC_CALLBACK_2(SettingScene::updateCheckBox, this));
    
    
    
    return true;
}



void SettingScene::GotoMainMenuScene(Ref* pSender, ui::Widget::TouchEventType type)
{
    auto scene = MainMenuScene::createScene();
    //unit test
    assert(scene);
    Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));
    
}

void SettingScene::updateMusicSlideBar(Ref* pSender, ui::Slider::EventType type)
{
    //get music slide bar
    ui::Slider* musicSlideBar =  static_cast<ui::Slider*>(this->getChildByName("SettingScene")->getChildByName("sound_slidebar"));
    //unit test
    assert(musicSlideBar);
    
    float percent = musicSlideBar->getPercent();
    //set music volume
    CocosDenshion::SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(percent*SETTING_SCENE_PERCENTAGE);
}
                                                                               

void SettingScene::updateEffectSlideBar(Ref* pSender, ui::Slider::EventType type)
{
    //get effect slide bar
    ui::Slider* effectSlidebar =  static_cast<ui::Slider*>(this->getChildByName("SettingScene")->getChildByName("Effect_slidebar"));
    //unit test
    assert(effectSlidebar);
    
    float percent = effectSlidebar->getPercent();
    //set effect volume
    CocosDenshion::SimpleAudioEngine::getInstance()->setEffectsVolume(percent*SETTING_SCENE_PERCENTAGE);
}

void SettingScene::updateCheckBox(Ref *pSender,ui::CheckBox::EventType type)
{
    if (type ==CheckBox::EventType::SELECTED)
    {
        //set music and effect bar to be muted and make the button move to left position
        CocosDenshion::SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(GAME_PLAY_SCENE_SOUND_VOLUME_EMPTY);
        CocosDenshion::SimpleAudioEngine::getInstance()->setEffectsVolume(GAME_PLAY_SCENE_SOUND_VOLUME_EMPTY);
        ui::Slider* effectSlidebar =  static_cast<ui::Slider*>(this->getChildByName("SettingScene")->getChildByName("Effect_slidebar"));
        //unit test
        assert(effectSlidebar);
        
        effectSlidebar->setPercent(GAME_PLAY_SCENE_SOUND_VOLUME_EMPTY);
        ui::Slider* musicSlideBar =  static_cast<ui::Slider*>(this->getChildByName("SettingScene")->getChildByName("sound_slidebar"));
        //unit test
        assert(musicSlideBar);
        
        musicSlideBar->setPercent(GAME_PLAY_SCENE_SOUND_VOLUME_EMPTY);
        
    }
    if (type ==CheckBox::EventType::UNSELECTED)
    {
        //set music and effect bar to nomral and make the button move to right position
        CocosDenshion::SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(GAME_PLAY_SCENE_SOUND_VOLUME_ONE);
        CocosDenshion::SimpleAudioEngine::getInstance()->setEffectsVolume(GAME_PLAY_SCENE_SOUND_VOLUME_ONE);
        ui::Slider* effectSlidebar =  static_cast<ui::Slider*>(this->getChildByName("SettingScene")->getChildByName("Effect_slidebar"));
        //unit test
        assert(effectSlidebar);
        
        effectSlidebar->setPercent(GAME_PLAY_SCENE_SOUND_VOLUME_FULL);
        ui::Slider* musicSlideBar =  static_cast<ui::Slider*>(this->getChildByName("SettingScene")->getChildByName("sound_slidebar"));
        //unit test
        assert(musicSlideBar);
        
        musicSlideBar->setPercent(GAME_PLAY_SCENE_SOUND_VOLUME_FULL);
    }
}

