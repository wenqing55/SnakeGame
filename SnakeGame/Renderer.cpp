#include "Renderer.h"
#include <iostream>
#include <windows.h>

Renderer::Renderer(int w, int h) : width(w), height(h) {
    HWND console = GetConsoleWindow();
    RECT r;
    GetWindowRect(console, &r);
    MoveWindow(console, r.left, r.top, 800, 600, TRUE);

    frontBuffer.resize(height, std::string(width, ' '));
    backBuffer.resize(height, std::string(width, ' '));

    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
    cursorInfo.bVisible = false;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}

void Renderer::clearBuffer() {
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            if (x == 0 || x == width - 1 || y == 0 || y == height - 1)
                backBuffer[y][x] = '#';
            else
                backBuffer[y][x] = ' ';
        }
    }
}

void Renderer::render(const Snake& snake, const Food& food, int score, bool isPaused, bool isGameOver) {
    clearBuffer();

    for (const auto& p : snake.getBody()) {
        backBuffer[p.y][p.x] = 'O';
    }

    Point foodPos = food.getPosition();
    backBuffer[foodPos.y][foodPos.x] = '*';

    std::string scoreText = " Score: " + std::to_string(score) + " ";
    for (int i = 0; i < (int)scoreText.size() && i < width; i++) {
        backBuffer[0][i] = scoreText[i];
    }

    if (isPaused) {
        std::string s = " PAUSED ";
        int x = width / 2 - 4;
        int y = height / 2;
        for (int i = 0; i < (int)s.size(); i++) {
            backBuffer[y][x + i] = s[i];
        }
    }

    if (isGameOver) {
        std::string s = " GAME OVER ";
        int x = width / 2 - 6;
        int y = height / 2;
        for (int i = 0; i < (int)s.size(); i++) {
            backBuffer[y][x + i] = s[i];
        }
    }

    frontBuffer.swap(backBuffer);
}

void Renderer::draw() {
    system("cls");
    COORD pos = {0, 0};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
    for (const auto& line : frontBuffer) {
        std::cout << line << std::endl;
    }
}