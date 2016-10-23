//
//  PhotonMultiplayer.cpp
//  KOF
//
//  Created by Dongtao Yu on 6/10/2015.
//
//

#include "PhotonMultiplayer.hpp"


static const ExitGames::Common::JString appId = L"baa6d632-3cd1-4304-95fc-50bd619551a6"; // set your app id here
static const ExitGames::Common::JString appVersion = L"1.0";


PhotonMultiplayer* PhotonMultiplayer::_instance = NULL;

void PhotonMultiplayer::initialize(ExitGames::Common::JString name)
{
    if (_instance == NULL)
    {
        _instance = new PhotonMultiplayer(name);
    }
}

cocos2d::Point PhotonMultiplayer::extractPos(std::string properties)
{
    std::vector<std::string> value = GameHelper::split(properties, '%');
    return cocos2d::Point(std::stof(value.at(0).c_str()), std::stof(value.at(1)));
}

std::string PhotonMultiplayer::buildProperties(std::initializer_list<std::string> properties)
{
    std::string value;
    for(auto i = properties.begin(); i != properties.end(); i++)
    {
        value += *i + '%';
    }
    return value;
    
}

std::string PhotonMultiplayer::buildEvent(int scene, int op, std::string properties)
{
    std::string output;
    output += std::to_string(scene).c_str();
    output += ';';
    output += std::to_string(op).c_str();
    output += ';';
    output += properties.c_str();
    output += ';';
    return output;
}

command_t PhotonMultiplayer::extractEvent(std::string message)
{
    std::vector<std::string> temp = GameHelper::split(message, ';');
    command_t command;
    command.scene = atoi(temp.at(0).c_str());
    command.operation = atoi(temp.at(1).c_str());
    command.properties = temp.at(2);
    return command;
}



PhotonMultiplayer* PhotonMultiplayer::getInstance()
{
    return _instance;
}


PhotonMultiplayer::PhotonMultiplayer(ExitGames::Common::JString name)
:c(*this, appId, appVersion, name, ExitGames::Photon::ConnectionProtocol::UDP, ExitGames::LoadBalancing::AuthenticationValues(), true, false)
{
    
}

void PhotonMultiplayer::service()
{
//    CCLOG("%d", c.getServerTime());
    c.service();
}

void PhotonMultiplayer::connect(void)
{
    CCLOG("connecting");
    c.connect();
    
}

void PhotonMultiplayer::disconnect(void)
{
    
}

void PhotonMultiplayer::setRoomIsOpen(bool t)
{
    c.getCurrentlyJoinedRoom().setIsOpen(t);
}

void PhotonMultiplayer::opCreateRoom(std::map<std::string, std::string> properties, bool isVisible)
{
    ExitGames::Common::Hashtable p = ExitGames::Common::Hashtable();
    
    ExitGames::Common::JString backgroundK = ROOM_PROPERTY_BACKGROUND;
    ExitGames::Common::JString backgroundV = properties.find(ROOM_PROPERTY_BACKGROUND)->second.c_str();
    
    
    
    ExitGames::Common::JString name = GameHelper::randomIntString(5).c_str();
    
    p.put(backgroundK, backgroundV);
    
    ExitGames::Common::JVector<ExitGames::Common::JString> v = ExitGames::Common::JVector<ExitGames::Common::JString>();
    
    v.addElement(backgroundK);
    
    c.opCreateRoom(
                   name,
                   isVisible,
                   true,
                   2,
                   p,
                   v,
                   ExitGames::Common::JString(),
                   ExitGames::LoadBalancing::LobbyType::DEFAULT,
                   INT_MAX/2,
                   3600);
}


void PhotonMultiplayer::opLeaveRoom()
{
    c.opLeaveRoom();
}

void PhotonMultiplayer::opJoinRoom(std::string id)
{
    c.opJoinRoom(id.c_str());
}

void PhotonMultiplayer::opJoinRandomRoom(void)
{
    c.opJoinRandomRoom();
}

void PhotonMultiplayer::run(void)
{
}

void PhotonMultiplayer::sendEvent(std::string event)
{
//    CCLOG("sending %s", event.c_str());
    c.opRaiseEvent(true, StringToJString(event), 0);
}

void PhotonMultiplayer::sendEvent(int scene, int op, std::string properties, bool broadcast)
{
    if (broadcast)
    {
        c.opRaiseEvent(true, StringToJString(buildEvent(scene, op, properties)), 0, 0, ExitGames::Lite::EventCache::DO_NOT_CACHE, NULL, 0, ExitGames::Lite::ReceiverGroup::ALL);
    }
    else
    {
        c.opRaiseEvent(true, StringToJString(buildEvent(scene, op, properties)), 0);
    }
}



void PhotonMultiplayer::addCustomProperty(std::string k, std::string v)
{
    c.getLocalPlayer().addCustomProperty(StringToJString(k), StringToJString(v));
}


void PhotonMultiplayer::setListener(MultiplayerCallback* l)
{
    this->listener = l;
}

bool PhotonMultiplayer::isConnected()
{
    if (c.getState() == ExitGames::LoadBalancing::PeerStates::JoinedLobby)
        return true;
    
    return false;
}

int PhotonMultiplayer::getPlayerNumber()
{
    return c.getLocalPlayer().getNumber();
}

int PhotonMultiplayer::getOpponentNumber()
{
    ExitGames::Common::JVector<ExitGames::LoadBalancing::Player*> players = c.getCurrentlyJoinedRoom().getPlayers();
    for (int i = 0 ; i < players.getSize() ; i++)
    {
        if (players[i]->getNumber() != getPlayerNumber() )
        {
            return players[i]->getNumber();
        }
    }
}

std::string PhotonMultiplayer::getRoomID()
{
    return JStringToString(c.getCurrentlyJoinedRoom().getName());
}


std::string PhotonMultiplayer::JStringToString(ExitGames::Common::JString input)
{
    std::string output;
    for (int i = 0 ; i < input.length(); i++)
    {
        if (input.charAt(i) != '\"'){
            output += input.charAt(i);
        }
    }
    
    
    return output;
}

ExitGames::Common::JString PhotonMultiplayer::StringToJString(std::string input)
{
    ExitGames::Common::JString output = input.c_str();
    return output;
}


std::vector<std::tuple<std::string, int, int, std::map<std::string, std::string>>> PhotonMultiplayer::getRoomList(void)
{
    std::vector<std::tuple<std::string, int, int, std::map<std::string, std::string>>> v;
    
    ExitGames::Common::JVector<ExitGames::LoadBalancing::Room*> r = c.getRoomList();
    
    for (int i = 0 ; i < r.getSize() ; i++)
    {
        std::string name = JStringToString(r[i]->getName());
        int numUsers = r[i]->getPlayerCount();
        int maxUsers = r[i]->getMaxPlayers();
        std::map<std::string, std::string> p;
        ExitGames::Common::JString backgroundK = ROOM_PROPERTY_BACKGROUND;
        std::string backgroundV = JStringToString(r[i]->getCustomProperties().getValue(backgroundK)->toString());
        p[ROOM_PROPERTY_BACKGROUND] = backgroundV;
        v.push_back(std::make_tuple(name, numUsers, maxUsers, p));
    }
    return v;
}


std::string PhotonMultiplayer::getBackground()
{
    return JStringToString(c.getCurrentlyJoinedRoom().getCustomProperties().getValue(ROOM_PROPERTY_BACKGROUND)->toString());
}


// protocol implementations

void PhotonMultiplayer::debugReturn(int /*debugLevel*/, const ExitGames::Common::JString& string)
{
    CCLOG("debugReturn %ls", string.cstr());
}

void PhotonMultiplayer::connectionErrorReturn(int errorCode)
{
    CCLOG("connectionErrorReturn %d", errorCode);
}

void PhotonMultiplayer::clientErrorReturn(int errorCode)
{
    CCLOG("clientErrorReturn %d", errorCode);
}

void PhotonMultiplayer::warningReturn(int warningCode)
{
    CCLOG("warningReturn %d", warningCode);
}

void PhotonMultiplayer::serverErrorReturn(int errorCode)
{
    CCLOG("serverErrorReturn %d", errorCode);
}


void PhotonMultiplayer::joinRoomEventAction(int playerNr, const ExitGames::Common::JVector<int>& /*playernrs*/, const ExitGames::LoadBalancing::Player& player)
{
    listener->joinRoomEventAction();
}

void PhotonMultiplayer::leaveRoomEventAction(int playerNr, bool isInactive)
{
    listener->leaveRoomEventAction();
}


void PhotonMultiplayer::customEventAction(int playerNr, nByte /*eventCode*/, const ExitGames::Common::Object& eventContent)
{
//    CCLOG("received: %ls", eventContent.toString().cstr());
    command_t c = extractEvent(JStringToString(eventContent.toString()));
    c.sender = playerNr;
    listener->customEventAction(c);
}

void PhotonMultiplayer::connectReturn(int errorCode, const ExitGames::Common::JString& errorString)
{
    CCLOG("RoundTripTime: %ds", c.getRoundTripTime());
    CCLOG("RoundTripTimeVariance: %ds", c.getRoundTripTimeVariance());
    CCLOG("ConnectReturn: %d", errorCode);
    if (errorCode) {
        return;
    }
    listener->onConnectDone();
}

void PhotonMultiplayer::disconnectReturn(void)
{
    
}

void PhotonMultiplayer::createRoomReturn(int localPlayerNr, const ExitGames::Common::Hashtable& gameProperties, const ExitGames::Common::Hashtable& /*playerProperties*/, int errorCode, const ExitGames::Common::JString& errorString)
{
    
    CCLOG("createRoomReturn: %d", errorCode);
    listener->onCreateRoomDone();
}
void PhotonMultiplayer::joinRoomReturn(int localPlayerNr, const ExitGames::Common::Hashtable& /*gameProperties*/, const ExitGames::Common::Hashtable& /*playerProperties*/, int errorCode, const ExitGames::Common::JString& errorString)
{
    CCLOG("joinRoomReturn: %d", errorCode);
    if (errorCode) {
        listener->onJoinRoomFailed();
        return;
    }
    listener->onJoinRoomDone();
}

void PhotonMultiplayer::joinRandomRoomReturn(int localPlayerNr, const ExitGames::Common::Hashtable& /*gameProperties*/, const ExitGames::Common::Hashtable& /*playerProperties*/, int errorCode, const ExitGames::Common::JString& errorString)
{
    CCLOG("joinRandomRoomReturn: %d", errorCode);
    if (errorCode) {
        listener->onJoinRoomFailed();
        return;
    }
    listener->onJoinRoomDone();
}

void PhotonMultiplayer::leaveRoomReturn(int errorCode, const ExitGames::Common::JString& errorString)
{
    CCLOG("leaveRoomReturn: %d", errorCode);
    listener->onLeaveRoomDone();
}

void PhotonMultiplayer::joinLobbyReturn(void)
{
    
}

void PhotonMultiplayer::leaveLobbyReturn(void)
{
}

void PhotonMultiplayer::onLobbyStatsResponse(const ExitGames::Common::JVector<ExitGames::LoadBalancing::LobbyStatsResponse>& lobbyStats)
{
}

void PhotonMultiplayer::onLobbyStatsUpdate(const ExitGames::Common::JVector<ExitGames::LoadBalancing::LobbyStatsResponse>& lobbyStats)
{
}

void PhotonMultiplayer::onAvailableRegions(const ExitGames::Common::JVector<ExitGames::Common::JString>& availableRegions, const ExitGames::Common::JVector<ExitGames::Common::JString>& availableRegionServers)
{
    // choose au server
    c.selectRegion("au");
}


void PhotonMultiplayer::onRoomListUpdate(void)
{
    CCLOG("onRoomListUpdate");
    listener->onRoomListUpdate();
}


void PhotonMultiplayer::onPlayerPropertiesChange(int, const ExitGames::Common::Hashtable &)
{
    listener->onPlayerPropertiesChange();
}