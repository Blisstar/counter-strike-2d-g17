#ifndef SERVER_H
#define SERVER_H

#include <atomic>
#include <iostream>
#include <memory>
#include <string>
#include <thread>
#include <utility>

#include <assert.h>

#include "socket.h"
#include "acceptor.h"

class Server {
private:
    Socket acceptorSkt;
    Broadcast broadcast;
    Gameloop game;

public:
    explicit Server(const std::string& servName);

    Server(const Server&) = delete;
    Server& operator=(const Server&) = delete;

    void run();
};
#endif
