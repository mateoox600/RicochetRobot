#pragma once

#include <vector>

#include "Robot.hpp"
#include "Wall.hpp"
#include "Target.hpp"

struct Global {
    std::vector<Robot> robots;
    std::vector<Wall> walls;
    std::vector<Target> targets;
    int moveCount;               // Number of moves it took to win the game
    bool won;
};

extern Global global;