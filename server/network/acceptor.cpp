#include "acceptor.h"

Acceptor::Acceptor(Socket _skt, Broadcast& _broadcast)
    : skt(std::move(_skt)), broadcast(_broadcast) {}

void Acceptor::run() {
    while (should_keep_running()) {
        try {
            Socket newClient = skt.accept();
            std::cout << "se acepto al nuevo cliente" << std::endl;
            reap_dead();
            std::cout << "se eliminaron los inactivos" << std::endl;
            broadcast.addClient(std::move(newClient));
            std::cout << "se agrego el nuevo cliente" << std::endl;
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
