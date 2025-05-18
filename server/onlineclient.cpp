#include "onlineclient.h"

OnlineClient::OnlineClient(unsigned int clientId, unsigned int gameId, Broadcast& broadcast,
                           Socket skt)
    : prt(std::move(skt)),
      receiverThread(clientId, prt, broadcast, gameId),
      senderThread(prt, snapshotsToSend) {}

void OnlineClient::connect() {
    receiverThread.start();
    senderThread.start();
}

void OnlineClient::pushSnapshot(Snapshot snapshot) {
    if (!prt.isClosed())
        snapshotsToSend.try_push(snapshot);
}

void OnlineClient::disconnect() {
    prt.close();
}

bool OnlineClient::isDisconnect() {
    return prt.isClosed();
}

OnlineClient::~OnlineClient() {
    disconnect();
    snapshotsToSend.close();
    receiverThread.stop();
    senderThread.stop();
    receiverThread.join();
    senderThread.join();
}
