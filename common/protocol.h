#ifndef PROTOCOL_H
#define PROTOCOL_H

#include <arpa/inet.h>
#include <assert.h>

#include <cstdint>
#include <iostream>
#include <list>
#include <string>
#include <utility>
#include <vector>

#include "socket.h"

class Protocol {
   protected:
    bool wasClosed;

   protected:
    Protocol();

    void sendall(Socket& skt, const void* data, unsigned int sz);

    void recvall(Socket& skt, void* data, unsigned int sz);

   private:
    void checkIfItsClosed(const Socket& skt);

   public:
    bool isClosed() const;
};
#endif
