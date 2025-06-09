#include "client_protocol.h"

#include "../common/defs.h"
#include "servererror.h"
#include "serversentincorrectmessage.h"

ClientProtocol::ClientProtocol(const char* servname, const char* port)
    : skt(Socket(servname, port)) {
    wasClosed = false;
}

LobbySnapshot ClientProtocol::recvLobbySnapshot() {
    ServerMessageType t;
    recvall(skt, &t, 1);

    std::cout << "Tipo de mensaje recibido: " << static_cast<int>(t) << std::endl;
    if (t == ServerMessageType::Error)
        throw new ServerError("An error ocurred in the server");
    if (t != ServerMessageType::LobbySnapshot)
        throw new ServerSentIncorrectMessage();

    uint32_t s = recvLong(skt);
    std::cout << "La cantidad de rooms que hay es: " << s << std::endl;
    LobbySnapshot l;
    for (int i = 0; i < s; i++) {
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
    if (t == ServerMessageType::Error)
        throw new ServerError("An error ocurred in the server");
    if (t != ServerMessageType::RoomSnapshot)
        throw new ServerSentIncorrectMessage();

    bool isHost = false;
    uint8_t connectedPlayers = 0;
    recvall(skt, &isHost, 1);
    recvall(skt, &connectedPlayers, 1);
    return RoomSnapshot(isHost, connectedPlayers);
}



PlayerSnapshot ClientProtocol::recvPlayerSnapshot() {
    
}


GameSnapshot ClientProtocol::recvGameSnapshot() {

}



void ClientProtocol::send_message(ClientMessage msg) {
    sendall(skt, &msg.type, 1);
    std::cout << "envio un " << static_cast<int>(msg.type) << std::endl;
    switch (msg.type) {
        case ClientMessageType::CreateGame: {
            CreateGame c = std::get<CreateGame>(msg.data);
            sendString(skt, c.gameName);
            sendLong(skt, c.mapId);
            sendString(skt, c.playerName);
        } break;

        case ClientMessageType::ConnectGame: {
            ConnectGame c = std::get<ConnectGame>(msg.data);
            sendLong(skt, c.gameId);
            sendString(skt, c.playerName);
        } break;

        case ClientMessageType::PlayerMessage: {
            PlayerMessage c = std::get<PlayerMessage>(msg.data);
            sendall(skt, &c.type, 1);
            sendShort(skt, c.firstParameter);
        } break;

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
