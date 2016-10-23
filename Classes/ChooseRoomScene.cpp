//
//  ChooseRoomScene.cpp
//  KOF
//
//  Created by Dongtao Yu on 16/08/2015.
//
//

#include "ChooseRoomScene.h"

Scene* ChooseRoomScene::createScene()
{
//    Multiplayer::getInstance()->resetAllListener();
    
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = ChooseRoomScene::create();
    
    layer->onRoomListUpdate();
    
    // add layer as a child to scened
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool ChooseRoomScene::init()
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
    
    auto node = CSLoader::createNode(CHOOSE_ROOM_SCENE_FILE);
    //unit test
    assert(node);
    
    node->setName(CHOOSE_ROOM_SCENE);
    //unit test
    assert(node->getName() == CHOOSE_ROOM_SCENE);
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile(BACKGROUND_PLIST);
    
    // back button
    cocos2d::ui::Button* buttonBack = static_cast<cocos2d::ui::Button*>(node->getChildByName(BACK_BUTTON));
    //unit test
    assert(buttonBack);
    buttonBack->addTouchEventListener(CC_CALLBACK_2(ChooseRoomScene::GotoMainMenuScene, this));
    
    // create room button
    cocos2d::ui::Button* buttonCreate = static_cast<cocos2d::ui::Button*>(node->getChildByName(CREATE_BUTTON));
    //unit test
    assert(buttonCreate);
    buttonCreate->addTouchEventListener(CC_CALLBACK_2(ChooseRoomScene::GotoCreateRoomScene, this));
    
    // search button
    cocos2d::ui::Button* buttonSearch = static_cast<cocos2d::ui::Button*>(node->getChildByName(SEARCH_BUTTON));
    //unit test
    assert(buttonSearch);
    buttonSearch->addTouchEventListener(CC_CALLBACK_2(ChooseRoomScene::SearchRoom, this));
    
    // quick join
    cocos2d::ui::Button* buttonQuickJoin = static_cast<cocos2d::ui::Button*>(node->getChildByName(QUICK_JOIN_BUTTON));
    //unit test
    assert(buttonQuickJoin);
    buttonQuickJoin->addTouchEventListener(CC_CALLBACK_2(ChooseRoomScene::buttonQuickJoinClicked, this));
    
    cocos2d::ui::ListView* listRoom = static_cast<cocos2d::ui::ListView*>(node->getChildByName(CHOOSE_ROOM_SCENE_ROOM_LIST));
    //unit test
    assert(listRoom);
    cocos2d::Vector<cocos2d::ui::Widget*> items = listRoom->getItems();
    static_cast<cocos2d::ui::ImageView*>(items.front())->addTouchEventListener(CC_CALLBACK_2(ChooseRoomScene::OnSelectedItem, this));
    listRoom->setItemModel(items.front());
    listRoom->removeItem(0);
    
    
    
    this->addChild(node);
    
    PhotonMultiplayer::getInstance()->setListener(this);
    this->scheduleUpdate();
    
    return true;
}

void ChooseRoomScene::update(float dt)
{
    PhotonMultiplayer::getInstance()->service();
}

void ChooseRoomScene::GotoMainMenuScene(Ref* pSender, cocos2d::ui::Widget::TouchEventType type)
{
    if (type == cocos2d::ui::Widget::TouchEventType::ENDED)
    {
        auto scene = MainMenuScene::createScene();
        //unit test
        assert(scene);
        Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));
    }
}


void ChooseRoomScene::GotoCreateRoomScene(Ref* pSender, cocos2d::ui::Widget::TouchEventType type)
{
    if (type == cocos2d::ui::Widget::TouchEventType::ENDED)
    {
        auto scene = CreateRoomScene::createScene();
        //unit test
        assert(scene);
        Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));
    }
}



void ChooseRoomScene::OnSelectedItem(Ref* pSender, cocos2d::ui::Widget::TouchEventType type){
    if (type == cocos2d::ui::Widget::TouchEventType::ENDED){
        //get the room ID for later use
        std::string roomID = static_cast<cocos2d::ui::ImageView*>(pSender)->getChildByName<cocos2d::ui::Text*>(CHOOSE_ROOM_SCENE_ROOM_LIST_ITEM_ID)->getString();
        PhotonMultiplayer::getInstance()->opJoinRoom(roomID);
        LoadingLayer::SetTextAndLoadingBar(static_cast<Node*>(this), false, "joining room...", 50.0f);
    }
}


void ChooseRoomScene::buttonQuickJoinClicked(cocos2d::Ref *pSender, cocos2d::ui::Widget::TouchEventType type)
{
    if (type == cocos2d::ui::Widget::TouchEventType::ENDED) {
        PhotonMultiplayer::getInstance()->opJoinRandomRoom();
        LoadingLayer::SetTextAndLoadingBar(static_cast<Node*>(this), false, "finding room...", 50.0f);
    }
}


void ChooseRoomScene::onJoinRoomDone()
{
    MultiplayerCallback::onJoinRoomDone();
    LoadingLayer::SetTextAndLoadingBar(static_cast<Node*>(this), true, "DONE", 100.0f);
    auto scene = ChooseCharacterScene::createScene();
    //unit test
    assert(scene);
    Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));
}

void ChooseRoomScene::onJoinRoomFailed()
{
    MultiplayerCallback::onJoinRoomFailed();
    MessageBox("Unable to find a room", "");
    LoadingLayer::RemoveLoadingLayer(static_cast<Node*>(this));
}

// RoomRequestListner
void ChooseRoomScene::onRoomListUpdate()
{
    auto node = this->getChildByName(CHOOSE_ROOM_SCENE);
    //unit test
    assert(node);
    //get the room list in choose room scene
    cocos2d::ui::ListView* list = static_cast<cocos2d::ui::ListView*>(node->getChildByName(CHOOSE_ROOM_SCENE_ROOM_LIST));
    //update room list
    list->removeAllItems();
    std::vector<std::tuple<std::string, int, int, std::map<std::string, std::string>>> roomList = PhotonMultiplayer::getInstance()->getRoomList();
    //replace with new room list
    for (int i = 0; i < roomList.size(); i++)
    {
        if (std::get<1>(roomList.at(i)) != 0 && std::get<1>(roomList.at(i)) != 2)
            createRoomListEntry(std::get<0>(roomList.at(i)), std::get<1>(roomList.at(i)), std::get<2>(roomList.at(i)), std::get<3>(roomList.at(i)));
    }
}

void ChooseRoomScene::createRoomListEntry(std::string roomId,
                                            int nonUsers,
                                            int maxUsers,
                                            std::map<std::string, std::string> properties)
{
    
    auto node = this->getChildByName(CHOOSE_ROOM_SCENE);
    //unit test
    assert(node);
    cocos2d::ui::ListView* list = static_cast<cocos2d::ui::ListView*>(node->getChildByName(CHOOSE_ROOM_SCENE_ROOM_LIST));
    list->pushBackDefaultItem();
    auto item = list->getItems().back();
    // add room id
    static_cast<ui::Text*>(item->getChildByName(CHOOSE_ROOM_SCENE_ROOM_LIST_ITEM_ID))->setString(roomId);
    // status
    static_cast<ui::Text*>(item->getChildByName(CHOOSE_ROOM_SCENE_ROOM_LIST_ITEM_STATUS))->setString(std::to_string(nonUsers) + "/" + std::to_string(maxUsers));
    // image
    std::string filename = fmt::format(BACKGROUND_ICON_PATH, properties.find(ROOM_PROPERTY_BACKGROUND)->second);
    static_cast<ui::ImageView*>(item->getChildByName(CHOOSE_ROOM_SCENE_ROOM_LIST_ITEM_BACKGROUND))->loadTexture(filename, ui::Widget::TextureResType::PLIST);
    std::string* background = new std::string(properties.find(ROOM_PROPERTY_BACKGROUND)->second);
    static_cast<ui::ImageView*>(item->getChildByName(CHOOSE_ROOM_SCENE_ROOM_LIST_ITEM_BACKGROUND))->setUserData(background);
    
}

void ChooseRoomScene::SearchRoom(Ref* pSender, cocos2d::ui::Widget::TouchEventType type)
{
    if (type == cocos2d::ui::Widget::TouchEventType::ENDED){
        auto node = this->getChildByName(CHOOSE_ROOM_SCENE);
        //unit test
        assert(node);
        auto sprite = static_cast<ui::ImageView*>(node->getChildByName(CHOOSE_ROOM_SCENE_SPRITE_SEARCH));
	    auto textSearch = static_cast<ui::TextField*>(sprite->getChildByName(CHOOSE_ROOM_SCENE_TEXT_SEARCH));
        
        if (!textSearch->getString().compare(""))
        {
            MessageBox("Please input searching Room ID", "");
            return;
        }
        PhotonMultiplayer::getInstance()->opJoinRoom(textSearch->getString());
        LoadingLayer::SetTextAndLoadingBar(static_cast<Node*>(this), false, "finding room...", 50.0f);
    }
}





