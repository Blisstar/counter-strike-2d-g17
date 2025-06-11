#include "protocol.h"

Protocol::Protocol() : wasClosed(false) {}

void Protocol::sendall(Socket& skt, const void* data, unsigned int sz) {
    if (!skt.is_stream_send_closed())
        skt.sendall(data, sz);
    checkIfItsClosed(skt);
}

void Protocol::recvall(Socket& skt, void* data, unsigned int sz) {
    if (!skt.is_stream_recv_closed())
        skt.recvall(data, sz);
    checkIfItsClosed(skt);
}

void Protocol::sendShort(Socket& skt, uint16_t data) {
    uint16_t d = htons(data);
    sendall(skt, &d, 2);
}

void Protocol::sendLong(Socket& skt, uint32_t data) {
    uint32_t d = htonl(data);
    sendall(skt, &d, 4);
}

uint16_t Protocol::recvShort(Socket& skt) {
    uint16_t d = 0;
    recvall(skt, &d, 2);
    return ntohs(d);
}

uint32_t Protocol::recvLong(Socket& skt) {
    uint32_t d = 0;
    recvall(skt, &d, 4);
    return ntohl(d);
}

void Protocol::sendString(Socket& skt, const std::string &data) {
    uint16_t dSize = htons(data.size());
    sendall(skt, &dSize, 2);
    sendall(skt, data.c_str(), data.size());
}

std::string Protocol::recvString(Socket& skt) {
    uint16_t dSize;
    recvall(skt, &dSize, 2);
    dSize = ntohs(dSize);

    std::vector<char> str(dSize);
    recvall(skt, str.data(), dSize);

    return std::string(str.data(), dSize);
}

void Protocol::sendFloat(Socket& skt, float data, uint16_t decimals) {
    sendShort(skt, decimals);
    uint32_t floatToInt = data * (10 ** decimals);
    sendLong(skt, floatToInt);

    return;
}

float Protocol::recvFloat(Socket& skt) {
    uint16_t decimals = recvShort(skt);
    uint32_t intData = recvLong(skt);
    float data = intData / (10 ** decimals);

    return data;
}


void Protocol::checkIfItsClosed(const Socket& skt) {
    wasClosed = skt.is_stream_recv_closed() && skt.is_stream_send_closed();
}

bool Protocol::isClosed() const {
    return wasClosed;
}