#include "receiver.h"

#include "game.h"

Receiver::Receiver(unsigned int _clientId, ServerProtocol& _prt, Broadcast& _broadcast, unsigned int _idGame)
    : clientId(clientId), prt(_prt), broadcast(_broadcast) {}

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
