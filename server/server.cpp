#include "server.h"

Server::Server(const std::string& servName): acceptorSkt(servName.c_str()), game(broadcast) {}

void Server::run() {
    Acceptor acceptor(std::move(acceptorSkt), broadcast);

    acceptor.start();

    std::string line;
    while (std::getline(std::cin, line) && line != "q") {}

    acceptor.finish();
}
