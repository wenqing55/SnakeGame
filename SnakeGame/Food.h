#pragma once
#include <vector>  // 必须加！
#include "Point.h"

class Food {
private:
    Point position;
    int mapWidth, mapHeight;
public:
    Food(int w, int h);
    void spawn(const std::vector<Point>& snakeBody);  // 仅声明
    Point getPosition() const;
    void setPosition(Point p);  // 仅声明
};