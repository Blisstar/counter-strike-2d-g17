#ifndef SENDER_H
#define SENDER_H

#include <assert.h>

#include <iostream>
#include <string>

#include "../common/queue.h"
#include "client_protocol.h"
#include "../common/thread.h"

class Sender : public Thread {
   private:
    ClientProtocol& prt;
    Queue<ClientMessage>& messagesToSend;

   public:
    Sender(ClientProtocol& _prt, Queue<ClientMessage>& q);

    Sender(const Sender&) = delete;
    Sender& operator=(const Sender&) = delete;

    void run() override;
};
#endif
