#include "Input.h"

Direction Input::getDirectionInput() {
    if (_kbhit()) {
        int ch = _getch();
        if (ch == 0 || ch == 224) {
            switch (_getch()) {
                case 72: return UP;
                case 80: return DOWN;
                case 75: return LEFT;
                case 77: return RIGHT;
            }
        }
    }
    return (Direction)-1;
}

char Input::getKeyInput() {
    if (_kbhit()) {
        return _getch();
    }
    return 0;
}