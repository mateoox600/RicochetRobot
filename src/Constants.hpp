#pragma once

#include <string>
#include "raylib-cpp.hpp"

namespace Constants {

    const int SCREEN_WIDTH = 800;                     // Width of the game window
    const int SCREEN_HEIGHT = 800;                    // Height of the game window
    const std::string TITLE_NAME = "Ricochet Robots"; // Title of the game window
    const int CELL_SIZE = 50;                         // Size of a cell
    const raylib::Vector2 halfCell(25, 25);           // Vector size of half a cell (usefull for cell position to screen position conversion)

}