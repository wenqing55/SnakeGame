#include "SaveSystem.h"
#include <fstream>
#include <sstream>
#include <sys/stat.h>
#include <direct.h>

static bool createDirIfNotExists(const std::string& dir) {
    struct _stat info;
    if (_stat(dir.c_str(), &info) != 0) {
        return _mkdir(dir.c_str()) == 0;
    }
    return (info.st_mode & _S_IFDIR) != 0;
}

bool SaveSystem::saveGame(const GameState& state, const std::string& path) {
    createDirIfNotExists("save");
    std::ofstream file(path);
    if (!file.is_open()) return false;
    file << "score=" << state.score << std::endl;
    file << "dir=" << state.direction << std::endl;
    file << "mapW=" << state.mapWidth << std::endl;
    file << "mapH=" << state.mapHeight << std::endl;
    file << "snake=";
    for (size_t i = 0; i < state.snake.size(); i++) {
        if (i > 0) file << ";";
        file << state.snake[i].x << "," << state.snake[i].y;
    }
    file << std::endl;
    file << "food=" << state.food.x << "," << state.food.y << std::endl;
    file << "isPaused=" << state.isPaused << std::endl;
    file.close();
    return true;
}

bool SaveSystem::loadGame(GameState& state, const std::string& path) {
    std::ifstream file(path);
    if (!file.is_open()) return false;
    std::string line;
    while (std::getline(file, line)) {
        size_t eqPos = line.find('=');
        if (eqPos == std::string::npos) continue;
        std::string key = line.substr(0, eqPos);
        std::string value = line.substr(eqPos + 1);
        if (key == "score") state.score = std::stoi(value);
        else if (key == "dir") state.direction = (Direction)std::stoi(value);
        else if (key == "mapW") state.mapWidth = std::stoi(value);
        else if (key == "mapH") state.mapHeight = std::stoi(value);
        else if (key == "snake") {
            state.snake.clear();
            std::stringstream ss(value);
            std::string coord;
            while (std::getline(ss, coord, ';')) {
                size_t commaPos = coord.find(',');
                int x = std::stoi(coord.substr(0, commaPos));
                int y = std::stoi(coord.substr(commaPos + 1));
                state.snake.emplace_back(x, y);
            }
        } else if (key == "food") {
            size_t commaPos = value.find(',');
            int x = std::stoi(value.substr(0, commaPos));
            int y = std::stoi(value.substr(commaPos + 1));
            state.food = Point(x, y);
        } else if (key == "isPaused") state.isPaused = (std::stoi(value) == 1);
    }
    state.isGameOver = false;
    file.close();
    return true;
}