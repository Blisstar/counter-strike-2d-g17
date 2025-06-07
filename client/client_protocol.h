#ifndef CLIENT_PROTOCOL_H
#define CLIENT_PROTOCOL_H

#include <arpa/inet.h>
#include <assert.h>

#include <cstdint>
#include <iostream>
#include <list>
#include <string>
#include <utility>
#include <vector>

#include "../common/defs.h"
#include "../common/protocol.h"
#include "../common/prtrecvinvalidvalue.h"

class ClientProtocol : public Protocol {
   private:
    Socket skt;

   public:
    explicit ClientProtocol(const char* servname, const char* port);

    ClientProtocol(const ClientProtocol&) = delete;
    ClientProtocol& operator=(const ClientProtocol&) = delete;

    void send_message(ClientMessage msg);

    LobbySnapshot recvLobbySnapshot();

    RoomSnapshot recvRoomSnapshot();

    void close();
};
#endif