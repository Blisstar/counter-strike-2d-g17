#ifndef EVENT_H
#define EVENT_H

#include <iostream>
#include <string>

#include <assert.h>

enum EventType { ENEMYDEAD = 0x04, ENEMYREVIVED = 0X05 };

struct Event {
public:
    uint8_t type;
    uint16_t enemiesDeadCnt;
    uint16_t enemiesAliveCnt;

public:
    // Event(uint8_t _type, uint16_t _enemiesDeadCnt, uint16_t _enemiesAliveCnt);

    void show() const;
};
#endif
