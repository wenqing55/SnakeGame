#pragma once
#include "Snake.h"
#include "Food.h"
#include "Renderer.h"
#include "Input.h"
#include "SaveSystem.h"
#include "GameState.h"

class Game {
private:
    Snake* snake;
    Food* food;
    Renderer* renderer;
    int score;
    int mapWidth, mapHeight;
    bool isGameOver;
    bool isPaused;
    void resetGame();
    GameState getCurrentState() const;
    void loadFromState(const GameState& state);
public:
    Game(int w = 30, int h = 20);
    ~Game();
    void run();
};