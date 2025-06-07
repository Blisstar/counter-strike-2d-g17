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
                                   unsigned int mapId,
                                   std::string playerName) {
    const std::lock_guard<std::mutex> lck(mtx);
    unsigned int gameId = nextGameId;
    games.emplace(std::piecewise_construct, std::forward_as_tuple(gameId), std::forward_as_tuple(*this, gameName, mapId));
    games.at(gameId).addPlayer(hostClientId, playerName);
    nextGameId++;
    return gameId;
}

void Broadcast::connectGame(unsigned int gameId, unsigned int clientId, std::string playerName) {
    try {
        games.at(gameId).addPlayer(clientId, playerName);
    } catch (const GameInProgressError& e) {
        std::cerr << e.what() << '\n';
        onlineClients.at(clientId).pushMessage(ServerMessage(
            ServerMessageType::Error, ErrorMessage(ErrorType::GameInProgress)));
    }
}

void Broadcast::disconnectGame(unsigned int gameId, unsigned int clientId) {
    if (gameId == 0) return;
    if (games.at(gameId).removePlayer(clientId)) {
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
        onlineClient.pushMessage(msg);
    }
}

void Broadcast::pushMessageById(unsigned int clientId, ServerMessage msg) {
    //no es necesario un mutex aca porque no se esta haciendo un recorrido sobre todos los clientes
    //se trata de uno en particular, de cualquier forma si el cliente esta conectado o no lo maneja el
    //con su propio mutex, por lo tanto nunca se va a pushear a alguien que ya este desconectado
    auto it = onlineClients.find(clientId);
    if (it != onlineClients.end()) it->second.pushMessage(msg);
}

void Broadcast::pushLobbySnapshotById(unsigned int clientId) {
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
