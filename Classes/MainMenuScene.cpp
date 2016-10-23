//
//  MainMenuScene.cpp
//  KOF
//
//  Created by Dongtao Yu on 12/08/2015.
//
//

#include "MainMenuScene.h"


Scene* MainMenuScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = MainMenuScene::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool MainMenuScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        //unit test
        assert(Layer::init() == false);
        return false;
    }
    
    //create node of main menu scene
    auto node = CSLoader::createNode("MainMenu.csb");
    //unit test
    assert(node);
    
    //get button for multiplayer
    ui::Button* buttonMultiplayer =  static_cast<ui::Button*>(node->getChildByName("buttonMultiplayer"));
    //unit test
    assert(buttonMultiplayer);
    buttonMultiplayer->addTouchEventListener(CC_CALLBACK_2(MainMenuScene::GoToChooseRoomScene, this));
    
    //get button for help
    ui::Button* buttonHelp =  static_cast<ui::Button*>(node->getChildByName("buttonHelp"));
    //unit test
    assert(buttonHelp);
    buttonHelp->addTouchEventListener(CC_CALLBACK_2(MainMenuScene::GoToHelpScene, this));

    //get button for setting
    ui::Button* buttonSetting =  static_cast<ui::Button*>(node->getChildByName("buttonSetting"));
    //unit test
    assert(buttonSetting);
    buttonSetting->addTouchEventListener(CC_CALLBACK_2(MainMenuScene::GoToSettingScene, this));
    
    //get button for leaderboard
    ui::Button* buttonLeaderboard =  static_cast<ui::Button*>(node->getChildByName("buttonLeaderboard"));
    //unit test
    assert(buttonLeaderboard);
    buttonLeaderboard->addTouchEventListener(CC_CALLBACK_2(MainMenuScene::GotoLeaderBoardScene, this));
    
    //get button for sending Facebook post
    ui::Button* buttonFacebook = node->getChildByName<ui::Button*>(FB_BUTTON);
    //unit test
    assert(buttonFacebook);
    buttonFacebook->addTouchEventListener(CC_CALLBACK_2(MainMenuScene::facebookClicked, this));
    
    //get button for sending Twitter post
    ui::Button* buttonTwitter = node->getChildByName<ui::Button*>(TW_BUTTON);
    //unit test
    assert(buttonTwitter);
    buttonTwitter->addTouchEventListener(CC_CALLBACK_2(MainMenuScene::twitterClicked, this));
    
    //initialize photon for multiplayer
    PhotonMultiplayer::initialize(GameHelper::randomString(5).c_str());
    PhotonMultiplayer::getInstance()->setListener(this);
    this->scheduleUpdate();
    
    this->addChild(node);

    return true;
}


void MainMenuScene::update(float dt)
{
    PhotonMultiplayer::getInstance()->service();
}


void MainMenuScene::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

void MainMenuScene::GoToChooseRoomScene(Ref* pSender, cocos2d::ui::Widget::TouchEventType type)
{
    //check if multiplayer button is pressed
    if(type == cocos2d::ui::Widget::TouchEventType::ENDED){
        
        if (!PhotonMultiplayer::getInstance()->isConnected())
        {
            PhotonMultiplayer::getInstance()->connect();
            LoadingLayer::SetTextAndLoadingBar(this, false, "Connecting....", 50.0f);
        }
        else
        {
            auto scene = ChooseRoomScene::createScene();
            Director::getInstance()->replaceScene( TransitionFade::create(TRANSITION_TIME, scene));
        }
    }
}

void MainMenuScene::facebookClicked(cocos2d::Ref *, ui::Widget::TouchEventType type)
{
    //check if facebook button is pressed
    if (type == ui::Widget::TouchEventType::ENDED) {
        SonarCocosHelper::Facebook::Share("", "", "This is a really fun game", "", "");
    }
}

void MainMenuScene::twitterClicked(cocos2d::Ref *, ui::Widget::TouchEventType type)
{
    //check if twitter button is pressed
    if (type == ui::Widget::TouchEventType::ENDED) {
        SonarCocosHelper::Twitter::Tweet("This is a really fun game", "", "");
    }
}


void MainMenuScene::GoToHelpScene(Ref* pSender, cocos2d::ui::Widget::TouchEventType type)
{
    auto scene = HelpScene::createScene();
    //uni test
    assert(scene);
    Director::getInstance( )->replaceScene( TransitionFade::create( TRANSITION_TIME, scene ) );
}


void MainMenuScene::GoToSettingScene(Ref* pSender, ui::Widget::TouchEventType type)
{
    auto scene = SettingScene::createScene();
    //uni test
    assert(scene);
    Director::getInstance( )->replaceScene( TransitionFade::create( TRANSITION_TIME, scene ) );
}

void MainMenuScene::GotoLeaderBoardScene(Ref* pSender, ui::Widget::TouchEventType type)
{
    SonarCocosHelper::GameCenter::showLeaderboard();
}

void MainMenuScene::onConnectDone()
{
    LoadingLayer::SetTextAndLoadingBar(static_cast<Node*>(this), true, "DONE...", 100.0f);
    auto scene = ChooseRoomScene::createScene();
    //uni test
    assert(scene);
    Director::getInstance()->replaceScene( TransitionFade::create(TRANSITION_TIME, scene));
}

