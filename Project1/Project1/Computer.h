#pragma once

#include "Player.h"
#include <stdlib.h>     /* srand, rand */
#include <time.h>

class Computer : public Player{
public:
    // Accessor made inline for efficiency
    inline string getPlayerType() const { 
        return "Computer";
    }

    // Utility functions that enable the human player to make moves
    int rollADieOnce();
    char selectColor();
    void showGameOptions();
    int getGameOption(Board * gameBoard);
    int getGameOptionForQuitGame();
    int getRowForABoardPiece( int maxRow, Board * gameBoard);
    int getColumnForABoardPiece(int maxCol, Board * gameBoard );
    int getMoveDirection();
    void getHelp( Board * gameBoard );

private:
    static const int GAME_OPTION_QUIT_GAME = 3;
};