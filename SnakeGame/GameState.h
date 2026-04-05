#pragma once
#include <vector>
#include "Point.h"
#include "Direction.h"

struct GameState {
    std::vector<Point> snake;
    Point food;
    Direction direction;
    int score;
    int mapWidth;
    int mapHeight;
    bool isGameOver;
    bool isPaused;
};