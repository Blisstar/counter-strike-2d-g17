#ifndef DEFS_H
#define DEFS_H

#include <cstdint>

enum class PlayerState : uint8_t {
    Idle = 0x00,
    InMotion = 0x01,
    Dead = 0x02,
};

struct PlayerAction {
    uint32_t idPlayer;
    PlayerMessage message;

    PlayerAction(uint32_t _idPlayer, PlayerMessage _message) : idPlayer(_idPlayer), message(_message) {}
};

#endif