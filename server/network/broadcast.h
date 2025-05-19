#ifndef BROADCAST_H
#define BROADCAST_H

class OnlineClient;

#include <assert.h>

#include <list>
#include <mutex>
#include <string>
#include <unordered_map>
#include <utility>

#include "game.h"
#include "onlineclient.h"
#include "queue.h"
#include "socket.h"

class Broadcast {
   private:
    std::mutex mtx;
    std::unordered_map<unsigned int, OnlineClient> onlineClients;
    std::unordered_map<unsigned int, Game> games;
    unsigned int nextClientId;
    unsigned int nextGameId;
    bool wasClosed;

   public:
    Broadcast();

    Broadcast(const Broadcast&) = delete;
    Broadcast& operator=(const Broadcast&) = delete;

    void addClient(Socket sktNewClient);

    unsigned int createGame(std::string gameName, unsigned int hostClientId,
                            unsigned int mapId);

    void connectGame(unsigned int gameId, unsigned int clientId);

    void disconnectGame(unsigned int gameId, unsigned int clientId);

    void startGame(unsigned int gameId, unsigned int hostClientId);

    void disconnectInactiveClients();

    void pushSnapshotToAll(const GameSnapshot snapshot);

    bool isClosed() const;

    void close();

    ~Broadcast();
};
#endif
