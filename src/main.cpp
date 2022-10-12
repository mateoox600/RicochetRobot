
#include <vector>
#include <set>
#include <math.h>
#include "raylib-cpp.hpp"

#include "Constants.hpp"
#include "Global.hpp"

#include "Robot.hpp"
#include "Wall.hpp"
#include "Target.hpp"

// Global object initialisation
Global global;

void randomRobotPosition() {
    // A vector of robot position generated (will have 5 vector at the end)
    std::vector<raylib::Vector2> robotPos;

    do {
        // Randomizing a vector to add to the positions
        raylib::Vector2 toAdd(floor(rand() % (Constants::SCREEN_WIDTH / Constants::CELL_SIZE)), floor(rand() % (Constants::SCREEN_WIDTH / Constants::CELL_SIZE)));
        
        // Searching if the vector already exists in the positions (to avoid placing multiple robots on the same spot)
        bool exists = false;
        for(raylib::Vector2 pos : robotPos) {
            if(pos == toAdd) {
                exists = true;
                break;
            }
        }
        // We continue the loop if the vector already exists
        if(exists) continue;
        // We push it in the positions vector if not
        robotPos.push_back(toAdd);
    } while (robotPos.size() < 5); // Loop until we have 5 vector

    // Looping over all the robots to reset them
    for(size_t i = 0; i < 5; i++) {
        global.robots[i].reset();
        // Setting up the new randomized positions
        global.robots[i].setPosition(robotPos[i]);
    }
}

void randomTarget() {
    // Reseting all targets to not selected
    for(size_t i = 0; i < global.targets.size(); i++) {
        global.targets[i].selectedTarget = false;
    }
    // Selecting a target that will be the player goal
    global.targets[floor(rand() % global.targets.size())].selectedTarget = true; 
}

void resetGame() {
    // Randomizes all robots, the target and resets all the changing values to default
    randomRobotPosition();
    randomTarget();
    global.moveCount = 0;
    global.won = false;
}


int main(int argc, char const *argv[]) {

    // Creating the window with values from Constants namespace and setting the window fps to 60
    raylib::Window window(Constants::SCREEN_WIDTH, Constants::SCREEN_HEIGHT, Constants::TITLE_NAME);
    window.SetTargetFPS(60);

    // Creating default robot in a vector
    std::vector<Robot> robots {
        Robot(0, raylib::Vector2(0, 0), GREEN),
        Robot(1, raylib::Vector2(0, 0), RED),
        Robot(2, raylib::Vector2(0, 0), YELLOW),
        Robot(3, raylib::Vector2(0, 0), GRAY),
        Robot(4, raylib::Vector2(0, 0), BLUE)
    };

    // Creating default walls for the map (they wont change as they are fixed in place)
    std::vector<Wall> walls {
        Wall { raylib::Vector2(2, 0), raylib::Vector2(1, 0) },
        Wall { raylib::Vector2(0, 7), raylib::Vector2(0, 1) },
        Wall { raylib::Vector2(1, 4), raylib::Vector2(1, 0) },
        Wall { raylib::Vector2(1, 5), raylib::Vector2(0, 1) },
        Wall { raylib::Vector2(3, 1), raylib::Vector2(0, 1) },
        Wall { raylib::Vector2(3, 1), raylib::Vector2(1, 0) },
        Wall { raylib::Vector2(12, 0), raylib::Vector2(1, 0) },
        Wall { raylib::Vector2(12, 2), raylib::Vector2(1, 0) },
        Wall { raylib::Vector2(11, 3), raylib::Vector2(0, 1) },
        Wall { raylib::Vector2(13, 3), raylib::Vector2(0, 1) },
        Wall { raylib::Vector2(14, 3), raylib::Vector2(1, 0) },
        Wall { raylib::Vector2(10, 4), raylib::Vector2(1, 0) },
        Wall { raylib::Vector2(10, 5), raylib::Vector2(0, 1) },
        Wall { raylib::Vector2(12, 5), raylib::Vector2(0, 1) },
        Wall { raylib::Vector2(12, 5), raylib::Vector2(1, 0) },
        Wall { raylib::Vector2(7, 3), raylib::Vector2(1, 0) },
        Wall { raylib::Vector2(6, 4), raylib::Vector2(0, 1) },
        Wall { raylib::Vector2(15, 6), raylib::Vector2(0, 1) },
        Wall { raylib::Vector2(4, 6), raylib::Vector2(0, 1) },
        Wall { raylib::Vector2(5, 6), raylib::Vector2(1, 0) },
        Wall { raylib::Vector2(7, 7), raylib::Vector2(0, 1) },
        Wall { raylib::Vector2(8, 7), raylib::Vector2(0, 1) },
        Wall { raylib::Vector2(7, 9), raylib::Vector2(0, 1) },
        Wall { raylib::Vector2(8, 9), raylib::Vector2(0, 1) },
        Wall { raylib::Vector2(7, 7), raylib::Vector2(1, 0) },
        Wall { raylib::Vector2(7, 8), raylib::Vector2(1, 0) },
        Wall { raylib::Vector2(9, 7), raylib::Vector2(1, 0) },
        Wall { raylib::Vector2(9, 8), raylib::Vector2(1, 0) },
        Wall { raylib::Vector2(0, 14), raylib::Vector2(0, 1) },
        Wall { raylib::Vector2(1, 11), raylib::Vector2(1, 0) },
        Wall { raylib::Vector2(1, 11), raylib::Vector2(0, 1) },
        Wall { raylib::Vector2(5, 11), raylib::Vector2(0, 1) },
        Wall { raylib::Vector2(5, 10), raylib::Vector2(1, 0) },
        Wall { raylib::Vector2(9, 11), raylib::Vector2(0, 1) },
        Wall { raylib::Vector2(10, 10), raylib::Vector2(1, 0) },
        Wall { raylib::Vector2(14, 9), raylib::Vector2(1, 0) },
        Wall { raylib::Vector2(14, 10), raylib::Vector2(0, 1) },
        Wall { raylib::Vector2(15, 12), raylib::Vector2(0, 1) },
        Wall { raylib::Vector2(12, 11), raylib::Vector2(0, 1) },
        Wall { raylib::Vector2(12, 11), raylib::Vector2(1, 0) },
        Wall { raylib::Vector2(10, 14), raylib::Vector2(0, 1) },
        Wall { raylib::Vector2(11, 14), raylib::Vector2(1, 0) },
        Wall { raylib::Vector2(8, 13), raylib::Vector2(1, 0) },
        Wall { raylib::Vector2(8, 13), raylib::Vector2(0, 1) },
        Wall { raylib::Vector2(6, 12), raylib::Vector2(0, 1) },
        Wall { raylib::Vector2(7, 12), raylib::Vector2(1, 0) },
        Wall { raylib::Vector2(3, 15), raylib::Vector2(0, 1) },
        Wall { raylib::Vector2(4, 14), raylib::Vector2(1, 0) },
        Wall { raylib::Vector2(6, 15), raylib::Vector2(1, 0) },
        Wall { raylib::Vector2(13, 15), raylib::Vector2(1, 0) }
    };

    // Setting up defaults target for reachable spots
    std::vector<Target> targets {
        Target { false, raylib::Vector2(3, 1), GREEN },
        Target { false, raylib::Vector2(11, 2), RED },
        Target { false, raylib::Vector2(13, 3), YELLOW },
        Target { false, raylib::Vector2(6, 3), BLUE },
        Target { false, raylib::Vector2(1, 4), RED },
        Target { false, raylib::Vector2(10, 4), GREEN },
        Target { false, raylib::Vector2(12, 5), BLUE },
        Target { false, raylib::Vector2(4, 6), BLUE },
        Target { false, raylib::Vector2(14, 9), YELLOW },
        Target { false, raylib::Vector2(5, 10), YELLOW },
        Target { false, raylib::Vector2(9, 10), GREEN },
        Target { false, raylib::Vector2(1, 11), BLUE },
        Target { false, raylib::Vector2(12, 11), RED },
        Target { false, raylib::Vector2(6, 12), BLUE },
        Target { false, raylib::Vector2(8, 13), GRAY },
        Target { false, raylib::Vector2(3, 14), RED },
        Target { false, raylib::Vector2(10, 14), BLUE },
    };

    // Putting all the data in the global object
    global = Global {
        robots,
        walls,
        targets,
        0,
        false
    };
    // Setting up all the game data and randomizing robot position
    resetGame();

    int robotSelected = -1; // Id of the currently selected robot
    while(!window.ShouldClose()) {

        // UPDATE

        // If the player has won and he press space we reset the game with new randomized values
        if(global.won && IsKeyPressed(KEY_SPACE)) {
            resetGame();
        }

        // Code rensposible for selecting and moving robots
        if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {

            // We get the mouse position and convert it to cell position
            raylib::Vector2 clickPosition = GetMousePosition();
            raylib::Vector2 cellPosition = raylib::Vector2(floor(clickPosition.x / Constants::CELL_SIZE), floor(clickPosition.y / Constants::CELL_SIZE));

            if(robotSelected == -1) {
                // If no robot are selected we seach for a robot at that cell position and while we do that we unselect every robots
                for(Robot robot : global.robots) {
                    robot.unselect();
                    if(robot.getPosition() == cellPosition) {
                        // If we find a robot at that position we select it
                        robot.select();
                        robotSelected = robot.getId();
                    }
                }
            }else {
                // If a robot is selected we get it's pointer
                Robot* selectedRobot = &global.robots[robotSelected];

                if(selectedRobot->getPosition() == cellPosition) {
                    // If the click was on the robot we unselect it
                    selectedRobot->unselect();
                    robotSelected = -1;
                }else if(selectedRobot->getPosition().Distance(cellPosition) == 1) {
                    // If the click was on the robot neighbor we move the robot in that direction and unselect the robot
                    selectedRobot->move(cellPosition - selectedRobot->getPosition());
                    selectedRobot->unselect();
                    robotSelected = -1;
                }
            }
        }

        // DRAW
        window.BeginDrawing();
        window.ClearBackground(WHITE);

        // Grid drawing (since the grid is a perfect square we can do all lines in the same loop)
        for(size_t i = 0; i < Constants::SCREEN_WIDTH / Constants::CELL_SIZE; i++) {
            int cellPos = Constants::CELL_SIZE * i;
            DrawLine(cellPos, 0, cellPos, Constants::SCREEN_HEIGHT, BLACK);
            DrawLine(0, cellPos, Constants::SCREEN_WIDTH, cellPos, BLACK);
        }
        
        // Draws all robots
        for(Robot robot : global.robots) {
            robot.draw();
        }

        // Drawing all walls not forgetting to convert all vector from cell position to screen position
        for(Wall wall : global.walls) {
            (wall.position * Constants::CELL_SIZE).DrawLine((wall.position + raylib::Vector2(wall.dir.y, wall.dir.x)) * Constants::CELL_SIZE, 5, RED);
        }

        // Draws the selected target
        for(Target target : global.targets) {
            if(!target.selectedTarget) continue; 
            (target.position * Constants::CELL_SIZE + Constants::halfCell).DrawCircle(Constants::CELL_SIZE * 0.1, target.color);
        }

        if(robotSelected != -1) {
            // If a robot is selected we get it and compute it's neighbor
            Robot selectedRobot = global.robots[robotSelected];
            std::vector<raylib::Vector2> neighbors {
                selectedRobot.getPosition() + raylib::Vector2(0, -1), // UP
                selectedRobot.getPosition() + raylib::Vector2(0, 1),  // RIGHT
                selectedRobot.getPosition() + raylib::Vector2(1, 0),  // DOWN
                selectedRobot.getPosition() + raylib::Vector2(-1, 0)  // LEFT
            };

            // Loops through neighbor to find if they are obstructed or not
            for(raylib::Vector2 neighbor : neighbors) {

                bool spaceOccupied = false;
                // If the neighbor cell is filled by a robot then we ignore that neighbor
                for(Robot robot : global.robots) {
                    if(neighbor == robot.getPosition()) {
                        spaceOccupied = true;
                        break;
                    }
                }
                if(spaceOccupied) continue;

                // If the space between the selected robot and the neighbor is separated by a wall we ignore that neighbor
                for(Wall wall : global.walls) {

                    raylib::Vector2* collisionPoint = nullptr;
                    // Checking collision between the line of the robot to the neighbor and the wall line
                    bool collision = (selectedRobot.getPosition() + raylib::Vector2(0.5, 0.5)).CheckCollisionLines((neighbor + raylib::Vector2(0.5, 0.5)), wall.position, wall.position + raylib::Vector2(wall.dir.y, wall.dir.x), collisionPoint);
                    
                    // If a collision occurs we ignore that neighbor
                    if(collision) {
                        spaceOccupied = true;
                        break;
                    }
                }
                if(spaceOccupied) continue;

                // If the neighbor wasn't ignore until now then it's valid and we draw it
                // Notice: We don't check for outside of playzone neighbor because even if they are drawn the player can't see them are they are outside the screen
                (neighbor * Constants::CELL_SIZE + Constants::halfCell).DrawCircle(Constants::CELL_SIZE * 0.15, selectedRobot.getColor());
            }

        }

        if(global.won) {
            // If the player has won we draw to the screen the number of moves it took and the instruction to restart a game

            // Text
            std::string wonText = "You won in " + std::to_string(global.moveCount) + " moves !";
            std::string instructionText = "Press SPACE to play again.";
            
            // Text Widths
            float wonTextWidth = raylib::MeasureText(wonText, 64);
            float instructionTextWidth = raylib::MeasureText(instructionText, 40);
            
            // Text Background Drawing
            DrawRectangle(Constants::SCREEN_WIDTH / 2 - wonTextWidth / 2 - 8, Constants::SCREEN_HEIGHT / 2 - 40, wonTextWidth + 16, 8 + 64 + 8 + 40 + 8 + 8, WHITE);
            DrawRectangleLines(Constants::SCREEN_WIDTH / 2 - wonTextWidth / 2 - 8, Constants::SCREEN_HEIGHT / 2 - 40, wonTextWidth + 16, 8 + 64 + 8 + 40 + 8 + 8, BLACK);
            
            // Text Drawing
            raylib::DrawText(wonText, Constants::SCREEN_WIDTH / 2 - wonTextWidth / 2, Constants::SCREEN_HEIGHT / 2 - 32, 64, BLACK);
            raylib::DrawText(instructionText, Constants::SCREEN_WIDTH / 2 - instructionTextWidth / 2, Constants::SCREEN_HEIGHT / 2 + 60, 40, BLACK);
        }

        window.EndDrawing();
    }

    return 0;
}
