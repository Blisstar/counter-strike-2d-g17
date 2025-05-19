#ifndef SENDER_H
#define SENDER_H

#include <assert.h>

#include <iostream>
#include <string>

#include "queue.h"
#include "server_protocol.h"
#include "thread.h"

class Sender : public Thread {
   private:
    ServerProtocol& prt;
<<<<<<< HEAD
    Queue<Message>& messagesToSend;
=======
    Queue<Message>& snapshotsToSend;
>>>>>>> 44da0aea7729e5f9883bfc13a11f42ae26438069

   public:
    Sender(ServerProtocol& _prt, Queue<Message>& q);

    Sender(const Sender&) = delete;
    Sender& operator=(const Sender&) = delete;

    void run() override;
};
#endif
