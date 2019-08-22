#pragma once

#include "Player.h"
#include <time.h>

class Human : public Player{
public:
    // Symbolic constants
    static const int GAME_OPTION_HELP = 3;

    // Accessor made inline for efficiency
    inline string getPlayerType() const { 
        return "Human";
    }

    // Utility functions that enable the human player to make moves
    int rollADieOnce();
    char selectColor();
    void showGameOptions();
    int getGameOption(Board * gameBoard);
    int getGameOptionForQuitGame();
    int getRowForABoardPiece( int maxRow, Board * gameBoard );
    int getColumnForABoardPiece( int maxCol, Board * gameBoard );
    int inputRowOrCol( int maxRowOrCol, string prompt );
    int getMoveDirection();

    // Other utility functions
    static int extractDigitFromText( string potentialNumber);
    void getHelp( Board * gameBoard );

private:
    static const int GAME_OPTION_QUIT_GAME = 4;
};