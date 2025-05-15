#ifndef PRT_RECV_INVALID_VALUE_H
#define PRT_RECV_INVALID_VALUE_H

#include <iostream>
#include <stdexcept>

class PrtRecvInvalidValue: public std::exception {
public:
    const char* what() const noexcept override { return "El protocolo recibió un valor invalido"; }
};
#endif
