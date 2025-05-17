#ifndef GAMELOOP_H
#define GAMELOOP_H

class Broadcast;

#include <assert.h>

#include <iostream>
#include <string>
#include <utility>
#include <vector>

#include "game_action.h"
#include "broadcast.h"
#include "queue.h"
#include "thread.h"

class Game : public Thread {
   private:
    Queue<GameAction> gameActionsToProcess;
    Broadcast& broadcast;
    std::string gameName;

   private:
    void processGameActions();

    Snapshot makeSnapshot();

   public:
    explicit Game(Broadcast& _broadcast, std::string _gameName);

    Game(const Game&) = delete;
    Game& operator=(const Game&) = delete;

    void run() override;

    void pushGameAction(GameAction gameAction);

    void addPlayer(unsigned int clientId);
};
#endif
