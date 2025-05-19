#ifndef SERVER_PROTOCOL_H
#define SERVER_PROTOCOL_H

#include <cstdint>
#include <iostream>
#include <list>
#include <string>
#include <utility>
#include <vector>

#include <arpa/inet.h>
#include <assert.h>

#include "defs.h"
#include "protocol.h"
#include "prtrecvinvalidvalue.h"

class ServerProtocol: public Protocol {
private:
    Socket skt;

public:
    explicit ServerProtocol(Socket _skt);

    ServerProtocol(const ServerProtocol&) = delete;
    ServerProtocol& operator=(const ServerProtocol&) = delete;

    void sendEvent(const Event& event);

    EventType recvEvent();

    void close();
};
#endif
