#ifndef PLAYER_H
#define PLAYER_H

#include <string>

#include "defs.h"
#include "ellipse.h"

class Player {
   public:
    Ellipse shape;

   private:
    unsigned int playerId;
    std::string playerName;
    uint8_t health;

   public:
    Player(unsigned int _playerId, std::string _playerName, float startX = 0.0f,
           float startY = 0.0f, float vel = 0.0f);

    unsigned int getPlayerId();

    PlayerState getState();

    Vector2 getPosition();

    void setInMotionWithDirection(Direction dir);

    void move();

    void stopMotion();

    void hurt(uint8_t damage);
};

#endif