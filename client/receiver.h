#ifndef RECEIVER_H
#define RECEIVER_H

class Game;

#include <assert.h>

#include <iostream>
#include <string>

#include "../common/thread.h"
#include "client_protocol.h"

class Game;

class Receiver : public Thread {

   private:
    const unsigned int clientId;
    ServerProtocol& prt;
    unsigned int gameId;

   public:
    Receiver(ClientProtocol& _prt);

    Receiver(const Receiver&) = delete;
    Receiver& operator=(const Receiver&) = delete;

    void run() override;
};
#endif
