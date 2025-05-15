#include "gameloop.h"

Gameloop::Gameloop(Broadcast& _broadcast): broadcast(_broadcast) { enemiesAliveLimit = 5; }

Event Gameloop::makeEvent(EventType eventType) {
    Event e;
    e.enemiesAliveCnt = enemiesAliveLimit - nextResurrect.size();
    e.enemiesDeadCnt = nextResurrect.size();
    e.type = eventType;
    return e;
}

void Gameloop::reviveEnemies() {
    while (0 < nextResurrect.size() && nextResurrect[0] == 15) {
        nextResurrect.erase(nextResurrect.begin());
        Event e = makeEvent(ENEMYREVIVED);
        broadcast.pushEventToAll(e);
        e.show();
    }
}

void Gameloop::attackAEnemy() {
    if (nextResurrect.size() < enemiesAliveLimit) {
        nextResurrect.push_back(0);
        Event e = makeEvent(ENEMYDEAD);
        broadcast.pushEventToAll(e);
        e.show();
    }
}

void Gameloop::run() {
    while (_keep_running || (nextResurrect.size() != 0)) {
        EventType eventType;
        while (eventsToProcess.try_pop(eventType)) {
            if (eventType == ENEMYDEAD)
                attackAEnemy();
        }
        reviveEnemies();
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
        for (size_t i = 0; i < nextResurrect.size(); i++) {
            nextResurrect[i]++;
        }
    }
    eventsToProcess.close();
}

void Gameloop::pushAttack() { eventsToProcess.try_push(ENEMYDEAD); }
