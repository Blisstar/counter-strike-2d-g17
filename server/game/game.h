#ifndef GAMELOOP_H
#define GAMELOOP_H

class Broadcast;

#include <assert.h>

#include <algorithm>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

#include "network/broadcast.h"
#include "errors/gameinprogresserror.h"
#include "../common/queue.h"

class Game /* : public Thread */ {
   private:
    //    Queue<GameAction> gameActionsToProcess;
    std::mutex mtx;
    Broadcast& broadcast;
    std::vector<unsigned int> connectedPlayers;
    std::string gameName;
    unsigned int mapId;
    bool startedGame;
    /*
       private:
        void processGameActions();

        GameSnapshot makeSnapshot();
     */
   public:
   Game(Broadcast& _broadcast, std::string _gameName, unsigned int _mapId);

    Game(const Game&) = delete;
    Game& operator=(const Game&) = delete;

    //    void run() override;

    void addPlayer(unsigned int clientId);

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
