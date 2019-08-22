#pragma once

#include "Piece.h"
#include <vector>
#include <unordered_map>
#include <fstream>
#include <climits>

class Board{
public:
    // Symbolic constants
    static const int INVALID_INDEX = -999;

    static const int MOVE_NORTHEAST = 1;
    static const int MOVE_NORTHWEST = 2;
    static const int MOVE_SOUTHEAST = 3;
    static const int MOVE_SOUTHWEST = 4;

    // Constructors
    Board( int dimension );
    Board( vector <vector <Piece*> > board, int dimension );

    // Accessor
    inline int getDimension(){
        return dimension;
    }
    
    // Utility functions
    void print();

    // Functions to move a piece from one position in the board to another position in the board
    bool moveNorthWest( Piece * piece, int initialRow, int initialCol, bool & capturedAPiece );
    bool moveNorthEast( Piece * piece, int initialRow, int initialCol, bool & capturedAPiece  );
    bool moveSouthWest( Piece * piece, int initialRow, int initialCol, bool & capturedAPiece  );
    bool moveSouthEast( Piece * piece, int initialRow, int initialCol, bool & capturedAPiece  );

    Piece * getPiece(int row, int col);
    bool hasReachedAllHomePoints( char playerColor );
    bool checkIfAPlayerReachedEdgePosition( char playerColor, int edgePositionRow, int edgePositionColumn );

    int computePointsBasedOnHomePositions( char playerColor );

    void writeToFile( ofstream & saveFile );
    void saveOneRow( ofstream & saveFile, vector <Piece*> oneRow );

    vector <Piece*> getAllPiecesOfAColor( char playerColor );
    bool canCaptureInOneMove( Piece * piece ); 
    bool checkCapture( Piece * possibleCapturerrrr, int row, int col );

    bool canCaptureDeadlyPieceInOneMove( Piece * onePiece );
    bool isDeadlyPiece( Piece * referencePiece, int deadlyPieceRow, int deadlyPieceCol );

    vector <Piece*> getPiecesThatCanMoveToHomePointInOneMove( char playerColor ); 

    int getNorthwestRow( int currentRow );
    int getNorthwestCol(int currentCol );

    int getNortheastRow(int currentRow );
    int getNortheastCol(int currentCol );

    int getSouthwestRow(int currentRow);
    int getSouthwestCol(int currentCol );

    int getSoutheastRow( int currentRow );
    int getSoutheastCol( int currentCol ); 

    int getRowOfAPiece( Piece * piece );
    int getColumnOfAPiece( Piece * piece );

    bool canReachHomePointInOneMove( Piece * piece, int row, int col); 

    int getPointForReachingAHomePosition( int row, int col, char playerColor );
    vector <Piece*> getPiecesThatCanMoveTowardsHomePosition( vector<Piece*> pieces, char playerColor );

    Piece * getBestPieceThatCanMoveTowardsHomePos( vector<Piece*> aRowOfpieces, char playerColor, int & optimalDirectionToMoveThePieceIn );
    Piece * getBestPieceThatCanMoveAwayFromHomePos( vector<Piece*> aRowOfpieces, char playerColor, int & optimalDirectionToMoveThePieceIn );
    vector <Piece*> getPiecesAlreadyInOpponentsHomePosition( vector<Piece*> pieces, char playerColor );

    // Check if there is at least one piece in the board whose color equals playerColor
    bool atLeastOnePieceExists( char playerColor );
    bool canMoveAtLeastOnePieceLegitimately( char playerColor );

    vector <Piece*> getPiecesFromTheRowFarthestFromOpponentsHomePos( vector <Piece*> pieces, char playerColor );
    string getDirectionString(int direction);

private:
    static const char NOTATION_FOR_EMPTY_PIECE = '+';

    vector <vector <Piece*> > gameBoard;
    int dimension; // The dimesion of a board can be 5, 7 or 9
    unordered_map<int, int> homePositionWeightageMap;

    // Utility functions
    void initializeBoard();
    void setUpBlackPieces();
    void setUpWhitePieces();
    bool move( Piece * piece, int originRow, int originCol, int destinationRow, int destinationCol, bool & capturedAPiece  );

    bool hasReachedHomePoint( char playerColor, int destinationRow, int destinationCol );
    void initializeMap();

    void printSymbolsBetweenTwoRows();
    void printFooter();

    bool canMoveNortheast( int row, int col );
    bool canMoveNorthwest( int row, int col );
    bool canMoveSoutheast(int row, int col);
    bool canMoveSouthwest( int row, int col );
    bool canMove( int originRow, int originCol, int destinationRow, int destinationCol );

    // Get all pieces of a given color from a given row 
    vector <Piece*> getCertainPiecesFromARow( int row, char playerColor );
    vector<Piece*> filterOutPiecesThatCantMove( vector<Piece*> pieces, char playerColor );
    vector <Piece*> getPiecesThatCanMoveAwayFromHomePosition( vector<Piece*> pieces, char playerColor );

    void findDestinationColWithMaxPoints( int destinationCol, int & maxHomePoints, Piece * & toReturn, Piece * onePiece, int & optimalDirectionToMoveThePieceIn, int directionSp );

    Piece * getBestBlackPieceThatCanMoveTowardsHomePos( vector<Piece*> aRowOfpieces, char playerColor, int &optimalDirectionToMoveThePieceIn, int rowNumber );
    Piece * getBestWhitePieceThatCanMoveTowardsHomePos( vector<Piece*> aRowOfpieces, char playerColor, int &optimalDirectionToMoveThePieceIn, int rowNumber );

    bool canMoveTowardsHomePosition( Piece * aPiece, char playerColor ); 

    Piece * getBestBlackPieceThatCanMoveAwayFromHomePos( vector<Piece*> aRowOfpieces, char playerColor, int &optimalDirectionToMoveThePieceIn, int rowNumber);
    Piece * getBestWhitePieceThatCanMoveAwayFromHomePos( vector<Piece*> aRowOfpieces, char playerColor, int &optimalDirectionToMoveThePieceIn, int rowNumber );

    vector <Piece*> choosePiecesFromARow( vector <Piece*> pieces, int rowToChooseFrom ); 
};