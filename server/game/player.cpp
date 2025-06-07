#include "player.h"

Player::Player(unsigned int _playerId, std::string _playerName, float startX, float startY, float vel)
    : Entity(startX, startY, vel), playerId(_playerId), playerName(_playerName) {}

unsigned int Player::getPlayerId() {
    return playerId;
}
