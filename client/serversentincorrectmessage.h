#ifndef SERVERSENTINCORRECTMESSAGE_H
#define SERVERSENTINCORRECTMESSAGE_H

#pragma once

#include <iostream>
#include <stdexcept>

class ServerSentIncorrectMessage: public std::exception {
public:
    const char* what() const noexcept override { return "Server has sent a incorrect message to the client"; }
};

#endif