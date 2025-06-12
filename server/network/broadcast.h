#ifndef BROADCAST_H
#define BROADCAST_H

class OnlineClient;

#include <assert.h>

#include <list>
#include <mutex>
#include <string>
#include <unordered_map>
#include <utility>

#include "onlineclient.h"
#include "../common/socket.h"
#include "../common/defs.h"

class Broadcast {
   private:
    std::mutex mtx;
    Lobby lobby;
    std::unordered_map<unsigned int, OnlineClient> onlineClients;
    unsigned int nextClientId;
    bool wasClosed;

   public:
    Broadcast();

    Broadcast(const Broadcast&) = delete;
    Broadcast& operator=(const Broadcast&) = delete;

    void addClient(Socket sktNewClient);

    unsigned int createGame(std::string gameName, unsigned int hostClientId,
                            unsigned int mapId, std::string playerName);

    void connectGame(unsigned int gameId, unsigned int clientId, std::string playerName);

    void disconnectGame(unsigned int gameId, unsigned int clientId);

    void startGame(unsigned int gameId, unsigned int hostClientId);

    void disconnectInactiveClients();

    void pushMessageToAll(ServerMessage msg);

    void pushMessageById(unsigned int clientId, ServerMessage msg);

    void pushLobbySnapshotById(unsigned int clientId);

    bool isClosed() const;

    void close();

    ~Broadcast();
};
#endif
