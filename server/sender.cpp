#include "sender.h"

Sender::Sender(ServerProtocol& _prt, Queue<Snapshot>& q): prt(_prt), snapshotsToSend(q) {}

void Sender::run() {
    while (!prt.isClosed()) {
        try {
            Snapshot snapshot = snapshotsToSend.pop();
            prt.sendSnapshot(snapshot);
        } catch (const std::exception& e) {
            prt.close();
            break;
        }
    }
}
