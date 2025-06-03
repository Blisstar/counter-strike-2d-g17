#include "client_protocol.h"
#include "defs.h"
#include "../serversentincorrectmessage.h"
#include "../servererror.h"

ClientProtocol::ClientProtocol(const char* servname, const char* port) :
    skt(Socket(servname, port)) {
    wasClosed = false;
}

LobbySnapshot ClientProtocol::recvLobbySnapshot() {
    ServerMessageType t;
    recvall(skt, &t, 1);
    if (t == ServerMessageType::Error) throw new ServerError("An error ocurred in the server");
    if (t != ServerMessageType::LobbySnapshot) throw new ServerSentIncorrectMessage();

    uint32_t s = recvLong(skt);
    LobbySnapshot l;
    for(int i = 0; i < s; i++) {
        uint32_t gameId = recvLong(skt);
        std::string gameName = recvString(skt);
        uint32_t mapId = recvLong(skt);
        uint8_t playersCount = 0;
        recvall(skt, &playersCount, 1);
        l.addRoomData(gameId, gameName, mapId, playersCount);
    }
    return l;
}

RoomSnapshot ClientProtocol::recvRoomSnapshot() {
    ServerMessageType t;
    recvall(skt, &t, 1);
    if (t == ServerMessageType::Error) throw new ServerError("An error ocurred in the server");
    if (t != ServerMessageType::RoomSnapshot) throw new ServerSentIncorrectMessage();

    bool isHost = false;
    uint8_t connectedPlayers = 0;
    recvall(skt, &isHost, 1);
    recvall(skt, &connectedPlayers, 1);
    return RoomSnapshot(isHost, connectedPlayers);
}

void ClientProtocol::send_message(ClientMessage msg) {
    sendall(skt, &msg.type, 1);
    switch (msg.type)
    {
    case ClientMessageType::CreateGame :
        {
            CreateGame c = std::get<CreateGame>(msg.data);
            sendString(skt, c.gameName);
            sendShort(skt, &c.mapId);
        }
        break;

    case ClientMessageType::ConnectGame :
        {
            ConnectGame c = std::get<ConnectGame>(msg.data);
            sendShort(skt, &c.gameId);
        }
        break;

    default:
        break;
    }   
}


void ClientProtocol::close() {
    if (!wasClosed) {
        wasClosed = true;
        skt.shutdown(SHUT_RDWR);
        skt.close();
    }
}












