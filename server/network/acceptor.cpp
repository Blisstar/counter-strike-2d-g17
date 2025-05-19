#include "acceptor.h"

Acceptor::Acceptor(Socket _skt, Broadcast& _broadcast)
    : skt(std::move(_skt)), broadcast(_broadcast) {}

void Acceptor::run() {
    while (should_keep_running()) {
        try {
            Socket newClient = skt.accept();

            reap_dead();
            broadcast.addClient(std::move(newClient));
        } catch (const std::exception& e) {
            kill_all();
            stop();
        }
    }
}

void Acceptor::reap_dead() {
    broadcast.disconnectInactiveClients();
}

void Acceptor::kill_all() {
    broadcast.close();
}

void Acceptor::finish() {
    if (this->is_alive()) {
        skt.shutdown(SHUT_RDWR);
        skt.close();
        this->join();
    }
}
