#pragma once
#include "GameState.h"
#include <string>

class SaveSystem {
public:
    static bool saveGame(const GameState& state, const std::string& path = "save/save.txt");
    static bool loadGame(GameState& state, const std::string& path = "save/save.txt");
};