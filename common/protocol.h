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

    void sendShort(Socket& skt, uint16_t data);

    void sendLong(Socket& skt, uint32_t data);

    uint16_t recvShort(Socket& skt);

    uint32_t recvLong(Socket& skt);

    void sendString(Socket& skt, const std::string &data);

    std::string recvString(Socket& skt);

    void sendFloat(Socket& skt, float data, uint16_t decimals);
    
    float recvFloat(Socket& skt);
    
   private:
    void checkIfItsClosed(const Socket& skt);

   public:
    bool isClosed() const;
};

#endif
