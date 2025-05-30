#ifndef CLIENT_H
#define CLIENT_H

#include <iostream>
#include <sstream>
#include <vector>

#include "client_protocol.h"
#include "../common/defs.h"
class Client {

public:
    Client(const char* servname, const char* port);

    void run();


private:
    ClientProtocol protocol;
    void send_message(ClientMessage msg);
    ServerMessage recv_message();
    std::vector<std::string> get_input();
    ClientMessageType get_message_type(const std::string& cmd);

};

#endif