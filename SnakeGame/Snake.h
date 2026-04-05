#pragma once
#include <deque>
#include "Point.h"
#include "Direction.h"

class Snake {
private:
    std::deque<Point> body;
    Direction currentDir;
    Direction nextDir;
public:
    Snake(int startX, int startY);
    void move(bool grow);
    void changeDirection(Direction newDir);
    void setDirection(Direction newDir);  // 仅声明
    const std::deque<Point>& getBody() const;
    Point getHead() const;
    Direction getDirection() const;
    bool checkSelfCollision() const;
};