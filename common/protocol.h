#ifndef PROTOCOL_H
#define PROTOCOL_H

#include <cstdint>
#include <iostream>
#include <list>
#include <string>
#include <utility>
#include <vector>

#include <arpa/inet.h>
#include <assert.h>

#include "socket.h"

class Protocol {
protected:
    void sendall(Socket& skt, const void* data, unsigned int sz);

    void recvall(Socket& skt, void* data, unsigned int sz);

public:
    bool isClosed() const;
};
#endif
