#include "receiver.h"

#include "game/game.h"
#include "broadcast.h"

Receiver::Receiver(unsigned int _clientId, ServerProtocol& _prt,
                   Broadcast& _broadcast)
    : clientId(_clientId), prt(_prt), broadcast(_broadcast), gameId(0) {}

void Receiver::run() {
    while (!prt.isClosed()) {
        try {
            ClientMessage msg = prt.recvMessage();
            switch (msg.type)
            {
            case ClientMessageType::ConnectGame : {
                std::cout << "se recibio un connect" <<std::endl;
                ConnectGame c = std::get<ConnectGame>(msg.data);
                broadcast.connectGame(c.gameId, clientId, c.playerName);
                gameId = c.gameId;
                break;
            }
            case ClientMessageType::CreateGame : {
                std::cout << "se recibio un create" <<std::endl;
                CreateGame c = std::get<CreateGame>(msg.data);
                gameId = broadcast.createGame(c.gameName, clientId, c.mapId, c.playerName);
                break;
            }
            case ClientMessageType::DisconnectGame : {
                std::cout << "se recibio un disconnect" <<std::endl;
                broadcast.disconnectGame(gameId, clientId);
                gameId = 0;
                break;
            }
            case ClientMessageType::GetListGame : {
                std::cout << "se recibio un get" <<std::endl;
                broadcast.pushLobbySnapshotById(clientId);
                break;
            }
            case ClientMessageType::StartGame : {
                std::cout << "se recibio un start" <<std::endl;
                broadcast.startGame(gameId, clientId);
                break;
            }
            default: {
                break;
            }
            }
        } catch (const std::exception& e) {
            std::cerr << "Receiver error: " << e.what() << std::endl;
            prt.close();
            break;
        }
    }
    if (gameId != 0)broadcast.disconnectGame(gameId, clientId);
}
