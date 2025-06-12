#ifndef RECEIVER_H
#define RECEIVER_H

class Game;

#include <assert.h>

#include <iostream>
#include <string>

#include "../common/thread.h"
#include "server_protocol.h"

class Game;
class Lobby;

class Receiver : public Thread {
   private:
    const unsigned int clientId;
    ServerProtocol& prt;
    Lobby& lobby;
    unsigned int gameId;

   public:
    Receiver(unsigned int _clientId, ServerProtocol& _prt, Lobby& _lobby);

    Receiver(const Receiver&) = delete;
    Receiver& operator=(const Receiver&) = delete;

    void run() override;
};
#endif
