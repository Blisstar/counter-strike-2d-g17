#ifndef ACCEPTOR_H
#define ACCEPTOR_H

#include <cstdint>
#include <iostream>
#include <memory>
#include <string>
#include <utility>

#include <arpa/inet.h>
#include <assert.h>

#include "socket.h"
#include "gameloop.h"
#include "thread.h"

class Acceptor: public Thread {
private:
    Socket skt;
    Broadcast& broadcast;
    Gameloop& game;

public:
    Acceptor(Socket _skt, Broadcast& _broadcast, Gameloop& _game);

    Acceptor(const Acceptor&) = delete;
    Acceptor& operator=(const Acceptor&) = delete;

    void run() override;

    void finish();

    void reap_dead();

    void kill_all();
};
#endif
