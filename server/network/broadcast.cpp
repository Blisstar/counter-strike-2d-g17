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
