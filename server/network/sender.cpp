#include "sender.h"

Sender::Sender(ServerProtocol& _prt, Queue<GameSnapshot>& q)
<<<<<<< HEAD
    : prt(_prt), messagesToSend(q) {}
=======
    : prt(_prt), snapshotsToSend(q) {}
>>>>>>> 44da0aea7729e5f9883bfc13a11f42ae26438069

void Sender::run() {
    while (!prt.isClosed()) {
        try {
<<<<<<< HEAD
            GameSnapshot snapshot = messagesToSend.pop();
=======
            GameSnapshot snapshot = snapshotsToSend.pop();
>>>>>>> 44da0aea7729e5f9883bfc13a11f42ae26438069
            prt.sendSnapshot(snapshot);
        } catch (const std::exception& e) {
            prt.close();
            break;
        }
    }
}
