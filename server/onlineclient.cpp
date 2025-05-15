#include "onlineclient.h"

OnlineClient::OnlineClient(Gameloop& game, Socket skt):
        prt(std::move(skt)), receiverThread(prt, game), senderThread(prt, eventsToSend) {}

void OnlineClient::connect() {
    receiverThread.start();
    senderThread.start();
}

void OnlineClient::pushEvent(Event event) {
    if (!prt.isClosed())
        eventsToSend.try_push(event);
}

void OnlineClient::disconnect() { prt.close(); }

bool OnlineClient::isDisconnect() { return prt.isClosed(); }

OnlineClient::~OnlineClient() {
    disconnect();
    eventsToSend.close();
    receiverThread.stop();
    senderThread.stop();
    receiverThread.join();
    senderThread.join();
}
