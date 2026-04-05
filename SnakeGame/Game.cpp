#include "Game.h"
#include <thread>
#include <chrono>

Game::Game(int w, int h) : mapWidth(w), mapHeight(h) {
    snake = new Snake(w / 2, h / 2);
    food = new Food(w, h);
    renderer = new Renderer(w, h);
    score = 0;
    isGameOver = false;
    isPaused = false;
}

Game::~Game() {
    delete snake;
    delete food;
    delete renderer;
}

void Game::resetGame() {
    delete snake;
    delete food;
    snake = new Snake(mapWidth / 2, mapHeight / 2);
    food = new Food(mapWidth, mapHeight);
    score = 0;
    isGameOver = false;
    isPaused = false;
}

GameState Game::getCurrentState() const {
    GameState state;
    state.snake = std::vector<Point>(snake->getBody().begin(), snake->getBody().end());
    state.food = food->getPosition();
    state.direction = snake->getDirection();
    state.score = score;
    state.mapWidth = mapWidth;
    state.mapHeight = mapHeight;
    state.isGameOver = isGameOver;
    state.isPaused = isPaused;
    return state;
}

void Game::loadFromState(const GameState& state) {
    delete snake;
    snake = new Snake(0, 0);
    auto& body = const_cast<std::deque<Point>&>(snake->getBody());
    body.clear();
    for (const auto& p : state.snake) {
        body.push_back(p);
    }
    snake->setDirection(state.direction);

    delete food;
    food = new Food(mapWidth, mapHeight);
    food->setPosition(state.food);

    score = state.score;
    isGameOver = state.isGameOver;
    isPaused = state.isPaused;
}

void Game::run() {
    while (true) {
        while (!isGameOver) {
            Direction dir = Input::getDirectionInput();
            if (dir != (Direction)-1) {
                snake->changeDirection(dir);
            }

            char key = Input::getKeyInput();
            if (key == 27) {
                SaveSystem::saveGame(getCurrentState());
                return;
            }
            if (key == 'p' || key == 'P') {
                isPaused = !isPaused;
                if (isPaused) SaveSystem::saveGame(getCurrentState());
            }
            if (key == 's' || key == 'S') {
                SaveSystem::saveGame(getCurrentState());
            }
            if (key == 'l' || key == 'L') {
                GameState state;
                if (SaveSystem::loadGame(state)) {
                    loadFromState(state);
                }
            }

            if (isPaused) {
                renderer->render(*snake, *food, score, isPaused, isGameOver);
                renderer->draw();
                std::this_thread::sleep_for(std::chrono::milliseconds(50));
                continue;
            }

            bool grow = snake->getHead() == food->getPosition();
            snake->move(grow);

            if (grow) {
                score += 10;
                food->spawn(std::vector<Point>(snake->getBody().begin(), snake->getBody().end()));
            }

            Point head = snake->getHead();
            if (head.x <= 0 || head.x >= mapWidth - 1 || head.y <= 0 || head.y >= mapHeight - 1) {
                isGameOver = true;
            }
            if (snake->checkSelfCollision()) {
                isGameOver = true;
            }

            renderer->render(*snake, *food, score, isPaused, isGameOver);
            renderer->draw();
            std::this_thread::sleep_for(std::chrono::milliseconds(130));
        }

        renderer->render(*snake, *food, score, isPaused, isGameOver);
        renderer->draw();

        while (true) {
            char key = Input::getKeyInput();
            if (key == 'r' || key == 'R') {
                resetGame();
                break;
            }
            if (key == 27) {
                return;
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(50));
        }
    }
}