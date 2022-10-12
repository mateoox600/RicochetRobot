#pragma once

#include "raylib-cpp.hpp"

struct Target {
    bool selectedTarget;      // If this target is selected
    raylib::Vector2 position; // Target position
    raylib::Color color;      // Target color
};
