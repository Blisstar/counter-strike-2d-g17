#include "lobby.h"
#include <gameinprogresserror.h>

unsigned int Lobby::createGame(std::string gameName,
                                   unsigned int hostClientId,
                                   unsigned int mapId,
                                   std::string playerName) {
    const std::lock_guard<std::mutex> lck(mtx);
    unsigned int gameId = nextGameId;
    games.emplace(std::piecewise_construct, std::forward_as_tuple(gameId), std::forward_as_tuple(*this, gameName, mapId));
    games.at(gameId).addPlayer(hostClientId, playerName);
    nextGameId++;
    return gameId;
}

void Lobby::connectGame(unsigned int gameId, unsigned int clientId, std::string playerName) {
    try {
        games.at(gameId).addPlayer(clientId, playerName);
    } catch (const GameInProgressError& e) {
        std::cerr << e.what() << '\n';
        onlineClients.at(clientId).pushMessage(ServerMessage(
            ServerMessageType::Error, ErrorMessage(ErrorType::GameInProgress)));
    }
}

void Lobby::disconnectGame(unsigned int gameId, unsigned int clientId) {
    if (gameId == 0) return;
    if (games.at(gameId).removePlayer(clientId)) {
        const std::lock_guard<std::mutex> lck(mtx);
        games.erase(gameId);
    }
}

void Lobby::startGame(unsigned int gameId, unsigned int hostClientId) {
    games.at(gameId).start(hostClientId);
}

void Lobby::pushLobbySnapshotById(unsigned int clientId) {
    //no es necesario un mutex aca porque no se esta haciendo un recorrido sobre todos los clientes
    //se trata de uno en particular, de cualquier forma si el cliente esta conectado o no lo maneja el
    //con su propio mutex, por lo tanto nunca se va a pushear a alguien que ya este desconectado
    const std::lock_guard<std::mutex> lck(mtx);
    LobbySnapshot l;
    std::cout << "se recibio un get 1" <<std::endl;
    for (auto& [gameId, game] : games) {
        l.addRoomData(gameId, game.getName(), game.getMapId(), game.getPlayersCount());
    }
    std::cout << "se recibio un get 2" <<std::endl;
    auto it = onlineClients.find(clientId);
    if (it != onlineClients.end()) it->second.pushMessage(ServerMessage(ServerMessageType::LobbySnapshot, l));
    std::cout << "se recibio un get 3" <<std::endl;
}