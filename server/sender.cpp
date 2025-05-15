#include "sender.h"

Sender::Sender(ServerProtocol& _prt, Queue<Event>& q): prt(_prt), eventsToSend(q) {}

void Sender::run() {
    while (!prt.isClosed()) {
        try {
            Event event = eventsToSend.pop();
            prt.sendEvent(event);
        } catch (const std::exception& e) {
            prt.close();
            break;
        }
    }
}
