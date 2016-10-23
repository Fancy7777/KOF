//
//  PhotonMultiplayer.hpp
//  KOF
//
//  Created by Dongtao Yu on 6/10/2015.
//
//

#ifndef PhotonMultiplayer_hpp
#define PhotonMultiplayer_hpp

#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include "Definitions.h"
#include "LoadBalancing-cpp/inc/Client.h"

#include "cocos2d.h"
#include "Definitions.h"
#include "GameHelper.h"
#include "MultiplayerCallback.h"


class PhotonMultiplayer : private ExitGames::LoadBalancing::Listener
{
public:
    static PhotonMultiplayer* _instance;
    static void initialize(ExitGames::Common::JString);
    static PhotonMultiplayer* getInstance();
    static std::string JStringToString(ExitGames::Common::JString);
    static ExitGames::Common::JString StringToJString(std::string);
    static std::string buildProperties(std::initializer_list<std::string> properties);
    static std::string buildEvent(int scene, int op, std::string properties="");
    static cocos2d::Point extractPos(std::string properties);
    std::string prevEvent;
    command_t extractEvent(std::string);
    
    void service();
    void setListener(MultiplayerCallback*);
    void run(void);
    void connect(void);
    void opCreateRoom(std::map<std::string, std::string>, bool);
    void opLeaveRoom();
    void opJoinRoom(std::string);
    void opJoinRandomRoom(void);
    void disconnect(void);
    void sendEvent(std::string);
    void sendEvent(int scene, int op, std::string properties="", bool=false);
    void addCustomProperty(std::string, std::string);
    void setRoomIsOpen(bool);
    int getPlayerNumber();
    int getOpponentNumber();
    std::string getBackground();
    
    
    bool isConnected();
    std::vector<std::tuple<std::string, int, int, std::map<std::string, std::string>>> getRoomList(void);
    
    
    std::string getRoomID();
    
    
protected:
    CC_SYNTHESIZE(std::string, playerCharactor, PlayerCharactor);
    CC_SYNTHESIZE(std::string, opponentCharactor, OpponentCharactor);
    
    
private:
    PhotonMultiplayer(ExitGames::Common::JString);
    // receive and print out debug out here
    virtual void debugReturn(int debugLevel, const ExitGames::Common::JString& string);
    
    // implement your error-handling here
    virtual void connectionErrorReturn(int errorCode);
    virtual void clientErrorReturn(int errorCode);
    virtual void warningReturn(int warningCode);
    virtual void serverErrorReturn(int errorCode);
    
    // events, triggered by certain operations of all players in the same room
    virtual void joinRoomEventAction(int playerNr, const ExitGames::Common::JVector<int>& playernrs, const ExitGames::LoadBalancing::Player& player);
    virtual void leaveRoomEventAction(int playerNr, bool isInactive);
    virtual void customEventAction(int playerNr, nByte eventCode, const ExitGames::Common::Object& eventContent);
    
    virtual void onLobbyStatsResponse(const ExitGames::Common::JVector<ExitGames::LoadBalancing::LobbyStatsResponse>& lobbyStats);
    virtual void onLobbyStatsUpdate(const ExitGames::Common::JVector<ExitGames::LoadBalancing::LobbyStatsResponse>& lobbyStats);
    virtual void onAvailableRegions(const ExitGames::Common::JVector<ExitGames::Common::JString>& availableRegions, const ExitGames::Common::JVector<ExitGames::Common::JString>& availableRegionServers);
    
    // callbacks for operations on PhotonLoadBalancing server
    virtual void connectReturn(int errorCode, const ExitGames::Common::JString& errorString);
    virtual void disconnectReturn(void);
    virtual void createRoomReturn(int localPlayerNr, const ExitGames::Common::Hashtable& gameProperties, const ExitGames::Common::Hashtable& playerProperties, int errorCode, const ExitGames::Common::JString& errorString);
    virtual void joinRoomReturn(int localPlayerNr, const ExitGames::Common::Hashtable& gameProperties, const ExitGames::Common::Hashtable& playerProperties, int errorCode, const ExitGames::Common::JString& errorString);
    virtual void joinRandomRoomReturn(int localPlayerNr, const ExitGames::Common::Hashtable& gameProperties, const ExitGames::Common::Hashtable& playerProperties, int errorCode, const ExitGames::Common::JString& errorString);
    virtual void leaveRoomReturn(int errorCode, const ExitGames::Common::JString& errorString);
    virtual void joinLobbyReturn(void);
    virtual void leaveLobbyReturn(void);
    
    virtual void onRoomListUpdate(void);
    virtual void onPlayerPropertiesChange(int, const ExitGames::Common::Hashtable &);
    
    
//    std::stack<>
    ExitGames::LoadBalancing::Client c;
    ExitGames::Common::Logger mLogger;
    MultiplayerCallback* listener;
};


#endif /* PhotonMultiplayer_hpp */
