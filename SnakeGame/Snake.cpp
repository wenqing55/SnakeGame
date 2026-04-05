#include "Snake.h"

Snake::Snake(int startX, int startY) {
    body.emplace_back(startX, startY);
    body.emplace_back(startX - 1, startY);
    body.emplace_back(startX - 2, startY);
    currentDir = RIGHT;
    nextDir = RIGHT;
}

void Snake::move(bool grow) {
    currentDir = nextDir;
    Point head = getHead();
    switch (currentDir) {
        case UP: head.y--; break;
        case RIGHT: head.x++; break;
        case DOWN: head.y++; break;
        case LEFT: head.x--; break;
    }
    body.push_front(head);
    if (!grow) {
        body.pop_back();
    }
}

void Snake::changeDirection(Direction newDir) {
    if ((currentDir == UP && newDir == DOWN) ||
        (currentDir == DOWN && newDir == UP) ||
        (currentDir == LEFT && newDir == RIGHT) ||
        (currentDir == RIGHT && newDir == LEFT)) {
        return;
    }
    nextDir = newDir;
}

// 仅在这里实现一次setDirection
void Snake::setDirection(Direction newDir) {
    currentDir = newDir;
    nextDir = newDir;
}

const std::deque<Point>& Snake::getBody() const { return body; }
Point Snake::getHead() const { return body.front(); }
Direction Snake::getDirection() const { return currentDir; }

bool Snake::checkSelfCollision() const {
    Point head = getHead();
    for (size_t i = 1; i < body.size(); i++) {
        if (body[i] == head) return true;
    }
    return false;
}