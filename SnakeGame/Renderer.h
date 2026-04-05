#pragma once
#include <string>
#include <vector>
#include "Snake.h"
#include "Food.h"

class Renderer {
private:
    int width, height;
    std::vector<std::string> frontBuffer;
    std::vector<std::string> backBuffer;
    void clearBuffer();
public:
    Renderer(int w, int h);
    void render(const Snake& snake, const Food& food, int score, bool isPaused, bool isGameOver);
    void draw();
};