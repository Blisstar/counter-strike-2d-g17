#include "server_protocol.h"

ServerProtocol::ServerProtocol(Socket _skt)
    : Protocol(), skt(std::move(_skt)) {}

void ServerProtocol::sendMessage(ServerMessage msg) {
    sendall(skt, &msg.type, 1);
    switch (msg.type) {
        case ServerMessageType::Error: {
            std::cout << "envio un error" << std::endl;
            ErrorMessage e = std::get<ErrorMessage>(msg.data);
            // send del enum de enviar error
            sendall(skt, &e.type, 1);
            break;
        }

        case ServerMessageType::LobbySnapshot: {
            std::cout << "envio un lobby" << std::endl;
            LobbySnapshot l = std::get<LobbySnapshot>(msg.data);
            unsigned int s = l.roomListData.size();
            sendLong(skt, s);
            for (RoomData r : l.roomListData) {
                sendLong(skt, r.gameId);
                sendString(skt, r.gameName);
                sendLong(skt, r.mapId);
                sendall(skt, &r.playersCount, 1);
            }
            break;
        }

        case ServerMessageType::RoomSnapshot: {
            std::cout << "envio un room" << std::endl;
            RoomSnapshot r = std::get<RoomSnapshot>(msg.data);
            sendall(skt, &r.isHost, 1);
            uint8_t s = r.playersCount;
            sendall(skt, &s, 1);
            break;
        }

        case ServerMessageType::GameSnapshot: {
            std::cout << "envio un game" << std::endl;
            GameSnapshot g = std::get<GameSnapshot>(msg.data);
            sendall(skt, &g.state, 1);
            uint8_t s = g.players.size();
            sendall(skt, &s, 1);
            for (PlayerSnapshot i : g.players) sendLong(skt, i.id);
            break;
        }

        default:
            break;
    }
}

ClientMessage ServerProtocol::recvMessage() {
    ClientMessageType t = ClientMessageType::InvalidClientMessage;
    ClientMessageData d = std::monostate{};  // Ensure d is initialized
    recvall(skt, &t, 1);
    switch (t) {
        case ClientMessageType::CreateGame: {
            std::string gameName = recvString(skt);
            unsigned int mapId = recvLong(skt);
            std::string playerName = recvString(skt);
            d = CreateGame(gameName, mapId, playerName);
        } break;

        case ClientMessageType::ConnectGame: {
            unsigned int gameId = recvLong(skt);
            std::string playerName = recvString(skt);
            d = ConnectGame(gameId, playerName);
        } break;

        case ClientMessageType::PlayerMessage: {
            PlayerMessageType t;
            recvall(skt, &t, 1);
            uint16_t parameter = recvShort(skt);
            d = PlayerMessage(t, parameter);
        } break;

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
