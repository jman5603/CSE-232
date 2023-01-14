#include "GamePiece.hpp"
#include "GameState.hpp"

#include <iostream>
#include <string>
using std::string;
#include <map>
using std::map;
#include <vector>
using std::vector;
using std::find;
#include <ostream>
using std::ostream;

GamePiece::GamePiece(std::string playerName, std::string pieceType, GameState * state)
{
    playerName_ = playerName;
    pieceType_ = pieceType;
    state_ = state;
    state_->pieces_++;
    state_->players_[playerName].push_back(pieceType);
    if (pieceType == "Wizard")
    {
        state_->wizards_++;
    }
}

GamePiece::GamePiece(GamePiece const & other)
{
    playerName_ = other.playerName_;
    pieceType_ = other.pieceType_;
    state_ = other.state_;
    state_->pieces_++;
    state_->players_[playerName_].push_back(pieceType_);
    if (other.pieceType_ == "Wizard")
    {
        state_->wizards_++;
    }
}

std::string const GamePiece::GetPlayer()
{
    return playerName_;
}

std::string const GamePiece::GetType()
{
    return pieceType_;
}

int GamePiece::GetPower() const
{
    if (pieceType_ == "Wizard")
    {
        return state_->NumPieces(playerName_, "Wizard");
    }
    else if (pieceType_ == "Scout")
    {
        return 1;
    }
    else if (pieceType_ == "Warrior")
    {
        return 5;
    }
    else
    {
        return 0;
    }
}

int GamePiece::GetSpeed() const
{
    if (pieceType_ == "Wizard")
    {
        int enemyWizards = (state_->wizards_) - (state_->NumPieces(playerName_, "Wizard"));
        if (12-enemyWizards < 1)
        {
            return 1;
        }
        else
        {
            return (12 - enemyWizards);
        }
    }
    else if (pieceType_ == "Scout")
    {
        return 8;
    }
    else if (pieceType_ == "Warrior")
    {
        return 2;
    }
    else
    {
        return 0;
    }
}

bool operator==(GamePiece const & piece1, GamePiece const & piece2)
{
    if ((piece1.GetPower() == piece2.GetPower()) && (piece1.GetSpeed() == piece2.GetSpeed()))
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool operator!=(GamePiece const & piece1, GamePiece const & piece2)
{
    if (piece1.GetPower() != piece2.GetPower() || piece1.GetSpeed() != piece2.GetSpeed())
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool operator<(GamePiece const & piece1, GamePiece const & piece2)
{
    if (piece1.GetPower() < piece2.GetPower())
    {
        return true;
    }
    else if (piece1.GetPower() == piece2.GetPower())
    {
        if (piece1.GetSpeed() < piece2.GetSpeed())
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }
}

bool operator>(GamePiece const & piece1, GamePiece const & piece2)
{
    if (piece1.GetPower() > piece2.GetPower())
    {
        return true;
    }
    else if (piece1.GetPower() == piece2.GetPower())
    {
        if (piece1.GetSpeed() > piece2.GetSpeed())
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }
}

bool operator<=(GamePiece const & piece1, GamePiece const & piece2)
{
    if (piece1.GetPower() < piece2.GetPower())
    {
        return true;
    }
    else if (piece1.GetPower() == piece2.GetPower())
    {
        if (piece1.GetSpeed() <= piece2.GetSpeed())
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }
}

bool operator>=(GamePiece const & piece1, GamePiece const & piece2)
{
    if (piece1.GetPower() > piece2.GetPower())
    {
        return true;
    }
    else if (piece1.GetPower() == piece2.GetPower())
    {
        if (piece1.GetSpeed() >= piece2.GetSpeed())
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }
}

ostream & operator<<(ostream & os, GamePiece const & piece)
{
    os << "(" << piece.playerName_ << "," << piece.pieceType_ << "," << piece.GetPower() << "," << piece.GetSpeed() << ")";
    return os;
}

GamePiece & GamePiece::operator=(GamePiece const & other)
{
    // checks if the piece is a wizard and deals with it accordingly
    if (other.pieceType_ == "Wizard" && pieceType_ != "Wizard")
    {
        state_->wizards_++;
    }
    else if (other.pieceType_ != "Wizard" && pieceType_ == "Wizard")
    {
        state_->wizards_--;
    }
    // erase old piece
    state_->players_[playerName_].erase(find(state_->players_[playerName_].begin(), state_->players_[playerName_].end(), pieceType_));
    playerName_ = other.playerName_;
    pieceType_ = other.pieceType_;
    // if changing game states, deal with it accordingly
    if (state_ != other.state_)
    {
        if (pieceType_ == "Wizard")
        {
            state_->wizards_--;
        }
        state_->pieces_--;
        state_ = other.state_;
        state_->pieces_++;
        if (pieceType_ == "Wizard")
        {
            state_->wizards_++;
        }
    }
    state_->players_[playerName_].push_back(pieceType_);
    return *this;
}

GamePiece::~GamePiece()
{
    state_->pieces_--;
    if (pieceType_ == "Wizard")
    {
        state_->wizards_--;
    }
    state_->players_[playerName_].erase(find(state_->players_[playerName_].begin(), state_->players_[playerName_].end(), pieceType_));
}
