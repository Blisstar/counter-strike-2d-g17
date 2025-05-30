#include "client.h"



Client::Client(const char* servname, const char* port) : protocol(servname, port) {}

void Client::run() {
    while(!protocol.isClosed()) {
        try {
            std::vector<std::string> words = get_input();
            if (words.empty()) continue;
            ClientMessageType t = get_message_type(words[0]);
            ClientMessageData d;
            switch (t) {
                case ClientMessageType::CreateGame:
                    d = CreateGame(words[1], static_cast<unsigned int>(std::stoi(words[2])));
                    break;
                case ClientMessageType::ConnectGame:
                    d = ConnectGame(static_cast<unsigned int>(std::stoi(words[1])));
                    break;
                case ClientMessageType::GetListGame:
                    d = std::monostate{};
                    break;
                case ClientMessageType::DisconnectGame:
                    d = std::monostate{};
                    break;
                case ClientMessageType::StartGame:
                    d = std::monostate{};
                    break;
                default:
                    // comando inválido, podrías mostrar un mensaje de error
                    continue;
            }
            ClientMessage c(t, d);
            protocol.send_message(c);
            ServerMessage msg = protocol.recv_message();
        } catch (const std::exception& e) {
            protocol.close();
            break;
        }
    }
}


ClientMessageType Client::get_message_type(const std::string& cmd) {
    if (cmd == "crear") return ClientMessageType::CreateGame;
    if (cmd == "unirse") return ClientMessageType::ConnectGame;
    if (cmd == "listar") return ClientMessageType::GetListGame;
    if (cmd == "salir") return ClientMessageType::DisconnectGame;
    if (cmd == "iniciar") return ClientMessageType::StartGame;
    return ClientMessageType::InvalidClientMessage;
}


std::vector<std::string> Client::get_input() {
    std::string input;
    std::getline(std::cin, input);

    std::istringstream iss(input);
    std::vector<std::string> words;
    std::string word;

    while (iss >> word) {
        words.push_back(word);
    }
    return words;
}
