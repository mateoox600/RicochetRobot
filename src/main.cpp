
#include <vector>
#include <set>
#include <math.h>
#include "raylib-cpp.hpp"

#include "Constants.hpp"
#include "Global.hpp"

#include "Robot.hpp"
#include "Wall.hpp"

Global global;

int main(int argc, char const *argv[]) {

    raylib::Window window(Constants::SCREEN_WIDTH, Constants::SCREEN_HEIGHT, Constants::TITLE_NAME);

    window.SetTargetFPS(60);

    std::vector<raylib::Vector2> robotPos;

    do {
        raylib::Vector2 toAdd(floor(rand() % (Constants::SCREEN_WIDTH / Constants::CELL_SIZE)), floor(rand() % (Constants::SCREEN_WIDTH / Constants::CELL_SIZE)));
        for(raylib::Vector2 pos : robotPos) {
            if(pos == toAdd) continue;
        }
        robotPos.push_back(toAdd);
    } while (robotPos.size() < 5);

    std::vector<Robot> robots {
        Robot(0, robotPos[0], GREEN),
        Robot(1, robotPos[1], RED),
        Robot(2, robotPos[2], YELLOW),
        Robot(3, robotPos[3], GRAY),
        Robot(4, robotPos[4], BLUE)
    };

    std::vector<Wall> walls {
        Wall { raylib::Vector2(15, 10), raylib::Vector2(0, 1) },
        Wall { raylib::Vector2(10, 15), raylib::Vector2(1, 0) }
    };

    global = Global {
        robots,
        walls,
        0
    };

    int robotSelected = -1;
    while(!window.ShouldClose()) {
        // UPDATE
        for(Robot robot : global.robots) {
            robot.update();
        }

        if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            raylib::Vector2 clickPosition = GetMousePosition();
            raylib::Vector2 cellPosition = raylib::Vector2(floor(clickPosition.x / Constants::CELL_SIZE), floor(clickPosition.y / Constants::CELL_SIZE));
            if(robotSelected == -1) {
                for(Robot robot : global.robots) {
                    robot.unselect();
                    if(robot.getPosition() == cellPosition) {
                        robot.select();
                        robotSelected = robot.getId();
                    }
                }
            }else {
                Robot* selectedRobot = &global.robots[robotSelected];
                if(selectedRobot->getPosition() == cellPosition) {
                    selectedRobot->unselect();
                    robotSelected = -1;
                }else if(selectedRobot->getPosition().Distance(cellPosition) == 1) {
                    selectedRobot->move(cellPosition - selectedRobot->getPosition());
                    global.moveCount++;
                    selectedRobot->unselect();
                    robotSelected = -1;
                }
            }
        }

        // DRAW
        window.BeginDrawing();
        window.ClearBackground(WHITE);

        // DRAW GRID
        for(size_t i = 0; i < Constants::SCREEN_WIDTH / Constants::CELL_SIZE; i++) {
            int cellPos = Constants::CELL_SIZE * i;
            DrawLine(cellPos, 0, cellPos, Constants::SCREEN_HEIGHT, BLACK);
            DrawLine(0, cellPos, Constants::SCREEN_WIDTH, cellPos, BLACK);
        }
        
        for(Robot robot : global.robots) {
            robot.draw();
        }

        for(Wall wall : global.walls) {
            (wall.position * Constants::CELL_SIZE).DrawLine((wall.position + raylib::Vector2(wall.dir.y, wall.dir.x)) * Constants::CELL_SIZE, 3, RED);
        }

        if(robotSelected != -1) {
            Robot selectedRobot = global.robots[robotSelected];

            std::vector<raylib::Vector2> neighbors {
                selectedRobot.getPosition() + raylib::Vector2(0, -1),
                selectedRobot.getPosition() + raylib::Vector2(0, 1),
                selectedRobot.getPosition() + raylib::Vector2(1, 0),
                selectedRobot.getPosition() + raylib::Vector2(-1, 0)
            };

            for(raylib::Vector2 neighbor : neighbors) {

                bool spaceOccupied = false;
                for(Robot robot : global.robots) {
                    if(neighbor == robot.getPosition()) {
                        spaceOccupied = true;
                        break;
                    }
                }
                if(spaceOccupied) continue;

                for(Wall wall : global.walls) {

                    raylib::Vector2* collisionPoint = nullptr;
                    bool collision = (selectedRobot.getPosition() + raylib::Vector2(0.5, 0.5)).CheckCollisionLines((neighbor + raylib::Vector2(0.5, 0.5)), wall.position, wall.position + raylib::Vector2(wall.dir.y, wall.dir.x), collisionPoint);
                    
                    if(collision) {
                        spaceOccupied = true;
                        break;
                    }
                }
                if(spaceOccupied) continue;

                (neighbor * Constants::CELL_SIZE + Constants::halfCell).DrawCircle(Constants::CELL_SIZE * 0.15, selectedRobot.getColor());
            }

        }

        window.EndDrawing();
    }

    return 0;
}
