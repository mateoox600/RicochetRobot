
#include "Robot.hpp"

#include "Constants.hpp"
#include "Global.hpp"

#include "Wall.hpp"
#include "Target.hpp"

// Intisialize the robot with passed values (could ignore position but usefull to have when debugging)
Robot::Robot(int id, raylib::Vector2 position, raylib::Color color) : id(id), position(position), color(color) { }

void Robot::move(raylib::Vector2 dir) { // dir is a vector of movement ex: (1, 0) is down (0, -1) is left

    // Insert old position in the position log (Duplicates could apear but they are not to worry about)
    positionLog.insert(positionLog.begin(), position);

    raylib::Vector2 newPosition = position; // The new position used to compute movements
    raylib::Vector2 oldPosition = position; // Used to compute wall collision
    int moved = -1;                         // Number of cell moved (starts at -1 because it count one too much when the movement is blocked)
    bool blocked = false;                   // If the robot is blocked in it's movements

    while(!blocked) {
        // Setting old position to new position and the adding the direction to the new position, and counting a movement
        oldPosition = newPosition;
        newPosition += dir;
        moved++;

        // If the movement makes the robot go out of the map we block it
        if(
            newPosition.x < 0 || newPosition.x >= Constants::SCREEN_WIDTH / Constants::CELL_SIZE ||
            newPosition.y < 0 || newPosition.y >= Constants::SCREEN_WIDTH / Constants::CELL_SIZE
        ) blocked = true;

        // Check if the new cell position does not contain a robot if it's the case we block the robot
        for(Robot robot : global.robots) {
            if(newPosition == robot.getPosition()) {
                blocked = true;
                break;
            }
        }

        // Checking wall collision
        for(Wall wall : global.walls) {

            raylib::Vector2* collisionPoint = nullptr;
            // Checking collision between the line of the old position to the new position and the wall line
            bool collision = (oldPosition + raylib::Vector2(0.5, 0.5)).CheckCollisionLines((newPosition + raylib::Vector2(0.5, 0.5)), wall.position, wall.position + raylib::Vector2(wall.dir.y, wall.dir.x), collisionPoint);
            
            // Block the robot if a collision occurs
            if(collision) {
                blocked = true;
                break;
            }
        }
    } // END LOOP

    // If we moved more than 0 times we add one to the global movements count
    if(moved > 0) {
        global.moveCount++;
    }

    // Change the position (We remove the dir because the newPosition is always one space to far)
    position = newPosition - dir;

    // Checking if the robot has reach the selected target
    for(Target target : global.targets) {
        if(!target.selectedTarget) continue;
        if(target.color != color) return;       // If the color is not the same we return
        if(target.position != position) return; // If the position is not the same we return
        global.won = true; // if the color of the robot and the target match and that they are in the same space the player won
    }
}

void Robot::draw() {
    // Draws a circle to represent the robot, the radius of this circle is 45% of the cell size
    (position * Constants::CELL_SIZE + Constants::halfCell).DrawCircle(Constants::CELL_SIZE * 0.45, color);
    
    // Loops over the position log to draw lines to represent robot old movements
    raylib::Vector2 lastPos = position;
    for(raylib::Vector2 oldPos : positionLog) {
        (lastPos * Constants::CELL_SIZE + Constants::halfCell).DrawLine(oldPos * Constants::CELL_SIZE + Constants::halfCell, color);
        lastPos = oldPos;
    }
}

void Robot::reset() {
    // Resets the robot by clearing the positionLog and unselecting the robot
    positionLog.clear();
    selected = false;
}

int Robot::getId() {
    return id;
}

raylib::Vector2 Robot::getPosition() {
    return position;
}

void Robot::setPosition(raylib::Vector2 newPosition) {
    position = newPosition;
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