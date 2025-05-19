#include "sender.h"

Sender::Sender(ServerProtocol& _prt, Queue<GameSnapshot>& q)
    : prt(_prt), messagesToSend(q) {}

void Sender::run() {
    while (!prt.isClosed()) {
        try {
            GameSnapshot snapshot = messagesToSend.pop();
            prt.sendSnapshot(snapshot);
        } catch (const std::exception& e) {
            prt.close();
            break;
        }
    }
}
