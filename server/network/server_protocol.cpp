#include "server_protocol.h"

ServerProtocol::ServerProtocol(Socket _skt)
    : Protocol(), skt(std::move(_skt)) {}

void ServerProtocol::sendMessage(ServerMessage msg) {
    sendall(skt, &msg.type, 1);
    switch (msg.type)
    {
    case ServerMessageType::Error :
        ErrorMessage e = std::get<ErrorMessage>(msg.data);
        sendall(skt, &e.type, 1);
        break;

    case ServerMessageType::LobbySnapshot :
        /* code */
        break;

    case ServerMessageType::RoomSnapshot :
        /* code */
        break;
        
    case ServerMessageType::GameSnapshot :
        /* code */
        break;
        
    default:
        break;
    }
}

ClientMessage ServerProtocol::recvMessage() {
    ClientMessageType t = ClientMessageType::InvalidClientMessage;
    ClientMessageData d = std::monostate{}; // Ensure d is initialized
    recvall(skt, &t, 1);
    switch (t)
    {
    case ClientMessageType::CreateGame :
        {
            std::string gameName = recvString(skt);
            unsigned int mapId = recvShort(skt);
            d = CreateGame(gameName, mapId);
        }
        break;

    case ClientMessageType::ConnectGame :
        {
            unsigned int gameId = recvShort(skt);
            d = ConnectGame(gameId);
        }
        break;
    
    default:
        break;
    }
    return ClientMessage{t, d};
}

void ServerProtocol::close() {
    if (!wasClosed) {
        wasClosed = true;
        skt.shutdown(SHUT_RDWR);
        skt.close();
    }
}
