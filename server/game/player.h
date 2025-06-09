#ifndef PLAYER_H
#define PLAYER_H

#include <string>

#include "ellipse.h"

class Player {
   public:
    Ellipse shape;

   private:
    unsigned int playerId;
    std::string playerName;

   public:
    Player(unsigned int _playerId, std::string _playerName, float startX = 0.0f,
           float startY = 0.0f, float vel = 0.0f);

    unsigned int getPlayerId();
};

#endif