#ifndef SERVERERROR_H
#define SERVERERROR_H

#pragma once

#include <iostream>
#include <stdexcept>

class ServerError: public std::exception {
private:
    std::string errorMsg;

public:
    ServerError(std::string _errorMsg) : errorMsg(_errorMsg) {}

    const char* what() const noexcept override { return errorMsg.c_str(); }
};

#endif