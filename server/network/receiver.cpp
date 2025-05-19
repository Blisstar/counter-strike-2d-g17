#include "receiver.h"

#include "game.h"

Receiver::Receiver(unsigned int _clientId, ServerProtocol& _prt,
                   Broadcast& _broadcast, unsigned int _idGame)
    : clientId(clientId), prt(_prt), broadcast(_broadcast) {}

void Receiver::run() {
    while (!prt.isClosed()) {
        try {
            ClientMessage msg = prt.recvMessage();
            switch (msg.type)
            {
            case ClientMessageType::ConnectGame : {
                ConnectGame c = std::get<ConnectGame>(msg.data);
                broadcast.connectGame(c.gameId, clientId);
                break;
            }
            case ClientMessageType::CreateGame : {
                CreateGame c = std::get<CreateGame>(msg.data);
                gameId = broadcast.createGame(c.gameName, clientId, c.mapId);
                break;
            }
            case ClientMessageType::DisconnectGame : {
                broadcast.disconnectGame(gameId, clientId);
                gameId = 0;
                break;
            }
            case ClientMessageType::GetListGame : {
                break;
            }
            case ClientMessageType::StartGame : {
                broadcast.startGame(gameId, clientId);
                break;
            }
            default:
                break;
            }
        } catch (const std::exception& e) {
            prt.close();
            break;
        }
    }
}
