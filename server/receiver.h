#ifndef RECEIVER_H
#define RECEIVER_H

class Gameloop;

#include <iostream>
#include <string>

#include <assert.h>

#include "server_protocol.h"
#include "thread.h"

class Gameloop;

class Receiver: public Thread {
private:
    ServerProtocol& prt;
    Gameloop& game;

public:
    Receiver(ServerProtocol& _prt, Gameloop& _game);

    Receiver(const Receiver&) = delete;
    Receiver& operator=(const Receiver&) = delete;

    void run() override;
};
#endif
