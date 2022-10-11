#pragma once

#include <vector>

#include "Robot.hpp"
#include "Wall.hpp"

struct Global {
    std::vector<Robot> robots;
    std::vector<Wall> walls;
    int moveCount;
};

extern Global global;