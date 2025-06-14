#ifndef GAMELOOP_H
#define GAMELOOP_H

class Broadcast;

#include <assert.h>

#include <algorithm>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

#include "../common/defs.h"
#include "../common/queue.h"
#include "errors/gameinprogresserror.h"
#include "network/broadcast.h"

class Player;

class Game : public Thread {
   private:
    Queue<PlayerAction> playerActionsToProcess;
    std::mutex mtx;
    Broadcast& broadcast;
    std::unordered_map<unsigned int, Player> players;
    std::string gameName;
    unsigned int hostClientId;
    unsigned int mapId;
    std::chrono::milliseconds rate;
    unsigned int stopWatch;
    bool startedGame;

   private:
    void processPlayerActions();

    void updateGame();

    void sendSnapshots();

    void notifyRoomStateToPlayers();

   public:
    Game(Broadcast& _broadcast, std::string _gameName, unsigned int _mapId, unsigned int hostId, std::string hostName);

    Game(const Game&) = delete;
    Game& operator=(const Game&) = delete;

    void pushPlayerAction(PlayerAction playerAction);

    std::string getName();

    unsigned int getMapId();

    uint8_t getPlayersCount();

    unsigned int getStopWatch();

    void run() override;

    void addPlayer(unsigned int clientId, std::string playerName);

    /*
     * Remove the player from the game.
     *
     * Return value:
     * A boolean the indicates if there is player left.
     * */
    bool removePlayer(unsigned int clientId);

    void start(unsigned int hostClientId);
};

#endif
