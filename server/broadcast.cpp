#include "broadcast.h"

Broadcast::Broadcast() : nextGameId(1), , wasClosed(false) {}

void Broadcast::addClient(Socket sktNewClient) {
    const std::lock_guard<std::mutex> lck(mtx);
    onlineClients.emplace(nextClientId, nextClientId, 0, this,
                          std::move(sktNewClient));
    onlineClients[nextClientId].connect();
    nextClientId++;
}

unsigned int Broadcast::createGame(std::string gameName,
                                   unsigned int hostClientId) {
    unsigned int gameId = nextGameId;
    games.emplace(gameId, this, gameName);
    games[gameId].addPlayer(hostClientId);
    nextGameId++;
    return gameId;
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

void Broadcast::pushSnapshotToAll(const Snapshot snapshot) {
    const std::lock_guard<std::mutex> lck(mtx);
    for (auto& [id, onlineClient] : onlineClients) {
        onlineClient.pushSnapshot(snapshot);
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
