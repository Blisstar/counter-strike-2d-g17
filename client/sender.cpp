#include "sender.h"

Sender::Sender(ClientProtocol& _prt, Queue<ClientMessage>& q)
    : prt(_prt), messagesToSend(q) {}

void Sender::run() {
    while (!prt.isClosed()) {
        try {
            prt.sendMessage(messagesToSend.pop());
        } catch (const std::exception& e) {
            prt.close();
            break;
        }
    }
}
