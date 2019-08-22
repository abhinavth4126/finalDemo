#include "Board.h"

/**/
    /*
    Board - Custom constructor 1 

    NAME

        Board

    SYNOPSIS

        Board::Board(int dimension)

    DESCRIPTION
        
        Initialize a board based on the board dimension provided in the parameter 

    RETURNS

        None

    AUTHOR

        Abhinav Thapaliya 

    DATE

        7/3/2019

*/
Board::Board(int dimension){
    this->dimension = dimension;

    initializeBoard();
    setUpBlackPieces();
    setUpWhitePieces();
    initializeMap();
}


/**/
    /*
    Board - Custom constructor 2

    NAME

        Board

    SYNOPSIS

        Board::Board(vector<vector<Piece *>> board, int dimension)

    DESCRIPTION
        
        Initialize a board based on the board dimension and the vector representing a 
        board provided in the parameter 

    RETURNS

        None

    AUTHOR

        Abhinav Thapaliya 

    DATE

        7/3/2019

*/
Board::Board(vector<vector<Piece *>> board, int dimension){
    this->dimension = dimension;
    this->gameBoard = board;
    initializeMap();
}


/**/
    /*
    initializeBoard - Create a two dimensional vector of Piece objects and populate
    the newly created vector of Piece objects wil NULL pointers 

    NAME

        initializeBoard

    SYNOPSIS

        void Board::initializeBoard()

    DESCRIPTION
        
        Create a two dimensional vector of Piece objects and populate
    the newly created vector of Piece objects wil NULL pointers 

    RETURNS

        None

    AUTHOR

        Abhinav Thapaliya 

    DATE

        7/3/2019

*/
void Board::initializeBoard(){
   
    for(int i = 0; i < dimension; i++){
        vector <Piece*> inner;

        for(int j = 0; j < dimension; j++){
            inner.push_back(NULL);
        }

        gameBoard.push_back(inner);
    }
}


/**/
    /*
    setUpBlackPieces - Set the starting position of the black pieces in the game board  

    NAME

        setUpBlackPieces

    SYNOPSIS

        void Board::setUpBlackPieces()

    DESCRIPTION
        
        The black pieces should be set up in the South side of the table 

    RETURNS

        None

    AUTHOR

        Abhinav Thapaliya 

    DATE

        7/3/2019

*/
void Board::setUpBlackPieces(){
    // All the pieces in the last row should be black pieces
    for(int i = 0; i < dimension; i++){
        Piece * p = new Piece( Piece::BLACK, false );
        gameBoard[dimension - 1][i] = p;
    }

    // The piece in 2nd last row, 1st column must be a black piece
    Piece * p1 = new Piece(Piece::BLACK, false);
    gameBoard[dimension - 2][0] = p1;

    // The piece in 2nd last row, last column must be a black piece
    Piece * p2 = new Piece(Piece::BLACK, false);
    gameBoard[dimension -2][dimension - 1] = p2;
}


/**/
    /*
    setUpWhitePieces - Set the starting position of the White pieces in the game board  

    NAME

        setUpWhitePieces

    SYNOPSIS

        void Board::setUpWhitePieces()

    DESCRIPTION
        
        The White pieces should be set up in the north side of the table 

    RETURNS

        None

    AUTHOR

        Abhinav Thapaliya 

    DATE

        7/3/2019

*/
void Board::setUpWhitePieces(){
    // All the pieces in the first row should be white pieces
    for(int i = 0; i < dimension; i++){
        Piece * p = new Piece( Piece::WHITE, false );
        gameBoard[0][i] = p;
    }

    // The piece in 2nd row, column 1 should be white
    Piece * p1 = new Piece(Piece::WHITE, false);
    gameBoard[1][0] = p1;

    // The piece in 2nd row, last column should be white
    Piece * p2 = new Piece(Piece::WHITE, false);
    gameBoard[1][dimension - 1] = p2;
}


/**/
    /*
    initializeMap - Initialize the member variable, homePositionWeightageMap  

    NAME

        initializeMap

    SYNOPSIS

        void Board::initializeMap()

    DESCRIPTION
        
        Opponent's "Home positions" are spots in the board where the players will
        try to move their pieces to. Certain home positions are more valuable than others.
        This functions initializes a map that maps column number with the points that can be gained 
        by reaching the home position's column

    RETURNS

        None

    AUTHOR

        Abhinav Thapaliya 

    DATE

        7/3/2019

*/
void Board::initializeMap(){
    int front = 0;
    int back = dimension - 1;

    homePositionWeightageMap[front++] = 3;
    homePositionWeightageMap[back--] = 3;    

    homePositionWeightageMap[front++] = 1;
    homePositionWeightageMap[back--] = 1;

    int weight = 5;

    while( front <= back ){
        homePositionWeightageMap[front++] = weight;
        homePositionWeightageMap[back--] = weight;
        weight += 2;
    }
}


/**/
    /*
    print - Display a string representation of the board to the player 

    NAME

        print

    SYNOPSIS

        void Board::print()

    DESCRIPTION
        
        White pieces in the board are denoted as 'W', black pieces as 'W'. White and 
        Black pieces that can capture opponent's pieces are denoted as 'WW' and "BB" respectively.
        Empty pieces are shown as empty characters. The directions, including East, West, South and North
        are also specified, along with row and column numbers so that the player can make moves
        intuitively. 

    RETURNS

        None

    AUTHOR

        Abhinav Thapaliya 

    DATE

        7/3/2019

*/
void Board::print(){
    cout << "\nN\n"; // N means North

    for(int row = 0; row < dimension; row++){
        cout << (row + 1) << "  "; 
        for(int col = 0; col < dimension; col++ ){
            Piece * toPrint = gameBoard[row][col];
            if( toPrint == NULL )
                cout << NOTATION_FOR_EMPTY_PIECE << " ";
            else{
                if( toPrint->getCapture() ){
                    toPrint->print();
                    toPrint->print();
                }
                else{
                    toPrint->print();
                    cout << " ";
                }
            }

            if( col < dimension - 1 )
                cout << "- ";         
        }

        if( row < dimension - 1 )
            printSymbolsBetweenTwoRows();
    }

    cout << "\nS\n"; // S means South
    printFooter();
}


/**/
    /*
    printFooter - Display the directions more clearly 

    NAME

        printFooter

    SYNOPSIS

        void Board::printFooter()

    DESCRIPTION
        
        'E' stands for East. 'W' stands for West. 'S' for
        South and 'N' for North 

    RETURNS

        None

    AUTHOR

        Abhinav Thapaliya 

    DATE

        7/3/2019

*/
void Board::printFooter(){
    cout << "W  "; // W means West

    for(int i = 0; i < dimension; i++ )
        cout << (i + 1) << "   ";

    cout << "E\n\n"; // E means East
}


/**/
    /*
    printSymbolsBetweenTwoRows - Display a symbol between two printed rows to
    make the board look more aesthitically pleasant 

    NAME

        printSymbolsBetweenTwoRows

    SYNOPSIS

        void Board::printSymbolsBetweenTwoRows()

    DESCRIPTION
        
        Used to make the printed format of the game board look prettier
        and more intuitive  

    RETURNS

        None

    AUTHOR

        Abhinav Thapaliya 

    DATE

        7/9/2019

*/
void Board::printSymbolsBetweenTwoRows(){
    char symbolToPrint = '|';
    cout << "\n   ";

    for(int i = 0; i < dimension; i++){
        cout << symbolToPrint << "   ";
    }

    cout << endl;
}


/**/
    /*
    moveNorthWest - Enable a player to move a piece northwest 

    NAME

        moveNorthWest

    SYNOPSIS

        bool Board::moveNorthWest(Piece *piece, int initialRow, int initialCol, bool & capturedAPiece )

    DESCRIPTION
        
        Used to make the printed format of the game board look prettier
        and more intuitive. captureAPiece is a boolean variable passed by reference 
        from the caller. This variable is set to true if the player can capture 
        a piece while moving northwest

    RETURNS

        True if the player successfully move northwest. Else false

    AUTHOR

        Abhinav Thapaliya 

    DATE

        7/9/2019

*/
bool Board::moveNorthWest(Piece *piece, int initialRow, int initialCol, bool & capturedAPiece ){
    // You can't go northwest if either the initialRow or the initialCol is 0, i.e
    // You can't move a piece northwest from either the first row or the first col of
    // of the gameBoard   
    if( 0 == initialRow || 0 == initialCol )
        return false;

    // gameBoard[initialRow - 1][initialCol -1] is the position to the northwest of 
    // gameBoard[initialRow][initialCol]

    return move( piece, initialRow, initialCol, initialRow - 1, initialCol - 1, capturedAPiece );
}


/**/
    /*
    moveNorthEast - Enable a player to move a piece northEast 

    NAME

        moveNorthEast

    SYNOPSIS

        bool Board::moveNorthEast(Piece *piece, int initialRow, int initialCol, bool & capturedAPiece )

    DESCRIPTION
        
        Used to make the printed format of the game board look prettier
        and more intuitive. captureAPiece is a boolean variable passed by reference 
        from the caller. This variable is set to true if the player can capture 
        a piece while moving northEast

    RETURNS

        True if the player successfully move northEast. Else false

    AUTHOR

        Abhinav Thapaliya 

    DATE

        7/9/2019

*/
bool Board::moveNorthEast(Piece *piece, int initialRow, int initialCol, bool & capturedAPiece ){
    // You can't go northeast if either the initialRow is 0 or the initialCol is dimension - 1, i.e
    // You can't move a piece northeast from either the first row or from the last col of
    // of the gameBoard   
    if( 0 == initialRow || dimension - 1 == initialCol )
        return false;

    // gameBoard[initialRow - 1][initialCol + 1] is the position to the northeast of 
    // gameBoard[initialRow][initialCol]

    return move( piece, initialRow, initialCol, getNortheastRow(initialRow), getNortheastCol(initialCol), capturedAPiece );
}


/**/
    /*
    moveSouthWest - Enable a player to move a piece SouthWest 

    NAME

        moveSouthWest

    SYNOPSIS

        bool Board::moveSouthWest(Piece *piece, int initialRow, int initialCol, bool & capturedAPiece )

    DESCRIPTION
        
        Used to make the printed format of the game board look prettier
        and more intuitive. captureAPiece is a boolean variable passed by reference 
        from the caller. This variable is set to true if the player can capture 
        a piece while moving SouthWest

    RETURNS

        True if the player successfully move SouthWest. Else false

    AUTHOR

        Abhinav Thapaliya 

    DATE

        7/9/2019

*/
bool Board::moveSouthWest(Piece *piece, int initialRow, int initialCol, bool & capturedAPiece){
    // You can't go southwest if either the initialRow is dimension - 1 or the initialCol is 0, i.e
    // You can't move a piece southwest from either the last row or from the first col of
    // of the gameBoard   
    if( dimension - 1 == initialRow || 0 == initialCol )
        return false;

    // gameBoard[initialRow + 1][initialCol - 1] is the position to the southwest of 
    // gameBoard[initialRow][initialCol]

    return move( piece, initialRow, initialCol, initialRow + 1, initialCol - 1, capturedAPiece );
}


/**/
    /*
    moveSouthEast - Enable a player to move a piece SouthEast 

    NAME

        moveSouthEast

    SYNOPSIS

        bool Board::moveSouthEast(Piece *piece, int initialRow, int initialCol, bool & capturedAPiece )

    DESCRIPTION
        
        Used to make the printed format of the game board look prettier
        and more intuitive. captureAPiece is a boolean variable passed by reference 
        from the caller. This variable is set to true if the player can capture 
        a piece while moving SouthEast

    RETURNS

        True if the player successfully move SouthEast. Else false

    AUTHOR

        Abhinav Thapaliya 

    DATE

        7/9/2019

*/
bool Board::moveSouthEast(Piece *piece, int initialRow, int initialCol, bool & capturedAPiece ){
    // You can't go southeast if either the initialRow or the initialCol is dimension - 1, i.e
    // You can't move a piece southeast from either the last row or the last col of
    // of the gameBoard   
    if( dimension - 1 == initialRow || dimension - 1 == initialCol )
        return false;

    // gameBoard[initialRow + 1][initialCol + 1] is the position to the southeast of 
    // gameBoard[initialRow][initialCol]

    return move( piece, initialRow, initialCol, initialRow + 1, initialCol + 1, capturedAPiece );
}


/**/
    /*
    move - Enable a player to move a piece legitimately to a destination
    spot in the board  

    NAME

        move

    SYNOPSIS

        bool Board::move(Piece *piece, int originRow, int originCol, int destinationRow, int destinationCol, bool & capturedAPiece)

    DESCRIPTION
        
        Enable a player to move a piece legitimately to a destination
        spot in the board. capturedAPiece is a boolean variable passed by reference 
        from the caller. This variable is set to true if the player can capture 
        a piece while moving SouthEast

    RETURNS

        True if the player successfully moved. false otherwise 

    AUTHOR

        Abhinav Thapaliya 

    DATE

        7/9/2019

*/
bool Board::move(Piece *piece, int originRow, int originCol, int destinationRow, int destinationCol, bool & capturedAPiece){
    Piece * pieceInDestinationSpot = gameBoard[destinationRow][destinationCol];

    // if there is already a piece in gameBoard[destinationRow][destinationCol]
    if( pieceInDestinationSpot != NULL ){
        
        // if the piece in the destination position does not belong to the opponent
        if( pieceInDestinationSpot->getColor() != piece->getOpponentsColor() )
            return false;

        // Check if the piece in the current position can capture opponent's piece
        if( !piece->getCapture() )
            return false;

        delete pieceInDestinationSpot;
        capturedAPiece = true;
    }

    // If the piece has reached one of the home points of the opponent, the piece should also be able to capture
    // opponent's piece
    if( hasReachedHomePoint(piece->getColor(), destinationRow, destinationCol ) ){
        piece->setCapture(true);
    }

    gameBoard[destinationRow][destinationCol] = piece;
    gameBoard[originRow][originCol] = NULL;

    return true; 
}


/**/
    /*
    getPiece - Get reference to a Piece object in the board given 
    row and column number of the piece 

    NAME

        getPiece

    SYNOPSIS

        Piece * Board::getPiece(int row, int col)

    DESCRIPTION
        
        Get reference to a Piece object in the board given 
        row and column number of the piece 

    RETURNS

        NULL if the row or column passed in the parameter are invalid. 
        Else, return a reference to a Piece object in the board 

    AUTHOR

        Abhinav Thapaliya 

    DATE

        7/9/2019

*/
Piece * Board::getPiece(int row, int col){
    if( row >= dimension || col >= dimension )
        return NULL;

    if( row < 0 || col < 0)
        return NULL;

    return gameBoard[row][col];
}


/**/
    /*
    hasReachedHomePoint - Check if the player making the move moved his piece
    to his opponent's home position

    NAME

        hasReachedHomePoint

    SYNOPSIS

        bool Board::hasReachedHomePoint( char playerColor, int destinationRow, int destinationCol )

    DESCRIPTION
        
        Check if the player making the move moved his piece
        to his opponent's home position 

    RETURNS

        True if the player making the move moved his piece to his opponent's home
        position. False otherwise 

    AUTHOR

        Abhinav Thapaliya 

    DATE

        7/10/2019

*/
bool Board::hasReachedHomePoint( char playerColor, int destinationRow, int destinationCol ){
    // In the figure below, if playerColor is Black edgePosition1 is the position in the 2nd row and the first column
    // If playerColor is White, edgePosition1 is the position in the dimension - 1 row, 1st column
    // If playerColor is Black, edgePosition2 is the position in the 2nd row, last column
    // If playerColor is White, edgePosition2 is the position in the second last row, last column  
    /*
           1   2   3   4   5
        1  W - W - W - W - W   
        2  W - - - - - - - W  
        3  
        4  B - - - - - - - B  
        5  B - B - B - B - B  
    */

    int edgePosition1Row = playerColor == Piece::BLACK? 1: dimension - 2;
    int edgePosition1Column = 0;

    int edgePosition2Row = playerColor == Piece::BLACK? 1: dimension - 2;
    int edgePosition2Column = dimension - 1;

    if( destinationRow == edgePosition1Row && destinationCol == edgePosition1Column)
        return true;

    if(destinationRow == edgePosition2Row && destinationCol == edgePosition2Column )
        return true;

    int homePointRow = playerColor == Piece::BLACK? 0: dimension - 1;

    if( destinationRow == homePointRow )
        return true;

    return false;
}


/**/
    /*
    hasReachedAllHomePoints - Check if the player making the move moved all of his pieces
    to his opponent's home positions

    NAME

        hasReachedAllHomePoints

    SYNOPSIS

        bool Board::hasReachedAllHomePoints(char playerColor)

    DESCRIPTION
        
        Check if the player making the move moved all of his pieces
        to his opponent's home positions

    RETURNS

        True if the player making the move moved all of his pieces to his opponent's home
        position. False otherwise 

    AUTHOR

        Abhinav Thapaliya 

    DATE

        7/10/2019

*/
bool Board::hasReachedAllHomePoints(char playerColor){
    // In the figure below, if playerColor is Black edgePosition1 is the position in the 2nd row and the first column
    // If playerColor is White, edgePosition1 is the position in the dimension - 1 row, 1st column
    // If playerColor is Black, edgePosition2 is the position in the 2nd row, last column
    // If playerColor is White, edgePosition2 is the position in the second last row, last column  
    /*
           1   2   3   4   5
        1  W - W - W - W - W   
        2  W - - - - - - - W  
        3  
        4  B - - - - - - - B  
        5  B - B - B - B - B  
    */

    // Start by checking if the home point row (either the first row or the last row, depending on playerColor ) has all
    // the pieces' colors are the same as playerColor
    int homePointRow = playerColor == Piece::BLACK? 0: dimension - 1;

    for(int i = 0; i < dimension; i++) {
        Piece * pieceToCheck = gameBoard[homePointRow][i];

        if( pieceToCheck == NULL || pieceToCheck->getColor() != playerColor )
            return false;
    }

    // Check if the piece's color in edgePosition1 and edgePosition2 is the same as playerColor
    int edgePosition1Row = playerColor == Piece::BLACK? 1: dimension - 2;
    int edgePosition1Column = 0;

    int edgePosition2Row = playerColor == Piece::BLACK? 1: dimension - 2;
    int edgePosition2Column = dimension - 1;

    return checkIfAPlayerReachedEdgePosition( playerColor, edgePosition1Row, edgePosition1Column ) &&
            checkIfAPlayerReachedEdgePosition( playerColor, edgePosition2Row, edgePosition2Column );
}


/**/
    /*
    checkIfAPlayerReachedEdgePosition - Check if the player reached an "edge" home position.

    NAME

        checkIfAPlayerReachedEdgePosition

    SYNOPSIS

        bool Board::checkIfAPlayerReachedEdgePosition(char playerColor, int edgePositionRow, int edgePositionColumn )

    DESCRIPTION
        
    // In the figure below, if playerColor is Black "edge" home positions are 2nd row, 1st column and 2nd row, last column.
    If playerColor is White, "edge" home positions are 2nd last row, 1st column and 2nd last row, last column.
           1   2   3   4   5
        1  W - W - W - W - W   
        2  W - - - - - - - W  
        3  
        4  B - - - - - - - B  
        5  B - B - B - B - B  

    RETURNS

        True if the player reached an "edge" position. False otherwise 

    AUTHOR

        Abhinav Thapaliya 

    DATE

        7/10/2019

*/
bool Board::checkIfAPlayerReachedEdgePosition(char playerColor, int edgePositionRow, int edgePositionColumn ){
    // Check if the piece's color in edgePosition1 is the same as playerColor
    Piece * edgePiece = gameBoard[edgePositionRow][edgePositionColumn];

    if( edgePiece == NULL || edgePiece->getColor() != playerColor )
        return false;

    return true;
}


/**/
    /*
    computePointsBasedOnHomePositions - Compute the total points a player got by occupying the 
    "home positions" that belong to their opponent

    NAME

        computePointsBasedOnHomePositions

    SYNOPSIS

        int Board::computePointsBasedOnHomePositions( char playerColor )

    DESCRIPTION
        
        A player can get different point depending on the opponent's "home position" he occupied. 

    RETURNS

        An integer that states the sum of points the player got by reaching opponent's home 
        positions. If the player has not reached opponents' home positions at all, return 0.  

    AUTHOR

        Abhinav Thapaliya 

    DATE

        7/10/2019

*/
int Board::computePointsBasedOnHomePositions( char playerColor ){
    int totalPoints = 0;

    // In the figure below, if playerColor is Black edgePosition1 is the position in the 2nd row and the first column
    // If playerColor is White, edgePosition1 is the position in the dimension - 1 row, 1st column
    // If playerColor is Black, edgePosition2 is the position in the 2nd row, last column
    // If playerColor is White, edgePosition2 is the position in the second last row, last column  
    /*
           1   2   3   4   5
        1  W - W - W - W - W   
        2  W - - - - - - - W  
        3  
        4  B - - - - - - - B  
        5  B - B - B - B - B  
    */

    // Start by checking if edgePosition1 has a piece whose color equals playerColor.
    // If yes, add 1 point to totalPoints
    // Check if the piece's color in edgePosition1 is the same as playerColor
    int edgePosition1Row = playerColor == Piece::BLACK? 1: dimension - 2;
    int edgePosition1Column = 0;
    if( checkIfAPlayerReachedEdgePosition(playerColor, edgePosition1Row, edgePosition1Column) )
        totalPoints++;

    // Start by checking if edgePosition2 has a piece whose color equals playerColor.
    // If yes, add 1 point to totalPoints
    // Check if the piece's color in edgePosition2 is the same as playerColor
    int edgePosition2Row = playerColor == Piece::BLACK? 1: dimension - 2;
    int edgePosition2Column = dimension - 1;
    if( checkIfAPlayerReachedEdgePosition(playerColor, edgePosition2Row, edgePosition2Column) )
        totalPoints++;

    // Start by checking if the home point row (either the first row or the last row, depending on playerColor ) has
    // the pieces' colors that are same as playerColor and add points based on a point weightage sysyem
    int homePointRow = playerColor == Piece::BLACK? 0: dimension - 1;

    for(int col = 0; col < dimension; col++){
        if( checkIfAPlayerReachedEdgePosition(playerColor, homePointRow, col ) )
            totalPoints += homePositionWeightageMap[col];
    }    

    return totalPoints;
}


/**/
    /*
    getPointForReachingAHomePosition - Compute the points a player got by occupying one of the 
    "home positions" that belong to their opponent

    NAME

        getPointForReachingAHomePosition

    SYNOPSIS

        int Board::getPointForReachingAHomePosition( int row, int col, char playerColor )

    DESCRIPTION
        
        A player can get different point depending on the opponent's "home position" he occupied. 

    RETURNS

        An integer that states the points the player got by reaching opponent's home 
        position. If the player has not reached opponent's home position, return 0.  

    AUTHOR

        Abhinav Thapaliya 

    DATE

        7/10/2019

*/
int Board::getPointForReachingAHomePosition( int row, int col, char playerColor ){
    if( row < 0 || col < 0 )
        return 0;

    if( col >= dimension || row >= dimension )
        return 0;

    // Start by checking if edgePosition1 has a piece whose color equals playerColor.
    // If yes, add 1 point to totalPoints
    // Check if the piece's color in edgePosition1 is the same as playerColor
    int edgePosition1Row = playerColor == Piece::BLACK? 1: dimension - 2;
    int edgePosition1Column = 0;
    if( row == edgePosition1Row && col == edgePosition1Column )
        return 1;

    // Start by checking if edgePosition2 has a piece whose color equals playerColor.
    // If yes, add 1 point to totalPoints
    // Check if the piece's color in edgePosition2 is the same as playerColor
    int edgePosition2Row = playerColor == Piece::BLACK? 1: dimension - 2;
    int edgePosition2Column = dimension - 1;
    if( row == edgePosition2Row && col == edgePosition2Column )
        return 1;

    // Start by checking if the home point row (either the first row or the last row, depending on playerColor ) has
    // the pieces' colors that are same as playerColor and compute points based on a point weightage sysyem
    int homePointRow = playerColor == Piece::BLACK? 0: dimension - 1;

    if( row == homePointRow )
        return homePositionWeightageMap[col];    
}


/**/
    /*
    writeToFile - Store the details of the board including the dimension and a text
    representation of the board pieces into a text file 

    NAME

        writeToFile

    SYNOPSIS

        void Board::writeToFile(ofstream &saveFile)

    DESCRIPTION
        
        White piece and Black piece that can't capture are written as 'W' and 'B'
        respectively. White piece and Black piece that can capture are written as 'WW' 
        and 'BB' respectively. Empty pieces (empty spots in the board) are denoted as
        'O'

    RETURNS

        None

    AUTHOR

        Abhinav Thapaliya 

    DATE

        7/10/2019

*/
void Board::writeToFile(ofstream &saveFile){
    saveFile << "Board:\n";
    for(int i = 0; i < dimension; i++){
        vector<Piece*> oneRow = gameBoard[i];

        saveOneRow( saveFile, oneRow );
    }

    saveFile << endl;
}



/**/
    /*
    saveOneRow - Save one row of the text representation of the board pieces 

    NAME

        saveOneRow

    SYNOPSIS

        void Board::saveOneRow( ofstream & saveFile, vector <Piece*> oneRow )

    DESCRIPTION
        
        White piece and Black piece that can't capture are written as 'W' and 'B'
        respectively. White piece and Black piece that can capture are written as 'WW' 
        and 'BB' respectively. Empty pieces (empty spots in the board) are denoted as
        'O'

    RETURNS

        None 

    AUTHOR

        Abhinav Thapaliya 

    DATE

        7/10/2019

*/
void Board::saveOneRow( ofstream & saveFile, vector <Piece*> oneRow ){
    saveFile << "\t";

    int rowSize = oneRow.size();

    for(int i = 0; i < rowSize; i++){
        Piece * toWrite = oneRow[i];
        if( toWrite == NULL ){
            saveFile << "O"; // Use symbolic constant
        }
        else{
            char currentColor = toWrite->getColor();

            saveFile << currentColor;
            if( toWrite->getCapture() )
                saveFile << currentColor;
        }

        saveFile << "  ";
    }

    saveFile << endl;
}


/**/
    /*
    getAllPiecesOfAColor - Get reference to all board pieces that are of the color
    specified in the parameter 

    NAME

        getAllPiecesOfAColor

    SYNOPSIS

        vector<Piece *> Board::getAllPiecesOfAColor(char playerColor)

    DESCRIPTION
        
        Get reference to all board pieces that are of the color specified in the
        parameter 

    RETURNS

        Vector of references to Piece objects that all have the same color.
        An empty vector if the board does not have pieces of the color specified 
        in this function's parameter  

    AUTHOR

        Abhinav Thapaliya 

    DATE

        7/10/2019

*/
vector<Piece *> Board::getAllPiecesOfAColor(char playerColor){
    vector <Piece *> result;

    for(int row = 0; row < dimension; row++){
        for(int col = 0; col < dimension; col++){
            Piece * piece = gameBoard[row][col];

            if( piece != NULL){
                if(piece->getColor() == playerColor )
                    result.push_back(piece);
            }
        }
    }

    return result;
}


/**/
    /*
    canCaptureInOneMove - Verify if a player can capture at least one of his
    opponent's piece in one move 

    NAME

        canCaptureInOneMove

    SYNOPSIS

        bool Board::canCaptureInOneMove(Piece *piece)

    DESCRIPTION
        
        Verify if a player can capture at least one of his opponent's piece
        in one move 

    RETURNS

        True if the player can capture at least one piece in one move. False 
        otherwise  

    AUTHOR

        Abhinav Thapaliya 

    DATE

        7/10/2019

*/
bool Board::canCaptureInOneMove(Piece *piece){

    if( !piece->getCapture() )
        return false;

    int currentRow = getRowOfAPiece(piece);
    int currentCol = getColumnOfAPiece(piece);

    int northeastRow = getNortheastRow( currentRow );
    int northeastCol = getNortheastCol( currentCol );

    int northwestRow = getNorthwestRow( currentRow );
    int northwestCol = getNortheastCol( currentCol );

    int southeastRow = getSoutheastRow( currentRow );
    int southeastCol = getSoutheastCol( currentCol );

    int southwestRow = getSouthwestRow( currentRow );
    int southwestCol = getSouthwestCol( currentCol );

    return checkCapture( piece, northeastRow, northeastCol) || checkCapture(piece, northwestRow, northwestCol) || checkCapture (piece, southeastRow, southeastCol ) || checkCapture( piece, southwestRow, southwestCol );
}


/**/
    /*
    getRowOfAPiece - Given a reference to a Piece object, compute its row in the 
    board

    NAME

        getRowOfAPiece

    SYNOPSIS

        int Board::getRowOfAPiece(Piece *piece)

    DESCRIPTION
        
        

    RETURNS

        If the piece specified in the parameter does not exist in the board, return
        an integer that denotes invalid value. Else return board row of the piece.
        If the piece exists in the 1st row, 0 is returned. IF it is in the 2nd row, 1 is
        returned. And so on.. 

    AUTHOR

        Abhinav Thapaliya 

    DATE

        7/10/2019

*/
int Board::getRowOfAPiece(Piece *piece){

    for(int row = 0; row < dimension; row++){
        for(int col = 0; col < dimension; col++ ){
            Piece * toCheck = gameBoard[row][col];

            if(toCheck == piece)
                return row;
        }
    }

    return INVALID_INDEX;
}


/**/
    /*
    getColumnOfAPiece - Given a reference to a Piece object, compute its column in the 
    board

    NAME

        getColumnOfAPiece

    SYNOPSIS

        int Board::getColumnOfAPiece(Piece *piece)

    DESCRIPTION
        
        Iterate through all elements in the board and see if the element equals 
        the value of the Piece object reference specified in the parameter. 

    RETURNS

        If the piece specified in the parameter does not exist in the board, return
        an integer that denotes invalid value. Else return board column of the piece.
        If the piece exists in the 1st column, 0 is returned. IF it is in the 2nd column, 1 is
        returned. And so on.. 

    AUTHOR

        Abhinav Thapaliya 

    DATE

        7/10/2019

*/
int Board::getColumnOfAPiece(Piece *piece){

    for(int row = 0; row < dimension; row++){
        for(int col = 0; col < dimension; col++ ){
            Piece * toCheck = gameBoard[row][col];

            if(toCheck == piece)
                return col;
        }
    }

    return INVALID_INDEX;
}


/**/
    /*
    checkCapture - Check if piece can capture another piece in the position specified 
    by row and col parameters 

    NAME

        checkCapture

    SYNOPSIS

        bool Board::checkCapture(Piece * possibleCapturerrrr, int row, int col)

    DESCRIPTION
        
         Check if piece can capture another piece in the position specified 
        by row and col parameters 

    RETURNS

        True if can capture in the position specified. False otherwise 

    AUTHOR

        Abhinav Thapaliya 

    DATE

        7/10/2019

*/
bool Board::checkCapture(Piece * possibleCapturerrrr, int row, int col){
    if( !possibleCapturerrrr->getCapture() )
        return false;

    Piece * possibleCapturee = getPiece( row, col );

    if( possibleCapturee == NULL ) // Can't capture an empty piece
        return false;

    if( possibleCapturee->getColor() == possibleCapturerrrr->getColor() ) //Can't capture piece of the same color (own piece)
        return false;

    return true;
}


/**/
    /*
    canCaptureDeadlyPieceInOneMove - Verify if a player can capture at least one of his
    opponent's deadly piece in one move 

    NAME

        canCaptureDeadlyPieceInOneMove

    SYNOPSIS

        bool Board::canCaptureDeadlyPieceInOneMove(Piece *onePiece)s

    DESCRIPTION
        
        Deadly piece is an opponent's piece that has the ability to capture the player's
        piece 

    RETURNS

        True if the player can capture at least one deadly piece in one move. False 
        otherwise  

    AUTHOR

        Abhinav Thapaliya 

    DATE

        7/10/2019

*/
bool Board::canCaptureDeadlyPieceInOneMove(Piece *onePiece){
    if( !onePiece->getCapture() )
        return false;

    int currentRow = getRowOfAPiece(onePiece);
    int currentCol = getColumnOfAPiece(onePiece);

    int northeastRow = getNortheastRow(currentRow);
    int northeastCol = getNortheastCol(currentCol);

    int northwestRow = getNorthwestRow(currentRow);
    int northwestCol = getNorthwestCol(currentCol);

    int southeastRow = getSoutheastRow(currentRow);
    int southeastCol = getSoutheastCol(currentCol);

    int southwestRow = getSouthwestRow(currentRow);
    int southwestCol = getSouthwestCol(currentCol);

    return isDeadlyPiece(onePiece, northeastRow, northeastCol) || isDeadlyPiece(onePiece, northwestRow, northwestCol) 
        || isDeadlyPiece(onePiece, southeastRow, southeastCol) || isDeadlyPiece(onePiece, southwestRow, southwestCol);
}


/**/
    /*
    isDeadlyPiece - Check if the piece in the row and column specified is a deadly piece

    NAME

        isDeadlyPiece

    SYNOPSIS

        bool Board::isDeadlyPiece(Piece *referencePiece, int deadlycurrentRow, int deadlycurrentCol)

    DESCRIPTION
         
        Deadly piece is an opponent's piece that has the ability to capture the player's
        piece  

    RETURNS

        True if the piece in the specified position is a deadly piece. False otherwise 

    AUTHOR

        Abhinav Thapaliya 

    DATE

        7/10/2019

*/
bool Board::isDeadlyPiece(Piece *referencePiece, int deadlycurrentRow, int deadlycurrentCol){
    
    Piece * potentiallyDeadlyPiece = getPiece(deadlycurrentRow, deadlycurrentCol );

    if(potentiallyDeadlyPiece == NULL)
        return false;

    // Check if the reference piece and the deadly piece are of the same color (belong to the same player).
    // if that happens, potentiallyDeadlyPiece is not a deadly piece as it can't capture pieces of the 
    // same color

    if( potentiallyDeadlyPiece->getColor() == referencePiece->getColor() )
        return false;

    if( potentiallyDeadlyPiece->getCapture() )
        return true;

    return false;
}


/**/
    /*
    getPiecesThatCanMoveToHomePointInOneMove - Get a collection of board pieces that can 
    go to opponent's home position in one move. 

    NAME

        getPiecesThatCanMoveToHomePointInOneMove

    SYNOPSIS

        vector<Piece *> Board::getPiecesThatCanMoveToHomePointInOneMove( char playerColor )

    DESCRIPTION
         
        Get a collection of board pieces that can go to opponent's home position in one move.
        The parameter, playerColor determines the color the pieces in the collection should have

    RETURNS

        A collection of board pieces 

    AUTHOR

        Abhinav Thapaliya 

    DATE

        7/10/2019

*/
vector<Piece *> Board::getPiecesThatCanMoveToHomePointInOneMove( char playerColor ){
    
    vector<Piece*> result;
    vector<Piece*> allPieces = getAllPiecesOfAColor( playerColor );

    for(int i = 0; i < allPieces.size(); i++){

        Piece * onePiece = allPieces[i];
        int pieceRow = getRowOfAPiece(onePiece);
        int pieceCol = getColumnOfAPiece(onePiece);

        // Already in home point
        if( hasReachedHomePoint( playerColor, pieceRow, pieceCol ) )
            continue;

        int northeastRow = getNortheastRow( pieceRow);
        int northeastCol = getNortheastCol( pieceCol );

        int northwestRow = getNorthwestRow( pieceRow );
        int northwestCol = getNorthwestCol( pieceCol );

        int southeastRow = getSoutheastRow( pieceRow );
        int southeastCol = getSoutheastCol( pieceCol );

        int southwestRow = getSouthwestRow( pieceRow );
        int southwestCol = getSouthwestCol( pieceCol );

        bool canMoveNortheast = canReachHomePointInOneMove( onePiece, northeastRow, northeastCol); 
        bool canMoveNorthwest = canReachHomePointInOneMove( onePiece, northwestRow, northwestCol );
        bool canMoveSoutheast = canReachHomePointInOneMove( onePiece, southeastRow, southeastCol);
        bool canMoveSouthwest = canReachHomePointInOneMove( onePiece, southwestRow, southwestCol );

        if( canMoveNortheast || canMoveNorthwest || canMoveSoutheast || canMoveSouthwest ){
            result.push_back( onePiece );         
        }
    }

    return result;
}


/**/
    /*
    getNortheastRow - Based on a row number, get row number of the row to the northeast

    NAME

        getNortheastRow

    SYNOPSIS

        int Board::getNortheastRow(int currentRow)

    DESCRIPTION
         
        Based on a row number, get row number of the row to the northeast

    RETURNS

        An integer varaible that states the row number of the row to the northeast of
        the row specified in the parameter 

    AUTHOR

        Abhinav Thapaliya 

    DATE

        7/10/2019

*/
int Board::getNortheastRow(int currentRow){
    return currentRow - 1;
}


/**/
    /*
    getNortheastCol - Based on a column number, get column number of the column to the northeast

    NAME

        getNortheastCol

    SYNOPSIS

        int Board::getNortheastCol(int currentCol)

    DESCRIPTION
         
        Based on a column number, get column number of the column to the northeast

    RETURNS

        An integer varaible that states the column number of the column to the northeast of
        the column specified in the parameter 

    AUTHOR

        Abhinav Thapaliya 

    DATE

        7/10/2019

*/
int Board::getNortheastCol(int currentCol ){
    return currentCol + 1;
}


/**/
    /*
    getNorthwestRow - Based on a row number, get row number of the row to the Northwest

    NAME

        getNorthwestRow

    SYNOPSIS

        int Board::getNorthwestRow(int currentRow)

    DESCRIPTION
         
        Based on a row number, get row number of the row to the Northwest

    RETURNS

        An integer varaible that states the row number of the row to the Northwest of
        the row specified in the parameter 

    AUTHOR

        Abhinav Thapaliya 

    DATE

        7/10/2019

*/
int Board::getNorthwestRow(int currentRow){
    return currentRow -1;
}


/**/
    /*
    getNorthwestCol - Based on a column number, get column number of the column to the Northwest

    NAME

        getNorthwestCol

    SYNOPSIS

        int Board::getNorthwestCol(int currentCol)

    DESCRIPTION
         
        Based on a column number, get column number of the column to the Northwest

    RETURNS

        An integer varaible that states the column number of the column to the Northwest of
        the column specified in the parameter 

    AUTHOR

        Abhinav Thapaliya 

    DATE

        7/10/2019

*/
int Board::getNorthwestCol(int currentCol ){
    return currentCol - 1;
}


/**/
    /*
    getSoutheastRow - Based on a row number, get row number of the row to the Southeast

    NAME

        getSoutheastRow

    SYNOPSIS

        int Board::getSoutheastRow(int currentRow)

    DESCRIPTION
         
        Based on a row number, get row number of the row to the Southeast

    RETURNS

        An integer varaible that states the row number of the row to the Southeast of
        the row specified in the parameter 

    AUTHOR

        Abhinav Thapaliya 

    DATE

        7/10/2019

*/
int Board::getSoutheastRow(int currentRow){
    return currentRow + 1;
}


/**/
    /*
    getSoutheastCol - Based on a column number, get column number of the column to the Southeast

    NAME

        getSoutheastCol

    SYNOPSIS

        int Board::getSoutheastCol(int currentCol)

    DESCRIPTION
         
        Based on a column number, get column number of the column to the Southeast

    RETURNS

        An integer varaible that states the column number of the column to the Southeast of
        the column specified in the parameter 

    AUTHOR

        Abhinav Thapaliya 

    DATE

        7/10/2019

*/
int Board::getSoutheastCol(int currentCol){
    return currentCol + 1;
}


/**/
    /*
    getSouthwestRow - Based on a row number, get row number of the row to the Southwest

    NAME

        getSouthwestRow

    SYNOPSIS

        int Board::getSouthwestRow(int currentRow)

    DESCRIPTION
         
        Based on a row number, get row number of the row to the Southwest

    RETURNS

        An integer varaible that states the row number of the row to the Southwest of
        the row specified in the parameter 

    AUTHOR

        Abhinav Thapaliya 

    DATE

        7/10/2019

*/
int Board::getSouthwestRow(int currentRow){
    return currentRow + 1;
}


/**/
    /*
    getSouthwestCol - Based on a column number, get column number of the column to the Southwest

    NAME

        getSouthwestCol

    SYNOPSIS

        int Board::getSouthwestCol(int currentCol)

    DESCRIPTION
         
        Based on a column number, get column number of the column to the Southwest

    RETURNS

        An integer varaible that states the column number of the column to the Southwest of
        the column specified in the parameter 

    AUTHOR

        Abhinav Thapaliya 

    DATE

        7/10/2019

*/
int Board::getSouthwestCol(int currentCol){
    return currentCol - 1;
}


/**/
    /*
    canReachHomePointInOneMove - Determine if the player can move its piece to the
    opponent's home position in one move 

    NAME

        canReachHomePointInOneMove

    SYNOPSIS

        bool Board::canReachHomePointInOneMove( Piece * piece, int row, int col )

    DESCRIPTION
         
        The integer variables, row and col specified in the parameters determine the position
        in which the poece specified in the parameter should be able to move 

    RETURNS

        True if the player can move the piece specfied in the parameter to a home
        position. False otherwise 

    AUTHOR

        Abhinav Thapaliya 

    DATE

        7/12/2019

*/
bool Board::canReachHomePointInOneMove( Piece * piece, int row, int col ){
    if( row < 0 || col < 0 )
        return false;

    if( row >= dimension || col >= dimension )
        return false;

    if(piece == NULL)
        return false;

    Piece * inHomePoint = gameBoard[row][col];

    if( inHomePoint == NULL ){
        return hasReachedHomePoint( piece->getColor(), row, col );
    }

    if( piece->getColor() == inHomePoint->getColor() ){
        return false;
    }

    // At this point, there is a piece already in the home position
    return piece->getCapture() && hasReachedHomePoint( piece->getColor(), row, col );
}


/**/
    /*
    getPiecesThatCanMoveTowardsHomePosition - Get the best collection of piece objects

    NAME

        getPiecesThatCanMoveTowardsHomePosition

    SYNOPSIS

        vector<Piece*> Board::getPiecesThatCanMoveTowardsHomePosition( vector<Piece*> pieces, char playerColor )

    DESCRIPTION
         
        Get the best collection of piece objects. If no piece can move towards home position,
        get a collection of pieces that can move away from home position.

    RETURNS

        A collection of reference to piece objects that can move towards home position. If no
        piece can move towards home position, get a collection of pieces that can move away 
        from home position. If no piece can move at all, return an empty vector  

    AUTHOR

        Abhinav Thapaliya 

    DATE

        7/12/2019

*/
vector<Piece*> Board::getPiecesThatCanMoveTowardsHomePosition( vector<Piece*> pieces, char playerColor ){

    if( pieces.size() == 0 || !(playerColor == Piece::BLACK || playerColor == Piece::WHITE) )
        return pieces;

    int minRow = INT_MAX;
    int maxRow = INT_MIN;

    for(int i = 0; i < pieces.size(); i++){
        Piece * onePiece = pieces[i];

        int pieceRow = getRowOfAPiece(onePiece);
        int pieceCol = getColumnOfAPiece( onePiece );

        if( hasReachedHomePoint( playerColor, pieceRow, pieceCol ) )
            continue;

        if( playerColor == Piece::BLACK ){
            if( canMoveNortheast(  pieceRow, pieceCol ) || canMoveNorthwest(pieceRow, pieceCol ) ){
                if( pieceRow - 1 < minRow )
                    minRow = pieceRow;
            }
            else if( canMoveSoutheast( pieceRow, pieceCol ) || canMoveSouthwest( pieceRow, pieceCol ) ){
                if( pieceRow + 1 < minRow )
                    minRow = pieceRow;
            }
        } 
        else{
            if( canMoveSoutheast( pieceRow, pieceCol ) || canMoveSouthwest( pieceRow, pieceCol) ){
                if( pieceRow + 1 > maxRow )
                    maxRow = pieceRow;
            }
            else if( canMoveNortheast( pieceRow, pieceCol ) || canMoveNorthwest( pieceRow, pieceCol ) ){
                if( pieceRow - 1 > maxRow )
                    maxRow = pieceRow;               
            }
        }
    }

    vector<Piece*> piecesInTheRowClosestToTheHomePos;

    if( playerColor == Piece::BLACK )
        piecesInTheRowClosestToTheHomePos = getCertainPiecesFromARow( minRow, playerColor );
    else
        piecesInTheRowClosestToTheHomePos =  getCertainPiecesFromARow( maxRow, playerColor );

    return filterOutPiecesThatCantMove( piecesInTheRowClosestToTheHomePos, playerColor );
}


/**/
    /*
    canMoveNortheast - Determine if the piece in the specified position can move northeast 

    NAME

        canMoveNortheast

    SYNOPSIS

        bool Board::canMoveNortheast( int row, int col )

    DESCRIPTION
         
        Determine if the piece in the specified position can move northeast. 

    RETURNS

        True if the piece in the speicifed position can move in the direction specified.
        False otherwise 

    AUTHOR

        Abhinav Thapaliya 

    DATE

        7/12/2019

*/
bool Board::canMoveNortheast( int row, int col ){
    if( row <= 0 || col < 0)
        return false;

    if( row >= dimension || col >= dimension - 1 )
        return false; 

    int northeastRow = getNortheastRow( row );
    int northeastCol = getNortheastCol( col );

    return canMove( row, col, northeastRow, northeastCol );
}


/**/
    /*
    canMoveNorthwest - Determine if the piece in the specified position can move Northwest 

    NAME

        canMoveNorthwest

    SYNOPSIS

        bool Board::canMoveNorthwest(int row, int col)

    DESCRIPTION
         
        Determine if the piece in the specified position can move Northwest. 

    RETURNS

        True if the piece in the speicifed position can move in the direction specified.
        False otherwise 

    AUTHOR

        Abhinav Thapaliya 

    DATE

        7/12/2019

*/
bool Board::canMoveNorthwest(int row, int col){
    if( row <= 0 || col < 1)
        return false;

    if( row >= dimension || col >= dimension )
        return false; 

    int destinationRow = getNorthwestRow( row); 
    int destinationCol = getNorthwestCol( col);
    return canMove( row, col, destinationRow, destinationCol ); 
}



/**/
    /*
    canMoveSoutheast - Determine if the piece in the specified position can move Southeast 

    NAME

        canMoveSoutheast

    SYNOPSIS

        bool Board::canMoveSoutheast(int row, int col)

    DESCRIPTION
         
        Determine if the piece in the specified position can move Southeast. 

    RETURNS

        True if the piece in the speicifed position can move in the direction specified.
        False otherwise 

    AUTHOR

        Abhinav Thapaliya 

    DATE

        7/12/2019

*/
bool Board::canMoveSoutheast(int row, int col){
    if( row < 0 || col < 0)
        return false;

    if( row >= dimension - 1 || col >= dimension - 1 )
        return false; 

    int destinationRow = getSoutheastRow( row); 
    int destinationCol = getSoutheastCol( col);
    return canMove( row, col, destinationRow, destinationCol ); 
}


/**/
    /*
    canMoveSouthwest - Determine if the piece in the specified position can move Southwest 

    NAME

        canMoveSouthwest

    SYNOPSIS

        bool Board::canMoveSouthwest(int row, int col)

    DESCRIPTION
         
        Determine if the piece in the specified position can move Southwest. 

    RETURNS

        True if the piece in the speicifed position can move in the direction specified.
        False otherwise 

    AUTHOR

        Abhinav Thapaliya 

    DATE

        7/12/2019

*/
bool Board::canMoveSouthwest(int row, int col){
    if( row < 0 || col < 1)
        return false;

    if( row >= dimension - 1 || col >= dimension )
        return false; 

    int destinationRow = getSouthwestRow( row); 
    int destinationCol = getSouthwestCol( col);
    return canMove( row, col, destinationRow, destinationCol ); 
}


/**/
    /*
    canMove - Determine if a piece in the origin spot can move to destination position 

    NAME

        canMove

    SYNOPSIS

        bool Board::canMove(int originRow, int originCol, int destinationRow, int destinationCol)

    DESCRIPTION
         
        Determine if a piece in the origin spot can move to destination position 

    RETURNS

        True if the piece in the origin position can move to the destination position.
        False otherwise 

    AUTHOR

        Abhinav Thapaliya 

    DATE

        7/12/2019

*/
bool Board::canMove(int originRow, int originCol, int destinationRow, int destinationCol){
    Piece * pieceToMove = gameBoard[originRow][originCol];

    if( pieceToMove == NULL )
        return false;

    char playerColor = pieceToMove->getColor();

    Piece * pieceInDirectionSpecified = getPiece( destinationRow, destinationCol );

    if( pieceInDirectionSpecified == NULL)
        return true;

    if( pieceInDirectionSpecified->getColor() == playerColor )
        return false;

    if( pieceToMove->getCapture() )
        return true; 
}


/**/
    /*
    getCertainPiecesFromARow - Get all the pieces that have the same color from a
    row in the board

    NAME

        getCertainPiecesFromARow

    SYNOPSIS

        vector<Piece *> Board::getCertainPiecesFromARow(int row, char playerColor)

    DESCRIPTION
         
        Get all the pieces that have the same color from arow in the board

    RETURNS

        A collection of reference to Piece objects 

    AUTHOR

        Abhinav Thapaliya 

    DATE

        7/12/2019

*/
vector<Piece *> Board::getCertainPiecesFromARow(int row, char playerColor){
    vector<Piece*> result;

    if( row < 0 || row >= dimension )
        return result;

    for(int col = 0; col < dimension; col++){
        Piece * aPiece = gameBoard[row][col];

        if( aPiece != NULL ){
            if( aPiece->getColor() == playerColor)
                result.push_back( aPiece );
        }
    }

    return result;
}


/**/
    /*
    filterOutPiecesThatCantMove - Given a collection of reference to Piece objects, filter out 
    any pieces that can't move legitimately in at least one direction

    NAME

        filterOutPiecesThatCantMove

    SYNOPSIS

        vector<Piece*> Board::filterOutPiecesThatCantMove(vector<Piece*> pieces, char playerColor)

    DESCRIPTION
         
        

    RETURNS

        A collection of reference to Piece objects 

    AUTHOR

        Abhinav Thapaliya 

    DATE

        7/12/2019

*/
vector<Piece*> Board::filterOutPiecesThatCantMove(vector<Piece*> pieces, char playerColor){
    vector <Piece*> canMoveTowardsHomePosition;

    for( int i = 0; i < pieces.size(); i++ ){
        Piece * onePiece = pieces[i];

        int pieceRow = getRowOfAPiece(onePiece);
        int pieceCol = getColumnOfAPiece( onePiece );

        if( hasReachedHomePoint( playerColor, pieceRow, pieceCol ) )
            continue;

        if( playerColor == Piece::BLACK ){
            if( canMoveNortheast(  pieceRow, pieceCol ) || canMoveNorthwest(pieceRow, pieceCol ) ){
                canMoveTowardsHomePosition.push_back( onePiece );
            }
        } 
        else{
            if( canMoveSoutheast( pieceRow, pieceCol ) || canMoveSouthwest( pieceRow, pieceCol) ){
                canMoveTowardsHomePosition.push_back( onePiece );
            }
        }
    }

    if( canMoveTowardsHomePosition.size() == 0)
        return getPiecesThatCanMoveAwayFromHomePosition( pieces, playerColor );

    return canMoveTowardsHomePosition;
}


/**/
    /*
    getPiecesThatCanMoveAwayFromHomePosition - Given a collection of reference to Piece objects, get
    a collection of reference to Piece objects that can move in direction away from opponent's 
    home position

    NAME

        getPiecesThatCanMoveAwayFromHomePosition

    SYNOPSIS

        vector<Piece*> Board::getPiecesThatCanMoveAwayFromHomePosition(vector<Piece*> pieces, char playerColor)

    DESCRIPTION
         
        For piece of Black color, away from home position is towards South. If the pieces have
        White color, away from home position is towards north

    RETURNS

        A collection of reference to Piece objects 

    AUTHOR

        Abhinav Thapaliya 

    DATE

        7/12/2019

*/
vector<Piece*> Board::getPiecesThatCanMoveAwayFromHomePosition(vector<Piece*> pieces, char playerColor){
    vector <Piece*> result;

    for(int i = 0; i < pieces.size(); i++){
        Piece * onePiece = pieces[i];

        int pieceRow = getRowOfAPiece(onePiece);
        int pieceCol = getColumnOfAPiece( onePiece );

        if( hasReachedHomePoint( playerColor, pieceRow, pieceCol ) )
            continue;

        if( playerColor == Piece::BLACK ){

            if( canMoveSoutheast( pieceRow, pieceCol ) || canMoveSouthwest( pieceRow, pieceCol ) )
                result.push_back(onePiece);
        } 
        else{
            if( canMoveNortheast( pieceRow, pieceCol ) || canMoveNorthwest( pieceRow, pieceCol ) )
                result.push_back( onePiece );    
        }
    }

    return result;
}


/**/
    /*
    getBestPieceThatCanMoveTowardsHomePos - Given a collection of reference to Piece objects, get
    the "best" piece towards opponent's home position. 

    NAME

        getBestPieceThatCanMoveTowardsHomePos

    SYNOPSIS

        Piece * Board::getBestPieceThatCanMoveTowardsHomePos( vector<Piece*> aRowOfpieces, char playerColor, int & optimalDirectionToMoveThePieceIn )

    DESCRIPTION
         
        "Best" piece is the piece that can move to 
        the most valuable column. Most valuable column is determined by the points a player can get
        by reaching opponent's home row. For a player playing black, opponent's home row is the first row. 
        For a player playing white, opponent's home row is the last row. Reaching certain positions in
        the opponent's home row can be more valuable than reaching other positions. 

        The example below may help clarify the description above. 
        Below the numbers not in the bracket are the column numbers. Column numbers increase from
        left to right. The numbers in the bracket state the point a player can get when he moves
        its piece to that column. 

        1(3) - 2(1) - 3(5) - 4(1) - 5(3)  

        For instance, if a player can move his piece to 3rd column, he will 
        get 5 points. If he can move his piece to the 5th column, he will get 3 points. In the example
        above, the third column is the most valuable column. So, in a collection of Piece objects, if
        there is a piece that can move to thr 5th column and if there is a piece that can move to the
        3rd column, this function would return the piece that can move to the 3rd column.

    RETURNS

        A reference to Piece object. If no pieces can move, return null 

    AUTHOR

        Abhinav Thapaliya 

    DATE

        7/12/2019

*/
Piece * Board::getBestPieceThatCanMoveTowardsHomePos( vector<Piece*> aRowOfpieces, char playerColor, int & optimalDirectionToMoveThePieceIn ) {
    // All pieces in aRowOfPieces belong to the same row in gameBoard
    if( aRowOfpieces.size() == 0)
        return NULL;

    Piece * toReturn = NULL;
    Piece * testPiece = aRowOfpieces[0];
    int rowNumber = getRowOfAPiece( testPiece );

    if( canMoveTowardsHomePosition(testPiece, playerColor) ){
        if( playerColor == Piece::BLACK ){
            return getBestBlackPieceThatCanMoveTowardsHomePos( aRowOfpieces, playerColor, optimalDirectionToMoveThePieceIn, rowNumber );
        }
        else if(playerColor == Piece::WHITE )
            return getBestWhitePieceThatCanMoveTowardsHomePos( aRowOfpieces, playerColor, optimalDirectionToMoveThePieceIn, rowNumber );
    }
    else
        return getBestPieceThatCanMoveAwayFromHomePos( aRowOfpieces, playerColor, optimalDirectionToMoveThePieceIn );
}


/**/
    /*
    canMoveTowardsHomePosition - Determine if a piece specified in the parameter can move
    towardds opponent's home position

    NAME

        canMoveTowardsHomePosition

    SYNOPSIS

        bool Board::canMoveTowardsHomePosition(Piece *aPiece, char playerColor)

    DESCRIPTION
         
        For piece of Black color, opponent's home position is towards North. If the pieces have
        White color, opponent's home position is towards South

    RETURNS

        True if the piece specified in the parameter can move towards opponent's home
        position. false otherwise  

    AUTHOR

        Abhinav Thapaliya 

    DATE

        7/12/2019

*/
bool Board::canMoveTowardsHomePosition(Piece *aPiece, char playerColor){
    if( aPiece == NULL || !(playerColor == Piece::BLACK || playerColor == Piece::WHITE ) )
        return false;

    int row = getRowOfAPiece( aPiece );
    int col = getColumnOfAPiece( aPiece ); 

    // For a player playing black, home position is towards north
    if( playerColor == Piece::BLACK ){
        if( canMoveNortheast(row, col) || canMoveNorthwest( row, col ) )
            return true;
    }

    // For a player playing white, home position is towards south
    if( playerColor == Piece::WHITE ){
        if( canMoveSoutheast(row, col) || canMoveSouthwest(row, col) )
            return true;
    }

    return false;
}


/**/
    /*
    getBestPieceThatCanMoveAwayFromHomePos - Get the best piece that can move away from opponent's 
    home position. Best piece is the piece that can go to the most valuable column

    NAME

        getBestPieceThatCanMoveAwayFromHomePos

    SYNOPSIS

        Piece * Board::getBestPieceThatCanMoveAwayFromHomePos( vector<Piece*> aRowOfpieces, char playerColor, int & optimalDirectionToMoveThePieceIn )

    DESCRIPTION
         
        For piece of Black color, away from opponent's home position is towards South. If the piece 
        have White color, away from opponent's home position is towards North.

        "Best" piece is the piece that can move to the most valuable column. Most valuable column
        is determined by the points a player can get
        by reaching opponent's home row. For a player playing black, opponent's home row is the first row. 
        For a player playing white, opponent's home row is the last row. Reaching certain positions in
        the opponent's home row can be more valuable than reaching other positions. 

        The example below may help clarify the description above. 
        Below the numbers not in the bracket are the column numbers. Column numbers increase from
        left to right. The numbers in the bracket state the point a player can get when he moves
        its piece to that column. 

        1(3) - 2(1) - 3(5) - 4(1) - 5(3)  

        For instance, if a player can move his piece to 3rd column, he will 
        get 5 points. If he can move his piece to the 5th column, he will get 3 points. In the example
        above, the third column is the most valuable column. So, in a collection of Piece objects, if
        there is a piece that can move to thr 5th column and if there is a piece that can move to the
        3rd column, this function would return the piece that can move to the 3rd column.

    RETURNS

        Reference to a Piece object if there is a piece that can move away from opponent's home
        position. Null if there is no piece that can move away from opponent's home position  

    AUTHOR

        Abhinav Thapaliya 

    DATE

        7/12/2019

*/
Piece * Board::getBestPieceThatCanMoveAwayFromHomePos( vector<Piece*> aRowOfpieces, char playerColor, int & optimalDirectionToMoveThePieceIn ) {

    if( aRowOfpieces.size() == 0)
        return NULL;

    Piece * toReturn = NULL;
    Piece * testPiece = aRowOfpieces[0];
    int rowNumber = getRowOfAPiece( testPiece );

    // int columnAdjustmentBlack = rowNumber % 2 == 0? 

    if( playerColor == Piece::BLACK ){
        return getBestBlackPieceThatCanMoveAwayFromHomePos( aRowOfpieces, playerColor, optimalDirectionToMoveThePieceIn, rowNumber );
    }
    else if(playerColor == Piece::WHITE )
        return getBestWhitePieceThatCanMoveAwayFromHomePos( aRowOfpieces, playerColor, optimalDirectionToMoveThePieceIn, rowNumber );  
}


void Board::findDestinationColWithMaxPoints(int destinationCol, int & maxHomePoints, Piece * & toReturn, Piece * onePiece, int & optimalDirectionToMoveThePieceIn, int direction ){
    int possibleHomePoints = homePositionWeightageMap[destinationCol];

    if(possibleHomePoints > maxHomePoints ){
        toReturn = onePiece;
        optimalDirectionToMoveThePieceIn = direction;
        maxHomePoints = possibleHomePoints;
    }

}


/**/
    /*
    getBestBlackPieceThatCanMoveTowardsHomePos - Get the best piece that can move towards opponent's 
    home position. Best piece is the piece that can go to the most valuable column

    NAME

        getBestBlackPieceThatCanMoveTowardsHomePos

    SYNOPSIS

    Piece *Board::getBestBlackPieceThatCanMoveTowardsHomePos( vector<Piece*> aRowOfpieces, char playerColor, int &optimalDirectionToMoveThePieceIn, int rowNumber)

    DESCRIPTION
         
        For piece of Black color, oppoonent's home position is towards North. 

        "Best" piece is the piece that can move to the most valuable column. Most valuable column
        is determined by the points a player can get
        by reaching opponent's home row. For a player playing black, opponent's home row is the first row. 
        For a player playing white, opponent's home row is the last row. Reaching certain positions in
        the opponent's home row can be more valuable than reaching other positions. 

        The example below may help clarify the description above. 
        Below the numbers not in the bracket are the column numbers. Column numbers increase from
        left to right. The numbers in the bracket state the point a player can get when he moves
        its piece to that column. 

        1(3) - 2(1) - 3(5) - 4(1) - 5(3)  

        For instance, if a player can move his piece to 3rd column, he will 
        get 5 points. If he can move his piece to the 5th column, he will get 3 points. In the example
        above, the third column is the most valuable column. So, in a collection of Piece objects, if
        there is a piece that can move to thr 5th column and if there is a piece that can move to the
        3rd column, this function would return the piece that can move to the 3rd column.

    RETURNS

        Reference to a Piece object if there is a piece that can move towards opponent's home
        position. Null if there is no piece that can move towards opponent's home position  

    AUTHOR

        Abhinav Thapaliya 

    DATE

        7/12/2019

*/
Piece *Board::getBestBlackPieceThatCanMoveTowardsHomePos( vector<Piece*> aRowOfpieces, char playerColor, int &optimalDirectionToMoveThePieceIn, int rowNumber){
    Piece * toReturn = NULL;
    int maxHomePoints = 0;

    for(int i = 0; i < aRowOfpieces.size(); i++ ){
        Piece * onePiece = aRowOfpieces[i];

        int boardColumnNumberOfOnePiece = getColumnOfAPiece( onePiece ); 

        // For a black piece, home position is towards north
        if( canMoveNortheast( rowNumber, boardColumnNumberOfOnePiece) ){
            int destinationCol = getNortheastCol( boardColumnNumberOfOnePiece );
            findDestinationColWithMaxPoints( destinationCol, maxHomePoints, toReturn, onePiece, optimalDirectionToMoveThePieceIn, MOVE_NORTHEAST );
        }

        if( canMoveNorthwest( rowNumber, boardColumnNumberOfOnePiece) ){
            int destinationCol = getNorthwestCol( boardColumnNumberOfOnePiece );
            findDestinationColWithMaxPoints( destinationCol, maxHomePoints, toReturn, onePiece, optimalDirectionToMoveThePieceIn, MOVE_NORTHWEST );
        }
    }

    return toReturn;
}


/**/
    /*
    getBestWhitePieceThatCanMoveTowardsHomePos - Given a collection of white pieces, get the
    best white piece that can move towards opponent's home position. Best piece is the
    piece that can go to the most valuable column

    NAME

        getBestWhitePieceThatCanMoveTowardsHomePos

    SYNOPSIS

    Piece *Board::getBestWhitePieceThatCanMoveTowardsHomePos( vector<Piece*> aRowOfpieces, char playerColor, int &optimalDirectionToMoveThePieceIn, int rowNumber )

    DESCRIPTION
         
        For piece of White color, oppoonent's home position is towards South. 

        "Best" piece is the piece that can move to the most valuable column. Most valuable column
        is determined by the points a player can get
        by reaching opponent's home row. For a player playing black, opponent's home row is the first row. 
        For a player playing white, opponent's home row is the last row. Reaching certain positions in
        the opponent's home row can be more valuable than reaching other positions. 

        The example below may help clarify the description above. 
        Below the numbers not in the bracket are the column numbers. Column numbers increase from
        left to right. The numbers in the bracket state the point a player can get when he moves
        its piece to that column. 

        1(3) - 2(1) - 3(5) - 4(1) - 5(3)  

        For instance, if a player can move his piece to 3rd column, he will 
        get 5 points. If he can move his piece to the 5th column, he will get 3 points. In the example
        above, the third column is the most valuable column. So, in a collection of Piece objects, if
        there is a piece that can move to thr 5th column and if there is a piece that can move to the
        3rd column, this function would return the piece that can move to the 3rd column.

    RETURNS

        Reference to a Piece object if there is a piece that can move towards opponent's home
        position. Null if there is no piece that can move towards opponent's home position  

    AUTHOR

        Abhinav Thapaliya 

    DATE

        7/12/2019

*/
Piece *Board::getBestWhitePieceThatCanMoveTowardsHomePos( vector<Piece*> aRowOfpieces, char playerColor, int &optimalDirectionToMoveThePieceIn, int rowNumber ){
    Piece * toReturn = NULL;
    int maxHomePoints = 0;

    // For a white piece, home position is towards south
    for(int i = 0; i < aRowOfpieces.size(); i++ ){
        Piece * onePiece = aRowOfpieces[i];

        int boardColumnNumberOfOnePiece = getColumnOfAPiece( onePiece ); 

        if( canMoveSoutheast( rowNumber, boardColumnNumberOfOnePiece) ){
            int destinationCol = getSoutheastCol( boardColumnNumberOfOnePiece );
            findDestinationColWithMaxPoints( destinationCol, maxHomePoints, toReturn, onePiece, optimalDirectionToMoveThePieceIn, MOVE_SOUTHEAST );
        }

        if( canMoveSouthwest( rowNumber, boardColumnNumberOfOnePiece) ){
            int destinationCol = getSouthwestCol( boardColumnNumberOfOnePiece );
            findDestinationColWithMaxPoints( destinationCol, maxHomePoints, toReturn, onePiece, optimalDirectionToMoveThePieceIn, MOVE_SOUTHWEST );
        }
    }
    
    return toReturn;
}


/**/
    /*
    getBestBlackPieceThatCanMoveAwayFromHomePos - Given a collection of black pieces, get the
    best black piece that can move away from opponent's home position. Best piece is the
    piece that can go to the most valuable column

    NAME

        getBestBlackPieceThatCanMoveAwayFromHomePos

    SYNOPSIS

    Piece *Board::getBestBlackPieceThatCanMoveAwayFromHomePos(vector<Piece*> aRowOfpieces, char playerColor, int &optimalDirectionToMoveThePieceIn, int rowNumber)

    DESCRIPTION
         
        For piece of Black color, away from oppoonent's home position is towards South. 

        "Best" piece is the piece that can move to the most valuable column. Most valuable column
        is determined by the points a player can get
        by reaching opponent's home row. For a player playing black, opponent's home row is the first row. 
        For a player playing white, opponent's home row is the last row. Reaching certain positions in
        the opponent's home row can be more valuable than reaching other positions. 

        The example below may help clarify the description above. 
        Below the numbers not in the bracket are the column numbers. Column numbers increase from
        left to right. The numbers in the bracket state the point a player can get when he moves
        its piece to that column. 

        1(3) - 2(1) - 3(5) - 4(1) - 5(3)  

        For instance, if a player can move his piece to 3rd column, he will 
        get 5 points. If he can move his piece to the 5th column, he will get 3 points. In the example
        above, the third column is the most valuable column. So, in a collection of Piece objects, if
        there is a piece that can move to thr 5th column and if there is a piece that can move to the
        3rd column, this function would return the piece that can move to the 3rd column.

    RETURNS

        Reference to a Piece object if there is a piece that can move towards opponent's home
        position. Null if there is no piece that can move towards opponent's home position  

    AUTHOR

        Abhinav Thapaliya 

    DATE

        7/12/2019

*/
Piece *Board::getBestBlackPieceThatCanMoveAwayFromHomePos(vector<Piece*> aRowOfpieces, char playerColor, int &optimalDirectionToMoveThePieceIn, int rowNumber){
    Piece * toReturn = NULL;
    int maxHomePoints = 0;

    // For a black piece, away from home position is towards south
    for(int i = 0; i < aRowOfpieces.size(); i++ ){
        Piece * onePiece = aRowOfpieces[i];

        int boardColumnNumberOfOnePiece = getColumnOfAPiece( onePiece ); 

        if( canMoveSoutheast( rowNumber, boardColumnNumberOfOnePiece) ){
            int destinationCol = getSoutheastCol( boardColumnNumberOfOnePiece );
            findDestinationColWithMaxPoints( destinationCol, maxHomePoints, toReturn, onePiece, optimalDirectionToMoveThePieceIn, MOVE_SOUTHEAST );
        }

        if( canMoveSouthwest( rowNumber, boardColumnNumberOfOnePiece) ){
            int destinationCol = getSouthwestCol( boardColumnNumberOfOnePiece );
            findDestinationColWithMaxPoints( destinationCol, maxHomePoints, toReturn, onePiece, optimalDirectionToMoveThePieceIn, MOVE_SOUTHWEST );
        }
    }
    
    return toReturn;
}


/**/
    /*
    getBestWhitePieceThatCanMoveAwayFromHomePos - Given a collection of white pieces, get the
    best white piece that can move away from opponent's home position. Best piece is the
    piece that can go to the most valuable column

    NAME

        getBestWhitePieceThatCanMoveAwayFromHomePos

    SYNOPSIS

    Piece *Board::getBestWhitePieceThatCanMoveAwayFromHomePos(std::vector<Piece*> aRowOfpieces, char playerColor, int &optimalDirectionToMoveThePieceIn, int rowNumber)
    
    DESCRIPTION
         
        For piece of white color, away from oppoonent's home position is towards North. 

        "Best" piece is the piece that can move to the most valuable column. Most valuable column
        is determined by the points a player can get
        by reaching opponent's home row. For a player playing black, opponent's home row is the first row. 
        For a player playing white, opponent's home row is the last row. Reaching certain positions in
        the opponent's home row can be more valuable than reaching other positions. 

        The example below may help clarify the description above. 
        Below the numbers not in the bracket are the column numbers. Column numbers increase from
        left to right. The numbers in the bracket state the point a player can get when he moves
        its piece to that column. 

        1(3) - 2(1) - 3(5) - 4(1) - 5(3)  

        For instance, if a player can move his piece to 3rd column, he will 
        get 5 points. If he can move his piece to the 5th column, he will get 3 points. In the example
        above, the third column is the most valuable column. So, in a collection of Piece objects, if
        there is a piece that can move to thr 5th column and if there is a piece that can move to the
        3rd column, this function would return the piece that can move to the 3rd column.

    RETURNS

        Reference to a Piece object if there is a piece that can move towards opponent's home
        position. Null if there is no piece that can move towards opponent's home position  

    AUTHOR

        Abhinav Thapaliya 

    DATE

        7/12/2019

*/
Piece *Board::getBestWhitePieceThatCanMoveAwayFromHomePos(std::vector<Piece*> aRowOfpieces, char playerColor, int &optimalDirectionToMoveThePieceIn, int rowNumber){
    Piece * toReturn = NULL;
    int maxHomePoints = 0;

    for(int i = 0; i < aRowOfpieces.size(); i++ ){
        Piece * onePiece = aRowOfpieces[i];

        int boardColumnNumberOfOnePiece = getColumnOfAPiece( onePiece ); 

        // For a white piece, away from opponents' position is towards north
        if( canMoveNortheast( rowNumber, boardColumnNumberOfOnePiece) ){
            int destinationCol = getNortheastCol( boardColumnNumberOfOnePiece );
            findDestinationColWithMaxPoints( destinationCol, maxHomePoints, toReturn, onePiece, optimalDirectionToMoveThePieceIn, MOVE_NORTHEAST );
        }

        if( canMoveNorthwest( rowNumber, boardColumnNumberOfOnePiece) ){
            int destinationCol = getNorthwestCol( boardColumnNumberOfOnePiece );
            findDestinationColWithMaxPoints( destinationCol, maxHomePoints, toReturn, onePiece, optimalDirectionToMoveThePieceIn, MOVE_NORTHWEST );
        }
    }

    return toReturn;
}


/**/
    /*
    getPiecesAlreadyInOpponentsHomePosition - Get a collection of pieces already in opponent's
    home position

    NAME

        getPiecesAlreadyInOpponentsHomePosition

    SYNOPSIS

        vector<Piece *> Board::getPiecesAlreadyInOpponentsHomePosition( vector<Piece *> pieces, char playerColor)

    DESCRIPTION
         
        For piece of Black color, opponent's home position is towards North. If the pieces have
        White color, opponent's home position is towards South         

    RETURNS

        A collection of reference to Piece objects        

    AUTHOR

        Abhinav Thapaliya 

    DATE

        7/16/2019

*/
vector<Piece *> Board::getPiecesAlreadyInOpponentsHomePosition( vector<Piece *> pieces, char playerColor){
    vector<Piece*> rowOfPieces; 

    if(pieces.size() == 0)
        return rowOfPieces;

    int maxRow = 0;
    int minRow = dimension - 1;

    if( playerColor == Piece::BLACK ){
        for(int i = 0; i < rowOfPieces.size(); i++){
            Piece * onePiece = rowOfPieces[i];

            int pieceRow = getRowOfAPiece( onePiece );
            int pieceCol = getColumnOfAPiece( onePiece );

            if( canMoveNortheast( pieceRow, pieceCol ) || canMoveNorthwest(pieceRow, pieceCol ) ){
                maxRow = pieceRow;
                break;
            }
        }

        rowOfPieces = getCertainPiecesFromARow( maxRow, playerColor );
    }

    if( playerColor == Piece::WHITE){
        for(int i = 0; i < rowOfPieces.size(); i++){
            Piece * onePiece = rowOfPieces[i];

            int pieceRow = getRowOfAPiece( onePiece );
            int pieceCol = getColumnOfAPiece( onePiece );

            if( canMoveSoutheast( pieceRow, pieceCol ) || canMoveSouthwest(pieceRow, pieceCol ) ){
                minRow = pieceRow;
                break;
            }
        }

        rowOfPieces = getCertainPiecesFromARow( minRow, playerColor);
    }

    return rowOfPieces;
}


/**/
    /*
    atLeastOnePieceExists - Check if there is at least one board piece whose color
    equals to the color specified in the parameter

    NAME

        atLeastOnePieceExists

    SYNOPSIS

        bool Board::atLeastOnePieceExists(char playerColor)

    DESCRIPTION
         
        Check if there is at least one board piece whose color equals to the 
        color specified in the parameter

    RETURNS

        True if there is at least one board piece whose color equals to the 
        color specified in the parameter. False otherwise 

    AUTHOR

        Abhinav Thapaliya 

    DATE

        7/16/2019

*/
bool Board::atLeastOnePieceExists(char playerColor){
    for(int row = 0; row < dimension; row++){
        for(int col = 0; col < dimension; col++){
            Piece * onePiece = gameBoard[row][col];

            if( onePiece != NULL){
                if( onePiece->getColor() == playerColor)
                    return true;
            }
        }
    }

    return false;
}


/**/
    /*
    canMoveAtLeastOnePieceLegitimately - Determine if the player playing the pieces of the color
    specified in the parameter, playerColor, can move at least one piece in a legitimate direction

    NAME

        canMoveAtLeastOnePieceLegitimately

    SYNOPSIS

        bool Board::canMoveAtLeastOnePieceLegitimately(char playerColor)

    DESCRIPTION
         
        Determine if the player playing the pieces of the color specified in the parameter,
        playerColor, can move at least one piece in a legitimate direction

    RETURNS

        True if the player can move at least one piece legitimately. False otherwise 

    AUTHOR

        Abhinav Thapaliya 

    DATE

        7/16/2019

*/
bool Board::canMoveAtLeastOnePieceLegitimately(char playerColor){
    for(int row = 0; row < dimension; row++ ){
        for(int col = 0; col < dimension; col++ ){
            Piece * onePiece = gameBoard[row][col];

            if( onePiece != NULL){
                if( onePiece->getColor() == playerColor ){
                    if( canMoveNortheast(row, col) || canMoveNorthwest(row, col) || canMoveSoutheast(row, col) || canMoveSouthwest(row, col) )
                        return true;
                }
            }
        }
    }

    return false;   
}


/**/
    /*
    getPiecesFromTheRowFarthestFromOpponentsHomePos - From a collection of reference to Piece objects,
    return a collection of reference to Piece objects that are in the row farthest from the opponent's 
    home position

    NAME

        getPiecesFromTheRowFarthestFromOpponentsHomePos

    SYNOPSIS

        vector<Piece *> Board::getPiecesFromTheRowFarthestFromOpponentsHomePos( vector<Piece * > pieces, char playerColor )

    DESCRIPTION
         
        For piece of Black color, away from opponent's home position is towards South. If the piece 
        have White color, away from opponent's home position is towards North

    RETURNS

        A vector of pointers referencing Piece objects

    AUTHOR

        Abhinav Thapaliya 

    DATE

        7/16/2019

*/
vector<Piece *> Board::getPiecesFromTheRowFarthestFromOpponentsHomePos( vector<Piece * > pieces, char playerColor ) {
    vector<Piece*> res;
    int maxRow = INT_MIN;
    int minRow = INT_MAX;
    int farthestRow;

    if( playerColor == Piece::BLACK ){
        for(int i = 0; i < pieces.size(); i++){
            Piece * onePiece = pieces[i];
            int pieceRow = getRowOfAPiece( onePiece );
            if( pieceRow < minRow){
                minRow = pieceRow;
            }
        }

        farthestRow = minRow;
    }
    else{
        for(int i = 0; i < pieces.size(); i++){
            Piece * onePiece = pieces[i];
            int pieceRow = getRowOfAPiece( onePiece );
            if( pieceRow > maxRow){
                maxRow = pieceRow;
            }
        }

        farthestRow = maxRow;
    }

    if( !(farthestRow == INT_MIN || farthestRow == INT_MAX ) )
        res = choosePiecesFromARow( pieces, farthestRow ); 

    return res;
}


/**/
    /*
    choosePiecesFromARow - Given a collection of references to Piece objects, return 
    a collection of references to Piece objects whose row (in the gameboard) equals
    to the row specified in the parameter 

    NAME

        choosePiecesFromARow

    SYNOPSIS

        vector<Piece *> Board::choosePiecesFromARow( vector<Piece *> pieces, int rowToChooseFrom)

    DESCRIPTION
         
        Given a collection of references to Piece objects, return 
        a collection of references to Piece objects whose row (in the gameboard) equals
        to the row specified in the parameter 

    RETURNS

        A vector of pointers referencing Piece objects

    AUTHOR

        Abhinav Thapaliya 

    DATE

        7/14/2019

*/
vector<Piece *> Board::choosePiecesFromARow( vector<Piece *> pieces, int rowToChooseFrom){
    vector <Piece *> res;

    for(int i = 0; i < pieces.size(); i++){
        Piece * onePiece = pieces[i];

        int row = getRowOfAPiece( onePiece );

        if( row == rowToChooseFrom )
            res.push_back( onePiece );
    }

    return res;
}


/**/
    /*
    getDirectionString -  Get a string represntation of direction based 
    on an integer representation of direction

    NAME

        getDirectionString

    SYNOPSIS

        string Board::getDirectionString(int direction)

    DESCRIPTION
         
        The integer representation of the directions is based on the symbolic
        constants defined in this class 

    RETURNS

        A string variable if the integer direction is legitimate. Return
        an empty string otherwise 

    AUTHOR

        Abhinav Thapaliya 

    DATE

        7/14/2019

*/
string Board::getDirectionString(int direction){
    string directionStr;

    switch (direction)
    {
    case MOVE_NORTHEAST:
        directionStr = "northeast";
        break;
    case MOVE_NORTHWEST:
        directionStr = "northwest";
        break;
    case MOVE_SOUTHEAST:
        directionStr = "southeast";
        break;
    case MOVE_SOUTHWEST:
        directionStr = "southwest";
        break;
    }

    return directionStr;
}