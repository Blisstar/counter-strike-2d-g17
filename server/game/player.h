#include <string>
#ifndef PLAYER_H
#define PLAYER_H

class Player {
   private:
    unsigned int playerId;
    std::string playerName;

   public:
    Player(unsigned int _playerId, std::string _playerName);

    unsigned int getPlayerId();
};

#endif