#pragma once

#include "Player.h"
#include "Human.h"
#include "Computer.h"
#include "Board.h"
#include <sstream>
#include <cstring>

class Game{
public:
    // Constructors
    Game( int boardDimension, int championshipScoreHuman, int championshipScoreComputer );
    Game(Board * board, Computer *compPlayer, Human *humanPlayer, int gameCount, string nextPlayer, int championshipScoreHuman, int championshipScoreComputer );

    // Accessors
    inline Human * getHumanPlayer(){
        return this->humanPlayer;
    }

    inline Computer * getComputerPlayer(){
        return this->computerPlayer;
    }

private:
    // Class Constants
    static const int POINT_PER_CAPTURE = 5;
    static const int QUITTING_PENALTY = -5;
    
    // Member variables
    Board * gameBoard;
    Computer * computerPlayer;
    Human * humanPlayer;
    static int gameCount;
    static bool turn; // If turn is true, it is computer's turn. Else, it is human's turn
    static string previousGameWinner;
    string moveSummary;
    bool aPlayerQuitGame;
    int championshipScoreHuman; // Saved file should contain players' championship scores
    int championshipScoreComputer; 

    // Functions to make moves and play a game
    void updateMoveSummaryWithRowAndColDescription( Player * player, int originRow, int originCol );

    Player * getCurrentPlayer();
    void setUpGame( bool gameLoaded = false );
    void rollDices();
    int rollDiceOneRound( Player * player );

    void summarizeDiceThrow( int sumOfDiceHumanPlayer, int sumOfDiceComputerPlayer );
    void assignColor( );
    void summarizeColorSelection();

    Player * getOpponentPlayer( Player * player );
    void playAGame();
    void playATurn( Player * player );

    void makeMove( Player * player );
    bool verifyMove(int moveDirection, Piece * pieceUserSelected, int originRow, int originCol, Player * player );

    bool gameOver();

    void endGame();

    int computePoints( Player * player );
    void quitGame( Player * player );
    //void setTurnForNextRound();
    void determineWinner();

    // Functions to save a game
    void saveGame();
    void savePlayerStats( ofstream & saveFile, Player * player, int playerChampionshipScore );
    void saveBoard( ofstream & saveFile );
    void saveNextPlayer( ofstream & saveFile );
    void askForHelp(  Player * player );
};