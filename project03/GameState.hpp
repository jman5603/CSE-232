#pragma once

#include <string>
using std::string;
#include <map>
using std::map;
#include <vector>
using std::vector;

class GameState
{
    public:
        GameState() = default;
        int pieces_ = 0;
        int wizards_ = 0;
        map<std::string, vector<std::string>> players_;

        int NumPieces();
        int NumPieces(std::string playerName);
        int NumPieces(std::string playerName, std::string pieceType);
};
