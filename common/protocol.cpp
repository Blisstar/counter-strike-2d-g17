#include "protocol.h"

void Protocol::sendall(Socket& skt, const void* data, unsigned int sz) {
    if (!skt.is_stream_send_closed())
        skt.sendall(data, sz);
}

void Protocol::recvall(Socket& skt, void* data, unsigned int sz) {
    if (!skt.is_stream_recv_closed())
        skt.recvall(data, sz);
}

bool Protocol::isClosed() const { return wasClosed; }
