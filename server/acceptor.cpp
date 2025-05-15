#include "acceptor.h"

Acceptor::Acceptor(Socket _skt, Broadcast& _broadcast, Gameloop& _game):
        skt(std::move(_skt)), broadcast(_broadcast), game(_game) {}

void Acceptor::run() {
    game.start();
    while (_keep_running) {
        try {
            Socket newClient = skt.accept();

            reap_dead();
            broadcast.addClient(std::move(newClient), game);
        } catch (const std::exception& e) {
            kill_all();
            stop();
        }
    }
}

void Acceptor::reap_dead() { broadcast.disconnectInactiveClients(); }

void Acceptor::kill_all() { broadcast.close(); }

void Acceptor::finish() {
    if (this->is_alive()) {
        game.stop();
        game.join();
        skt.shutdown(SHUT_RDWR);
        skt.close();
        this->join();
    }
}
