#ifndef ONLINE_CLIENT_H
#define ONLINE_CLIENT_H

#include <iostream>
#include <string>
#include <utility>

#include <assert.h>

#include "event.h"
#include "queue.h"
#include "receiver.h"
#include "sender.h"

class OnlineClient {
private:
    ServerProtocol prt;
    Queue<Event> eventsToSend;
    Receiver receiverThread;
    Sender senderThread;

private:
    void disconnect();

public:
    OnlineClient(Gameloop& _game, Socket skt);

    OnlineClient(const OnlineClient&) = delete;
    OnlineClient& operator=(const OnlineClient&) = delete;

    void pushEvent(Event event);

    void connect();

    bool isDisconnect();

    ~OnlineClient();
};
#endif
