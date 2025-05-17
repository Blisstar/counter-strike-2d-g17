#ifndef ONLINE_CLIENT_H
#define ONLINE_CLIENT_H

#include <assert.h>

#include <iostream>
#include <string>
#include <utility>

#include "broadcast.h"
#include "queue.h"
#include "receiver.h"
#include "sender.h"

class OnlineClient {
   private:
    ServerProtocol prt;
    Queue<Snapshot> snapshotsToSend;
    Receiver receiverThread;
    Sender senderThread;

   private:
    void disconnect();

   public:
    OnlineClient(unsigned int clientId, unsigned int gameId, Broadcast& broadcast, Socket skt);

    OnlineClient(const OnlineClient&) = delete;
    OnlineClient& operator=(const OnlineClient&) = delete;

    void pushSnapshot(Snapshot snapshot);

    void connect();

    bool isDisconnect();

    ~OnlineClient();
};
#endif
