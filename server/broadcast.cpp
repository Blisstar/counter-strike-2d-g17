#include "broadcast.h"

Broadcast::Broadcast(): wasClosed(false) {}

void Broadcast::addClient(Socket sktNewClient, Gameloop& game) {
    const std::lock_guard<std::mutex> lck(mtx);
    onlineClients.emplace_back(game, std::move(sktNewClient)).connect();
}

void Broadcast::disconnectInactiveClients() {
    const std::lock_guard<std::mutex> lck(mtx);
    onlineClients.remove_if([](OnlineClient& c) { return c.isDisconnect(); });
}

void Broadcast::pushEventToAll(const Event event) {
    const std::lock_guard<std::mutex> lck(mtx);
    for (OnlineClient& client: onlineClients) {
        client.pushEvent(event);
    }
}

bool Broadcast::isClosed() const { return wasClosed; }

void Broadcast::close() {
    const std::lock_guard<std::mutex> lck(mtx);
    wasClosed = true;
    onlineClients.clear();
}

Broadcast::~Broadcast() { close(); }
