#include "receiver.h"

#include "gameloop.h"

Receiver::Receiver(ServerProtocol& _prt, Gameloop& _game): prt(_prt), game(_game) {}

void Receiver::run() {
    while (!prt.isClosed()) {
        try {
            EventType event = prt.recvEvent();
            if (event == ENEMYDEAD && !prt.isClosed())
                game.pushAttack();
        } catch (const std::exception& e) {
            prt.close();
            break;
        }
    }
}
