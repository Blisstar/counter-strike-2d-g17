#ifndef LOBBY_H
#define LOBBY_H

#include <mutex>
#include <string>
#include <unordered_map>

#include "game/game.h"

class Lobby {
   private:
    Broadcast& broadcast;
    std::mutex mtx;
    std::unordered_map<unsigned int, Game> games;
    unsigned int nextGameId;
    bool wasClosed;

   public:
    Lobby(Broadcast& _broadcast);

    Lobby(const Lobby&) = delete;
    Lobby& operator=(const Lobby&) = delete;

    unsigned int createGame(std::string gameName, unsigned int hostClientId,
                            unsigned int mapId, std::string playerName);

    void connectGame(unsigned int gameId, unsigned int clientId,
                     std::string playerName);

    void disconnectGame(unsigned int gameId, unsigned int clientId);

    void startGame(unsigned int gameId, unsigned int hostClientId);

    void pushLobbySnapshotById(unsigned int clientId);
};

#endif