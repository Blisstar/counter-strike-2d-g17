#ifndef BROADCAST_H
#define BROADCAST_H

class OnlineClient;

#include <list>
#include <mutex>
#include <string>
#include <utility>

#include <assert.h>

#include "event.h"
#include "socket.h"
#include "onlineclient.h"
#include "queue.h"

class Broadcast {
private:
    std::mutex mtx;
    std::list<OnlineClient> onlineClients;
    Queue<Event> eventsToProcess;
    bool wasClosed;

public:
    Broadcast();

    Broadcast(const Broadcast&) = delete;
    Broadcast& operator=(const Broadcast&) = delete;

    void addClient(Socket sktNewClient, Gameloop& game);

    void disconnectInactiveClients();

    void pushEventToAll(const Event event);

    bool isClosed() const;

    void close();

    ~Broadcast();
};
#endif
