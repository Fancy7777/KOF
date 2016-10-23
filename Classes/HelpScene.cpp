//
//  HelpScene.cpp
//  KOF
//
//  Created by Dongtao Yu on 15/08/2015.
//
//

#include "HelpScene.h"

Scene* HelpScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelpScene::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelpScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        //unit test
        assert(Layer::init() == false);
        return false;
    }
    
    cocos2d::Size visibleSize = Director::getInstance()->getWinSize();
    cocos2d::Vec2 origin = Director::getInstance()->getVisibleOrigin();
    

    auto node = CSLoader::createNode("Help.csb");
    //unit test
    assert(node);
    
    cocos2d::ui::Button* buttonBack =  static_cast<cocos2d::ui::Button*>(node->getChildByName("buttonBack"));
    buttonBack->addTouchEventListener(CC_CALLBACK_2(HelpScene::GotoMainMenuScene, this));
    this->addChild(node);
    
    return true;
}

void HelpScene::GotoMainMenuScene(cocos2d::Ref* pSender, ui::Widget::TouchEventType type)
{
    auto scene = MainMenuScene::createScene();
    //unit test
    assert(scene);
    
    Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));
    
}