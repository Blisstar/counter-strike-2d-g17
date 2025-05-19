#ifndef SERVER_PROTOCOL_H
#define SERVER_PROTOCOL_H

#include <arpa/inet.h>
#include <assert.h>

#include <cstdint>
#include <iostream>
#include <list>
#include <string>
#include <utility>
#include <vector>

#include "defs.h"
#include "protocol.h"
#include "prtrecvinvalidvalue.h"

class ServerProtocol : public Protocol {
   private:
    Socket skt;

   public:
    explicit ServerProtocol(Socket _skt);

    ServerProtocol(const ServerProtocol&) = delete;
    ServerProtocol& operator=(const ServerProtocol&) = delete;

    void sendMessage(ServerMessage msg);

    ClientMessage recvMessage();

    void close();
};
#endif
