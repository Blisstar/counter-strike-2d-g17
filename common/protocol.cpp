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

void Protocol::checkIfItsClosed(const Socket& skt) {
    wasClosed = skt.is_stream_recv_closed() && skt.is_stream_send_closed();
}

bool Protocol::isClosed() const {
    return wasClosed;
}