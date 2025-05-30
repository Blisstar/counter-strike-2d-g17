#ifndef ONLINE_CLIENT_H
#define ONLINE_CLIENT_H

#include <assert.h>

#include <iostream>
#include <string>
#include <utility>

#include "broadcast.h"
#include "../common/queue.h"
#include "sender.h"
#include "../common/thread.h"
#include "receiver.h"

class OnlineClient {
   private:
    ServerProtocol prt;
    Queue<ServerMessage> messagesToSend;
    Receiver receiverThread;
    Sender senderThread;

   private:
    void disconnect();

   public:
    OnlineClient(unsigned int clientId,
                 Broadcast& broadcast, Socket skt);

    OnlineClient(const OnlineClient&) = delete;
    OnlineClient& operator=(const OnlineClient&) = delete;

    void pushMessage(ServerMessage msg);

    void connect();

    bool isDisconnect();

    ~OnlineClient();
};
#endif
