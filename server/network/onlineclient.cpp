#include "onlineclient.h"

OnlineClient::OnlineClient(unsigned int clientId, unsigned int gameId,
                           Broadcast& broadcast, Socket skt)
    : prt(std::move(skt)),
      receiverThread(clientId, prt, broadcast, gameId),
      senderThread(prt, messagesToSend) {}

void OnlineClient::connect() {
    receiverThread.start();
    senderThread.start();
}

<<<<<<< HEAD
void OnlineClient::pushMessage(Message msg) {
=======
void OnlineClient::pushSnapshot(GameSnapshot snapshot) {
>>>>>>> 44da0aea7729e5f9883bfc13a11f42ae26438069
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
