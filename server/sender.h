#ifndef SENDER_H
#define SENDER_H

#include <iostream>
#include <string>

#include <assert.h>

#include "event.h"
#include "server_protocol.h"
#include "queue.h"
#include "thread.h"

class Sender: public Thread {
private:
    ServerProtocol& prt;
    Queue<Event>& eventsToSend;

public:
    Sender(ServerProtocol& _prt, Queue<Event>& q);

    Sender(const Sender&) = delete;
    Sender& operator=(const Sender&) = delete;

    void run() override;
};
#endif
