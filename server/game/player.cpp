#include "player.h"

Player::Player(unsigned int _playerId, std::string _playerName)
    : playerId(_playerId), playerName(_playerName) {}

unsigned int Player::getPlayerId() {
    return playerId;
}
