#pragma once

#include <vector>
#include "raylib-cpp.hpp"

class Robot {
private:
    int id;                                   // Id of the robot alias it's position in the robots vector
    raylib::Vector2 position;
    raylib::Color color;                      // Color of the robot

    std::vector<raylib::Vector2> positionLog; // Vector of all the position the robot has been to

    bool selected = false;                    // If the robot is currently selected by the player
public:
    Robot(int id, raylib::Vector2 position, raylib::Color color);

    void move(raylib::Vector2 dir);
    void draw();

    void reset();

    int getId();
    raylib::Vector2 getPosition();
    void setPosition(raylib::Vector2 newPosition);
    raylib::Color getColor();
    bool isSelected();
    void select();
    void unselect();
};