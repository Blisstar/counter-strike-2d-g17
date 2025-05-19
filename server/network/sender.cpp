#include "sender.h"

Sender::Sender(ServerProtocol& _prt, Queue<GameSnapshot>& q)
    : prt(_prt), snapshotsToSend(q) {}

void Sender::run() {
    while (!prt.isClosed()) {
        try {
            GameSnapshot snapshot = snapshotsToSend.pop();
            prt.sendSnapshot(snapshot);
        } catch (const std::exception& e) {
            prt.close();
            break;
        }
    }
}
