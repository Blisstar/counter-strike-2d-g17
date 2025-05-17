#include "server_protocol.h"

ServerProtocol::ServerProtocol(Socket _skt) : Protocol(), skt(std::move(_skt)) {}

void ServerProtocol::sendEvent(const Event& event) {
    char v = SERV_SEND_EVENT;
    sendall(skt, &v, 1);
    uint16_t enemiesAliveCnt = htons(event.enemiesAliveCnt);
    uint16_t enemiesDeadCnt = htons(event.enemiesDeadCnt);
    sendall(skt, &enemiesAliveCnt, 2);
    sendall(skt, &enemiesDeadCnt, 2);
    sendall(skt, &event.type, 1);
}

EventType ServerProtocol::recvEvent() {
    char v = 0;
    recvall(skt, &v, 1);
    if (v == SERV_RECV_ATTACK) {
        return ENEMYDEAD;
    } else {
        throw PrtRecvInvalidValue();
    }
}

void ServerProtocol::close() {
    if (!wasClosed) {
        wasClosed = true;
        skt.shutdown(SHUT_RDWR);
        skt.close();
    }
}
