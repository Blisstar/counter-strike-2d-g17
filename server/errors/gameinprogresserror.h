#ifndef GAMEINPROGRESSERROR_H
#define GAMEINPROGRESSERROR_H

#pragma once

#include <iostream>
#include <stdexcept>

class GameInProgressError: public std::exception {
public:
    const char* what() const noexcept override { return "Game in progress, nobody can join it."; }
};

#endif