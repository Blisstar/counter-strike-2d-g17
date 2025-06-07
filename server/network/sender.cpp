#include "sender.h"

Sender::Sender(ServerProtocol& _prt, Queue<ServerMessage>& q)
    : prt(_prt), messagesToSend(q) {}

void Sender::run() {
    while (!prt.isClosed()) {
        try {
            prt.sendMessage(messagesToSend.pop());
        } catch (const std::exception& e) {
            std::cerr << "[Sender] Error: " << e.what() << std::endl;
            prt.close();
            break;
        }
    }
}
