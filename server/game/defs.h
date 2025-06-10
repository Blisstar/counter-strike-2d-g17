#include <cstdint>
#ifndef DEFS.H_H
#define DEFS.H_H

enum class PlayerState : uint8_t {
    Idle = 0x00,
    InMotion = 0x01,
    Dead = 0x02,
};


#endif