#pragma once

#include "raylib-cpp.hpp"

struct Wall {
    raylib::Vector2 position; // Position of the wall
    raylib::Vector2 dir;      // Direction of the wall (direction it's blocking ex: (1, 0) blocks deplacement on the x axis so it's a vectical wall)
};