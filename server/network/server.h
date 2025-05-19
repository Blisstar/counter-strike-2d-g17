#ifndef SERVER_H
#define SERVER_H

#include <assert.h>

#include <atomic>
#include <iostream>
#include <memory>
#include <string>
#include <thread>
#include <utility>

#include "acceptor.h"
#include "socket.h"

class Server {
   private:
    Socket acceptorSkt;
    Broadcast broadcast;

   public:
    explicit Server(const std::string& servName);

    Server(const Server&) = delete;
    Server& operator=(const Server&) = delete;

    void run();
};
#endif
