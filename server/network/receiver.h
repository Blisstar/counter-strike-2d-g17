#ifndef RECEIVER_H
#define RECEIVER_H

class Game;

#include <assert.h>

#include <iostream>
#include <string>

#include "server_protocol.h"
#include "thread.h"

class Game;

class Receiver : public Thread {
   private:
    const unsigned int clientId;
    ServerProtocol& prt;
    Broadcast& broadcast;
    unsigned int gameId;

   public:
    Receiver(unsigned int _clientId, ServerProtocol& _prt, Broadcast& _broadcast, unsigned int _gameId);

    Receiver(const Receiver&) = delete;
    Receiver& operator=(const Receiver&) = delete;

    void run() override;
};
#endif
