#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include "entity.h"
#include "ellipse.h"

class Player : public Entity, public Ellipse {
   private:
    unsigned int playerId;
    std::string playerName;

   public:
    Player(unsigned int _playerId, std::string _playerName, float startX = 0.0f, float startY = 0.0f, float vel = 1.0f);

    unsigned int getPlayerId();
};

#endif