#pragma once
#include "GameState.hpp"

#include <string>
#include <ostream>
using std::ostream;

class GamePiece
{
    private:
        std::string playerName_ = "";
        std::string pieceType_ = "";
        GameState* state_ = nullptr;

    public:
        GamePiece(std::string playerName, std::string pieceType, GameState* state);
        GamePiece(GamePiece const & other);
        std::string const GetPlayer();
        std::string const GetType();
        int GetPower() const;
        int GetSpeed() const;
        // ==
        friend bool operator==(GamePiece const & piece1, GamePiece const & piece2);
        // !=
        friend bool operator!=(GamePiece const & piece1, GamePiece const & piece2);
        // <
        friend bool operator<(GamePiece const & piece1, GamePiece const & piece2);
        // >
        friend bool operator>(GamePiece const & piece1, GamePiece const & piece2);
        // <=
        friend bool operator<=(GamePiece const & piece1, GamePiece const & piece2);
        // >=
        friend bool operator>=(GamePiece const & piece1, GamePiece const & piece2);
        // <<
        friend ostream & operator<<(ostream & os, GamePiece const & piece);
        // =
        GamePiece & operator=(GamePiece const & other);
        ~GamePiece();
};
