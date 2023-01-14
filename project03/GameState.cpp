#include "GameState.hpp"

int GameState::NumPieces()
{
    return pieces_;
}

int GameState::NumPieces(string playerName)
{
    return players_[playerName].size();
}

int GameState::NumPieces(string playerName, string pieceType)
{
    int count = 0;
    for (auto piece : players_[playerName])
    {
        if (piece == pieceType)
        {
            count++;
        }
    }
    return count;
}
