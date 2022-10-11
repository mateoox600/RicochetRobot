
#include "Robot.hpp"

#include "Constants.hpp"
#include "Global.hpp"

#include "Wall.hpp"

Robot::Robot(int id, raylib::Vector2 position, raylib::Color color) : id(id), position(position), color(color) {
    //printf("x: %f, y: %f\n", position.x, position.y);
}

void Robot::update() {
    
}

void Robot::move(raylib::Vector2 dir) {
    bool blocked = false;
    positionLog.insert(positionLog.begin(), position);
    raylib::Vector2 newPosition = position;
    raylib::Vector2 oldPosition = position;
    while(!blocked) {
        oldPosition = newPosition;
        newPosition += dir;

        if(
            newPosition.x < 0 || newPosition.x >= Constants::SCREEN_WIDTH / Constants::CELL_SIZE ||
            newPosition.y < 0 || newPosition.y >= Constants::SCREEN_WIDTH / Constants::CELL_SIZE
        ) blocked = true;

        for(Robot robot : global.robots) {
            if(newPosition == robot.getPosition()) {
                blocked = true;
                break;
            }
        }

        for(Wall wall : global.walls) {

            raylib::Vector2* collisionPoint = nullptr;
            bool collision = (oldPosition + raylib::Vector2(0.5, 0.5)).CheckCollisionLines((newPosition + raylib::Vector2(0.5, 0.5)), wall.position, wall.position + raylib::Vector2(wall.dir.y, wall.dir.x), collisionPoint);
            
            if(collision) {
                blocked = true;
                break;
            }
        }
    }
    position = newPosition - dir;
}

void Robot::draw() {
    (position * Constants::CELL_SIZE + Constants::halfCell).DrawCircle(Constants::CELL_SIZE * 0.45, color);
    raylib::Vector2 lastPos = position;
    for(raylib::Vector2 oldPos : positionLog) {
        (lastPos * Constants::CELL_SIZE + Constants::halfCell).DrawLine(oldPos * Constants::CELL_SIZE + Constants::halfCell, color);
        lastPos = oldPos;
    }
}

int Robot::getId() {
    return id;
}

raylib::Vector2 Robot::getPosition() {
    return position;
}

raylib::Color Robot::getColor() {
    return color;
}

bool Robot::isSelected() {
    return selected;
}

void Robot::select() {
    selected = true;
}

void Robot::unselect() {
    selected = false;
}