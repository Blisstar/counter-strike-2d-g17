#ifndef GAMELOOP_H
#define GAMELOOP_H

class Broadcast;

#include <iostream>
#include <string>
#include <utility>
#include <vector>

#include <assert.h>

#include "event.h"
#include "broadcast.h"
#include "queue.h"
#include "thread.h"

class Gameloop: public Thread {
private:
    std::vector<uint> nextResurrect;
    uint16_t enemiesAliveLimit;
    Queue<EventType> eventsToProcess;
    Broadcast& broadcast;

private:
    Event makeEvent(EventType eventType);

    void reviveEnemies();

    void attackAEnemy();

public:
    explicit Gameloop(Broadcast& _broadcast);

    Gameloop(const Gameloop&) = delete;
    Gameloop& operator=(const Gameloop&) = delete;

    void run() override;

    void pushAttack();
};
#endif
