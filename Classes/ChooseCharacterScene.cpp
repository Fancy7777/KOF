//
//  ChooseRoomScene.cpp
//  KOF
//
//  Created by Dongtao Yu on 16/08/2015.
//
//

#include "ChooseCharacterScene.h"

#pragma mark init
Scene* ChooseCharacterScene::createScene()
{
    
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = ChooseCharacterScene::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool ChooseCharacterScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        //unit test
        assert(Layer::init() == false);
        return false;
    }
    
    this->playerSelected = "";
    this->opponentSelected = "";
    this->playerReady = false;
    this->opponentReady = false;
    
    
    cocos2d::Size visibleSize = Director::getInstance()->getWinSize();
    cocos2d::Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    auto node = CSLoader::createNode(CHOOSE_CHARACTER_SCENE_FILE);
    //unit test
    assert(node);
    node->setName(CHOOSE_CHARACTER_SCENE);
    //unit test
    assert(node->getName() == CHOOSE_CHARACTER_SCENE);
    
    //get the button for back
    cocos2d::ui::Button* buttonBack = static_cast<cocos2d::ui::Button*>(node->getChildByName(BACK_BUTTON));
    //unit test
    assert(buttonBack);
    
    //add listener to listen if the button is pressed
    buttonBack->addTouchEventListener(CC_CALLBACK_2(ChooseCharacterScene::ButtonBackClicked, this));
    
    //set the room ID of current room
    node->getChildByName<cocos2d::ui::Text*>(CHOOSE_CHARACTER_SCENE_ROOMID)->setString(PhotonMultiplayer::getInstance()->getRoomID());
    
    //display iamges of 6 characters
    for(int i = 1 ; i <= 6 ; i ++)
    {
        //get image of each character
        cocos2d::ui::ImageView* image = static_cast<cocos2d::ui::ImageView*>(node->getChildByName(CHOOSE_CHARACTER_SCENE_CHARACTER_PREFIX+std::to_string(i)));
        //unit test
        assert(image);
        //add touch event listener to listen which character is choosen
        image->addTouchEventListener(CC_CALLBACK_2(ChooseCharacterScene::CharacterClicked, this));
    }
    
    //add event listener to listen if the ready button is pressed
    node->getChildByName<cocos2d::ui::Button*>(CHOOSE_CHARACTER_SCENE_READY_L)->addTouchEventListener(CC_CALLBACK_2(ChooseCharacterScene::ButtonReadyClicked, this));
    //add event listener to listen if the go button is pressed
    node->getChildByName<cocos2d::ui::Button*>(CHOOSE_CHARACTER_SCENE_GO_L)->addTouchEventListener(CC_CALLBACK_2(ChooseCharacterScene::ButtonGoClicked, this));
    this->addChild(node);
    
    PhotonMultiplayer::getInstance()->setListener(this);
    this->scheduleUpdate();
    return true;
}


#pragma mark getters / setters
void ChooseCharacterScene::setOpponentSelected(std::string name)
{
    if(!name.compare(""))
    {
        return;
    }
    this->opponentSelected = name;
    //show opponent character image if it is selected
    ShowSelectedCharacter(opponentSelected, false);
}


void ChooseCharacterScene::setPlayerSelected(std::string name)
{
    if(!name.compare(""))
    {
        return;
    }
    if(playerSelected.compare("")){
        RemoveSelectedBorder(playerSelected);
    }
    playerSelected = name;
    //show the selected border
    ShowSelectedBorder(playerSelected);
    //show player character image if it is selected
    ShowSelectedCharacter(playerSelected, true);
    
}


void ChooseCharacterScene::setPlayerReady(bool value)
{
    if (value)
    {
        if(playerSelected.compare(""))
        {
            //player is ready
            SetReadyButtonVisible(false, true);
            SetGoButtonVisible(true, true);
            playerReady = true;
        }
        else
        {
            MessageBox("", "Please Select a Character First");
        }
    }
    else
    {
        //player is not ready
        SetGoButtonVisible(false, true);
        SetReadyButtonVisible(true, true);
        playerReady = false;
    }
    CheckBothReady();
}

void ChooseCharacterScene::setOpponentReady(bool value)
{
    if (value)
    {
        if (!opponentSelected.compare(""))
            return;
        //opponent player is ready
        SetReadyButtonVisible(false, false);
        SetGoButtonVisible(true, false);
        opponentReady = true;
    } else {
        //opponent player is not ready
        SetGoButtonVisible(false, false);
        SetReadyButtonVisible(true, false);
        opponentReady = false;
    }
    CheckBothReady();
}



#pragma mark buttons / events
void ChooseCharacterScene::CharacterClicked(Ref* pSender, cocos2d::ui::Widget::TouchEventType type)
{
    if(type == cocos2d::ui::Widget::TouchEventType::ENDED){
        setPlayerSelected(static_cast<Node*>(pSender)->getName());
        PhotonMultiplayer::getInstance()->sendEvent(MP_CHOOSE_CHARACTER_SCENE, OP_CCS_CHARACTER_CHANGED, static_cast<Node*>(pSender)->getName());
    }
}

void ChooseCharacterScene::ButtonBackClicked(Ref* pSender, cocos2d::ui::Widget::TouchEventType type)
{
    if(type == cocos2d::ui::Widget::TouchEventType::ENDED){
        LoadingLayer::SetTextAndLoadingBar(static_cast<Node*>(this), false, "leaving room...", 50.0f);
        PhotonMultiplayer::getInstance()->opLeaveRoom();
    }
}

void ChooseCharacterScene::ButtonGoClicked(Ref* pSender, cocos2d::ui::Widget::TouchEventType type)
{
    if(type == cocos2d::ui::Widget::TouchEventType::ENDED)
    {
        setPlayerReady(false);
        PhotonMultiplayer::getInstance()->sendEvent(MP_CHOOSE_CHARACTER_SCENE, OP_CCS_NOTREADY, playerSelected);
    }
}

void ChooseCharacterScene::ButtonReadyClicked(Ref* pSender, cocos2d::ui::Widget::TouchEventType type)
{
    if(type == cocos2d::ui::Widget::TouchEventType::ENDED)
    {
        setPlayerReady(true);
        PhotonMultiplayer::getInstance()->sendEvent(MP_CHOOSE_CHARACTER_SCENE, OP_CCS_READY, playerSelected);
    }
    
}


#pragma mark ready / go buttons
void ChooseCharacterScene::CheckBothReady()
{
    if(opponentReady && playerReady)
    {
        LoadingLayer::SetTextAndLoadingBar(static_cast<Node*>(this), false, "waiting for player...", 20.0f);
        PhotonMultiplayer::getInstance()->sendEvent(MP_CHOOSE_CHARACTER_SCENE, OP_CCS_START_GAME, "", true);
    }
}


void ChooseCharacterScene::SetGoButtonVisible(bool visible, bool left)
{
    //judge it is left or right button
    std::string name = left ? CHOOSE_CHARACTER_SCENE_GO_L : CHOOSE_CHARACTER_SCENE_GO_R;
    auto node = this->getChildByName(CHOOSE_CHARACTER_SCENE)->getChildByName<cocos2d::ui::Button*>(name);
    //unit test
    assert(node);
    node->setTouchEnabled(visible);
    node->setVisible(visible);
    
}

void ChooseCharacterScene::SetReadyButtonVisible(bool visible, bool left)
{
    //judge it is left or right button
    std::string name = left ? CHOOSE_CHARACTER_SCENE_READY_L : CHOOSE_CHARACTER_SCENE_READY_R;
    auto node = this->getChildByName(CHOOSE_CHARACTER_SCENE)->getChildByName<cocos2d::ui::Button*>(name);
    //unit test
    assert(node);
    node->setTouchEnabled(visible);
    node->setVisible(visible);
}


void ChooseCharacterScene::ResetGoReadyButton()
{
    setPlayerReady(false);
    setOpponentReady(false);
}





#pragma mark select character
void ChooseCharacterScene::ShowSelectedCharacter(std::string name, bool left)
{
    //judge it is left or right place to put the character image
    std::string place = left ? CHOOSE_CHARACTER_SCENE_PLAYER_ICON_HOLDER : CHOOSE_CHARACTER_SCENE_OPPONENT_ICON_HOLDER;
    //get the image of the character
    cocos2d::ui::ImageView* image = static_cast<cocos2d::ui::ImageView*>(this->getChildByName(CHOOSE_CHARACTER_SCENE)->getChildByName(place));
    //unit test
    assert(image);
    //show the image
    image->setVisible(true);
    std::string filename = fmt::format(CHARACTER_ICON_BIG_PATH, name);
    image->loadTexture(filename, cocos2d::ui::Widget::TextureResType::PLIST);
}


void ChooseCharacterScene::ShowSelectedBorder(std::string name)
{
    
    this->getChildByName(CHOOSE_CHARACTER_SCENE)->getChildByName(name)->getChildByName(BORDER_UNSELECTED)->setVisible(false);
    this->getChildByName(CHOOSE_CHARACTER_SCENE)->getChildByName(name)->getChildByName(BORDER_SELECTED)->setVisible(true);
}


void ChooseCharacterScene::RemoveSelectedBorder(std::string name)
{
    this->getChildByName(CHOOSE_CHARACTER_SCENE)->getChildByName(name)->getChildByName(BORDER_SELECTED)->setVisible(false);
    this->getChildByName(CHOOSE_CHARACTER_SCENE)->getChildByName(name)->getChildByName(BORDER_UNSELECTED)->setVisible(true);
}



#pragma mark callbacks

void ChooseCharacterScene::onLeaveRoomDone()
{
    MultiplayerCallback::onLeaveRoomDone();
    LoadingLayer::SetTextAndLoadingBar(static_cast<Node*>(this), true, "Done...", 100.0f);
    auto scene = ChooseRoomScene::createScene();
    //unit test
    assert(scene);
    Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));
}


void ChooseCharacterScene::joinRoomEventAction()
{
    MultiplayerCallback::joinRoomEventAction();
    PhotonMultiplayer::getInstance()->sendEvent(MP_CHOOSE_CHARACTER_SCENE, OP_CCS_CHARACTER_CHANGED, playerSelected);
    ResetGoReadyButton();
    this->getChildByName(CHOOSE_CHARACTER_SCENE)->getChildByName(CHOOSE_CHARACTER_SCENE_WAITING)->setVisible(false);
}

void ChooseCharacterScene::leaveRoomEventAction()
{
    MultiplayerCallback::leaveRoomEventAction();
    ResetGoReadyButton();
    this->getChildByName(CHOOSE_CHARACTER_SCENE)->getChildByName(CHOOSE_CHARACTER_SCENE_WAITING)->setVisible(true);
    this->getChildByName(CHOOSE_CHARACTER_SCENE)->getChildByName(CHOOSE_CHARACTER_SCENE_OPPONENT_ICON_HOLDER)->setVisible(false);
}

void ChooseCharacterScene::onPlayerPropertiesChange()
{
    //change selected player
    MultiplayerCallback::onPlayerPropertiesChange();
}


void ChooseCharacterScene::customEventAction(command_t event)
{
    MultiplayerCallback::customEventAction(event);
    switch (event.operation) {
        case OP_CCS_CHARACTER_CHANGED:
                setOpponentSelected(event.properties);
            break;
        case OP_CCS_READY:
            setOpponentSelected(event.properties);
            setOpponentReady(true);
            break;
    
        case OP_CCS_NOTREADY:
                setOpponentSelected(event.properties);
                setOpponentReady(false);
            break;
    
        case OP_CCS_START_GAME:
            if (!isGameStart)
                StartGame();
            
            break;
                
        default:
            break;
    }
}

#pragma mark loop
void ChooseCharacterScene::update(float dt)
{
    PhotonMultiplayer::getInstance()->service();
    
}


#pragma mark start game
void ChooseCharacterScene::StartGame()
{
    if (isGameStart)
        return;
    
    isGameStart = true;
    
    PhotonMultiplayer::getInstance()->setRoomIsOpen(false);
    PhotonMultiplayer::getInstance()->setPlayerCharactor(playerSelected);
    PhotonMultiplayer::getInstance()->setOpponentCharactor(opponentSelected);
    
    
    
    LoadingLayer::SetTextAndLoadingBar(static_cast<Node*>(this), false, "Done...", 100.0f);
    auto scene = GamePlayScene::createScene();
    //unit test
    assert(scene);
    Director::getInstance()->replaceScene(scene);
    
}

