#ifndef SENDER_H
#define SENDER_H

#include <assert.h>

#include <iostream>
#include <string>

#include "../common/queue.h"
#include "server_protocol.h"
#include "../common/thread.h"

class Sender : public Thread {
   private:
    ServerProtocol& prt;
    Queue<ServerMessage>& messagesToSend;

   public:
    Sender(ServerProtocol& _prt, Queue<ServerMessage>& q);

    Sender(const Sender&) = delete;
    Sender& operator=(const Sender&) = delete;

    void run() override;
};
#endif
