#include "Food.h"
#include <cstdlib>
#include <ctime>

Food::Food(int w, int h) : mapWidth(w), mapHeight(h) {
    srand((unsigned int)time(NULL));
    spawn({});  // 初始生成，传空vector
}

void Food::spawn(const std::vector<Point>& snakeBody) {
    bool onSnake;
    do {
        onSnake = false;
        position.x = rand() % (mapWidth - 2) + 1;
        position.y = rand() % (mapHeight - 2) + 1;
        for (const auto& p : snakeBody) {
            if (p == position) {
                onSnake = true;
                break;
            }
        }
    } while (onSnake);
}

Point Food::getPosition() const { return position; }

// 仅在这里实现一次setPosition
void Food::setPosition(Point p) {
    position = p;
}