#include "broadcast.h"

Broadcast::Broadcast() : nextGameId(1), nextClientId(0), wasClosed(false) {}

void Broadcast::addClient(Socket sktNewClient) {
    const std::lock_guard<std::mutex> lck(mtx);
    onlineClients.emplace(nextClientId, nextClientId, 0, this,
                          std::move(sktNewClient));
    onlineClients[nextClientId].connect();
    nextClientId++;
}

unsigned int Broadcast::createGame(std::string gameName,
                                   unsigned int hostClientId,
                                   unsigned int mapId) {
    const std::lock_guard<std::mutex> lck(mtx);
    unsigned int gameId = nextGameId;
    games.emplace(gameId, this, gameName, mapId);
    games[gameId].addPlayer(hostClientId);
    nextGameId++;
    return gameId;
}

void Broadcast::connectGame(unsigned int gameId, unsigned int clientId) {
    try {
        games[gameId].addPlayer(clientId);
    } catch (const GameInProgressError& e) {
        std::cerr << e.what() << '\n';
        onlineClients[clientId].pushMessage(ServerMessage(
            ServerMessageType::Error, ErrorMessage(ErrorType::GameInProgress)));
    }
}

void Broadcast::disconnectGame(unsigned int gameId, unsigned int clientId) {
    if (!games[gameId].removePlayer(clientId)) {
        const std::lock_guard<std::mutex> lck(mtx);
        games.erase(gameId);
    }
}

void Broadcast::startGame(unsigned int gameId, unsigned int hostClientId) {
    games[gameId].start(hostClientId);
}

void Broadcast::disconnectInactiveClients() {
    const std::lock_guard<std::mutex> lck(mtx);
    for (auto it = onlineClients.begin(); it != onlineClients.end();) {
        if (it->second.isDisconnect()) {
            it = onlineClients.erase(
                it);  // erase devuelve el siguiente iterador
        } else {
            ++it;
        }
    }
}

void Broadcast::pushMessageToAll(ServerMessage msg) {
    const std::lock_guard<std::mutex> lck(mtx);
    for (auto& [id, onlineClient] : onlineClients) {
        onlineClient.pushMessage(std::move(msg));
    }
}

bool Broadcast::isClosed() const {
    return wasClosed;
}

void Broadcast::close() {
    const std::lock_guard<std::mutex> lck(mtx);
    wasClosed = true;
    onlineClients.clear();
}

Broadcast::~Broadcast() {
    close();
}
