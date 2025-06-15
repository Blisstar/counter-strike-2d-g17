#ifndef PLAYER_H
#define PLAYER_H

#include <string>

#include "../common/defs.h"
#include "defs.h"
#include "ellipse.h"
#include "game.h"
#include "armament.h"

class Player {
   public:
    Ellipse shape;

   private:
    Game& game;
    unsigned int playerId;
    std::string playerName;
    uint8_t health;
    Armament armament;

   public:
    Player(Game& _game, unsigned int _playerId, std::string _playerName, float startX = 0.0f,
           float startY = 0.0f, float vel = 0.0f);

    unsigned int getPlayerId();

    PlayerState getState();

    Vector2 getPosition();

    void setInMotionWithDirection(Direction dir);

    void setShootingWithDirection(uint16_t angle);

    void move();

    void stopMotion();

    void hurt(uint8_t damage);
};

#endif