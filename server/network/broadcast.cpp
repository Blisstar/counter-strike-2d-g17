#include "broadcast.h"

Broadcast::Broadcast() : nextClientId(0), nextGameId(1), wasClosed(false) {}

void Broadcast::addClient(Socket sktNewClient) {
    const std::lock_guard<std::mutex> lck(mtx);
    onlineClients.emplace(
        std::piecewise_construct, std::forward_as_tuple(nextClientId),
        std::forward_as_tuple(nextClientId, *this, std::move(sktNewClient)));
    onlineClients.at(nextClientId).connect();
    nextClientId++;
}

unsigned int Broadcast::createGame(std::string gameName,
                                   unsigned int hostClientId,
                                   unsigned int mapId) {
    const std::lock_guard<std::mutex> lck(mtx);
    unsigned int gameId = nextGameId;
    games.emplace(std::piecewise_construct, std::forward_as_tuple(gameId), std::forward_as_tuple(*this, gameName, mapId));
    games.at(gameId).addPlayer(hostClientId);
    nextGameId++;
    return gameId;
}

void Broadcast::connectGame(unsigned int gameId, unsigned int clientId) {
    try {
        games.at(gameId).addPlayer(clientId);
    } catch (const GameInProgressError& e) {
        std::cerr << e.what() << '\n';
        onlineClients.at(clientId).pushMessage(ServerMessage(
            ServerMessageType::Error, ErrorMessage(ErrorType::GameInProgress)));
    }
}

void Broadcast::disconnectGame(unsigned int gameId, unsigned int clientId) {
    if (!games.at(gameId).removePlayer(clientId)) {
        const std::lock_guard<std::mutex> lck(mtx);
        games.erase(gameId);
    }
}

void Broadcast::startGame(unsigned int gameId, unsigned int hostClientId) {
    games.at(gameId).start(hostClientId);
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
