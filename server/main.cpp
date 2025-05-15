#include <iostream>

#include "server.h"

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "error: The interface is:\n./server <port>" << std::endl;
        return -1;
    }

    Server server(argv[1]);
    server.run();
}
