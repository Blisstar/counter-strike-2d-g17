#include "server_protocol.h"

ServerProtocol::ServerProtocol(Socket _skt)
    : Protocol(), skt(std::move(_skt)) {}

void ServerProtocol::sendMessage(ServerMessage msg) {
    char v = SERV_SEND_EVENT;
    sendall(skt, &v, 1);
    uint16_t enemiesAliveCnt = htons(event.enemiesAliveCnt);
    uint16_t enemiesDeadCnt = htons(event.enemiesDeadCnt);
    sendall(skt, &enemiesAliveCnt, 2);
    sendall(skt, &enemiesDeadCnt, 2);
    sendall(skt, &event.type, 1);
}

ClientMessage ServerProtocol::recvMessage() {
    ClientMessageType t = ClientMessageType::InvalidClientMessage;
    ClientMessageData d;
    recvall(skt, &t, 1);
    switch (t)
    {
    case ClientMessageType::ConnectGame :
        /* code */
        break;
    
    default:
        break;
    }
}

void ServerProtocol::close() {
    if (!wasClosed) {
        wasClosed = true;
        skt.shutdown(SHUT_RDWR);
        skt.close();
    }
}
