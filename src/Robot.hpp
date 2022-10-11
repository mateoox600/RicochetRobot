#pragma once

#include <vector>
#include "raylib-cpp.hpp"

class Robot {
private:
    int id;
    raylib::Vector2 position;
    raylib::Color color;

    std::vector<raylib::Vector2> positionLog;

    bool selected = false;
public:
    Robot(int id, raylib::Vector2 position, raylib::Color color);

    void update();
    void move(raylib::Vector2 dir);
    void draw();

    int getId();
    raylib::Vector2 getPosition();
    raylib::Color getColor();
    bool isSelected();
    void select();
    void unselect();
};