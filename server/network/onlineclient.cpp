#include "onlineclient.h"

OnlineClient::OnlineClient(unsigned int clientId, Lobby& lobby,
                           Socket skt)
    : prt(std::move(skt)),
      receiverThread(clientId, prt, lobby),
      senderThread(prt, messagesToSend) {}

void OnlineClient::connect() {
    receiverThread.start();
    senderThread.start();
}

void OnlineClient::pushMessage(ServerMessage msg) {
    if (!prt.isClosed())
        messagesToSend.try_push(msg);
}

void OnlineClient::disconnect() {
    prt.close();
}

bool OnlineClient::isDisconnect() {
    return prt.isClosed();
}

OnlineClient::~OnlineClient() {
    disconnect();
    messagesToSend.close();
    receiverThread.stop();
    senderThread.stop();
    receiverThread.join();
    senderThread.join();
}
