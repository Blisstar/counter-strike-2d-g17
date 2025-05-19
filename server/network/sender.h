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
    Queue<Message>& snapshotsToSend;

   public:
    Sender(ServerProtocol& _prt, Queue<Message>& q);

    Sender(const Sender&) = delete;
    Sender& operator=(const Sender&) = delete;

    void run() override;
};
#endif
