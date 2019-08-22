#pragma once

#include "Board.h"
#include <string>
#include <time.h>

class Player{
public:
    // Constructors
    Player();
    
    // Symbolic constants
    static const int GAME_OPTION_SAVE_GAME = 1;
    static const int GAME_OPTION_MAKE_MOVE = 2;

    static const int MOVE_NORTHEAST = 1;
    static const int MOVE_NORTHWEST = 2;
    static const int MOVE_SOUTHEAST = 3;
    static const int MOVE_SOUTHWEST = 4;

    // Selectors
    inline int getScore() const{
        return score; 
    }

    inline char getColor() const{
        return color;
    }

    inline bool getQuit() const {
        return quit;
    }

    inline int getNumCaptures() const {
        return numCaptures;
    }

    string getColorString();

    // Mutators
    void updateScore(int scr );
    void setScore(int scr );
    bool setColor( char clr );
    void setQuit( bool quit );
    void incrementNumCaptures();

    virtual string getPlayerType() const = 0; // Return a text that is either "Computer" or "Human"
    virtual int rollADieOnce() = 0;
    virtual char selectColor() = 0;

    // Display a game option menu before each player plays. The game menu is slightly different for the human
    // and the computer player as the human player has an additional option to ask for help but the 
    // comptuer player does not have help option
    virtual void showGameOptions() = 0;
    virtual int getGameOption( Board * gameBoard ) = 0;
    virtual int getGameOptionForQuitGame() = 0;
    virtual int getRowForABoardPiece( int maxRow, Board * gameBoard  ) = 0;
    virtual int getColumnForABoardPiece( int maxCol, Board * gameBoard  ) = 0;
    virtual int getMoveDirection() = 0;
    virtual void getHelp(Board * gameBoard ) = 0;

protected:
    // Symbolic constants
    static const int INVALID_INPUT = 999;

    // Member variables
    int score;
    char color;
    bool quit;
    int numCaptures;

    // Utility functions to make efficient moves for computer and for human (help feature)       

    // Return true if the player can make a move. False otherwise
    bool computeOptimalMove( Board * gameBoard );
    
    inline Piece * getOptimalPiece() const {
        return optimalPieceToMove;
    }

    inline int getOptimalMoveDirection() const {
        return optimalDirectionToMoveThePieceIn;
    }

private:
    vector <Piece*> getPiecesThatCanCapture(  Board * gameBoard );
    Piece * optimalPieceToMove;
    int optimalDirectionToMoveThePieceIn;
    void resetOptimalMove();

    vector<Piece*> getPiecesThatCanCaptureDeadlyPieces( vector<Piece*> pieces, Board * gameBoard );
    Piece * getBestPieceThatCantCapture( vector<Piece*> pieces, Board * gameBoard ); 
    Piece * getPieceThatCanGoToMostValuableHomePoint( vector<Piece*> pieces, Board * gameBoard );
    void computeMostValuableHomePieceOccupant( int & localMaxPoint, int & localMoveDirection, int rowInDirectionSpecified, int colInDirectionSpecified, int directionType, Piece * piece, Board * gameBoard );
    vector <Piece*> getBestPiecesRowWise( vector<Piece *> pieces, Board * gameBoard );
    Piece * getBestPieceColumnWise( vector<Piece*> aRowOfpieces, Board * gameBoard );

    Piece * getBestPieceThatCanCaptureDeadlyPieces( vector<Piece*> piecesThatCanCaptureDeadlyPieces, Board * gameBoard );
    Piece * getBestPieceThatCanCaptureNonDeadlyPieces( vector <Piece*> piecesThatCanCapture, Board * gameBoard );
    Piece * getBestCapturePieceColumnWise( vector <Piece*> pieces, Board * gameBoard );
};