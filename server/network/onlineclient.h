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
<<<<<<< HEAD
    Queue<Message> messagesToSend;
=======
    Queue<GameSnapshot> snapshotsToSend;
>>>>>>> 44da0aea7729e5f9883bfc13a11f42ae26438069
    Receiver receiverThread;
    Sender senderThread;

   private:
    void disconnect();

   public:
    OnlineClient(unsigned int clientId, unsigned int gameId,
                 Broadcast& broadcast, Socket skt);

    OnlineClient(const OnlineClient&) = delete;
    OnlineClient& operator=(const OnlineClient&) = delete;

<<<<<<< HEAD
    void pushMessage(Message msg);
=======
    void pushSnapshot(GameSnapshot snapshot);
>>>>>>> 44da0aea7729e5f9883bfc13a11f42ae26438069

    void connect();

    bool isDisconnect();

    ~OnlineClient();
};
#endif
