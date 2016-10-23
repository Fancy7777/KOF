//
//  MultiplayerCallback.h
//  KOF
//
//  Created by Dongtao Yu on 25/09/2015.
//
//

#ifndef MultiplayerCallback_h
#define MultiplayerCallback_h

class MultiplayerCallback
{
public:
    
    
    
#pragma mark room
    virtual void onCreateRoomDone(){ CCLOG("create room done..."); };
    virtual void onJoinRoomDone(){ CCLOG("join room done..."); };
    virtual void onJoinRoomFailed(){ CCLOG("join room failed..."); }
    virtual void onLeaveRoomDone(){ CCLOG("leave room done..."); };
    
    virtual void joinRoomEventAction() { CCLOG("on user joined "); };
    virtual void leaveRoomEventAction() { CCLOG("on user leaved "); };
    
#pragma mark connecttion
    virtual void onConnectDone(){ CCLOG("connection done"); };
    
#pragma mark lobby
    virtual void onRoomListUpdate() { CCLOG("onRoomListUpdate"); };
    virtual void onJoinLobbyDone(){ CCLOG("join lobby done...");};
    virtual void onLeaveLobbyDone(){ CCLOG("leave lobby done...");};
    
#pragma mark event
    virtual void customEventAction(command_t) { CCLOG("customEventAction"); };
    virtual void onPlayerPropertiesChange() { CCLOG("onPlayerPropertiesChange"); };
};

#endif /* MultiplayerCallback_h */
