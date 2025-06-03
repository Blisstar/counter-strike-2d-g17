#include "receiver.h"



Receiver::Receiver(ClientProtocol& _prt)
    : prt(_prt) {}

void Receiver::run() {
    while (!prt.isClosed()) {
        prt.receive_gamesnapshot()
    }
}
