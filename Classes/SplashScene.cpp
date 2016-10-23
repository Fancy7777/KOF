//
//  SplashScene.cpp
//  KOF
//
//  Created by Dongtao Yu on 12/08/2015.
//
//

#include "SplashScene.h"


USING_NS_CC;

Scene* SplashScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = SplashScene::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool SplashScene::init()
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
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    //preload the background music
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic("music/backgroundmusic.mp3");
    //play the background music
    CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("music/backgroundmusic.mp3",true);
    
    
    //get SplashScreen node
    auto node = CSLoader::createNode("SplashScreen.csb");
    //unit test
    assert(node);
    
    //set later use name
    node->setName("SplashScreen");
    //unit test
    assert(node->getName() == "SplashScreen");
    
    this->addChild(node);
    this->schedule(schedule_selector(SplashScene::updateLoadingBar), 0.015f);
    
    //bundle the character image with an event
    for (int i = 1 ; i <= 6 ; i ++)
    {
        SpriteFrameCache::getInstance()->addSpriteFramesWithFile(fmt::format(CHARACTER_SPRITE_PATH, "character" + std::to_string(i) ));
        AnimationCache::getInstance()->addAnimationsWithFile(fmt::format(CHARACTER_ANIMATION_PATH, "character" + std::to_string(i) ));
    }
    
    //bundle the backgorund image with an event
    for (int i = 1 ; i <= 4 ; i++)
    {
        SpriteFrameCache::getInstance()->addSpriteFramesWithFile(fmt::format(BACKGROUND_SPRITE_PATH, "background" + std::to_string(i) ));
        AnimationCache::getInstance()->addAnimationsWithFile(fmt::format(BACKGROUND_ANIMATION_PATH, "background" + std::to_string(i) ));
        
    }
    return true;
}


void SplashScene::updateLoadingBar( float dt )
{
    //get loading bar node
    ui::LoadingBar* loadingBar = static_cast<ui::LoadingBar*>(this->getChildByName("SplashScreen")->getChildByName("loadingBar"));
    //unit test
    assert(loadingBar);
    
    float percent = loadingBar->getPercent() + 1;
    loadingBar->setPercent(percent);
    
    //go to main menu scenen when loading bar reach 100
    if(percent >= 100)
    {
        this->unschedule(schedule_selector(SplashScene::updateLoadingBar));
        this->scheduleOnce(schedule_selector(SplashScene::GoToMainMenuScene), DISPLAY_TIME_SPLASH_SCENE);
    }
}




void SplashScene::GoToMainMenuScene( float dt )
{
    auto scene = MainMenuScene::createScene();
    Director::getInstance( )->replaceScene( TransitionFade::create( TRANSITION_TIME, scene ) );
}
