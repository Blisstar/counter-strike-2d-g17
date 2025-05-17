#ifndef ACCEPTOR_H
#define ACCEPTOR_H

#include <arpa/inet.h>
#include <assert.h>

#include <cstdint>
#include <iostream>
#include <memory>
#include <string>
#include <utility>

#include "game.h"
#include "socket.h"
#include "thread.h"

class Acceptor : public Thread {
   private:
    Socket skt;
    Broadcast& broadcast;

   public:
    Acceptor(Socket _skt, Broadcast& _broadcast);

    Acceptor(const Acceptor&) = delete;
    Acceptor& operator=(const Acceptor&) = delete;

    void run() override;

    void finish();

    void reap_dead();

    void kill_all();
};
#endif
