#include "Player.h"


/**/
    /*
    Player - Default constructor. Initialize the member variables

    NAME

        Player

    SYNOPSIS

        Player::Player()

    DESCRIPTION
        
        Initialize the member variables

    RETURNS

        None

    AUTHOR

        Abhinav Thapaliya 

    DATE

        7/3/2019

*/
Player::Player(){
    score = 0;
    color = ' ';
    quit = false;
    numCaptures = 0;    
    resetOptimalMove();
}


/**/
    /*
    updateScore - Mutator used to update the increase the player's score

    NAME

        updateScore

    SYNOPSIS

        void Player::updateScore(int scr)

    DESCRIPTION
        
        Increment a player's score by the value of the integer parameter

    RETURNS

        None

    AUTHOR

        Abhinav Thapaliya 

    DATE

        7/3/2019

*/
void Player::updateScore(int scr){
    this->score += scr;
}


/**/
    /*
    setScore - Mutator used to set the player's score

    NAME

        setScore

    SYNOPSIS

        void Player::setScore(int scr)

    DESCRIPTION
        
        Set a player's score with the value of the integer parameter

    RETURNS

        None

    AUTHOR

        Abhinav Thapaliya 

    DATE

        7/3/2019

*/
void Player::setScore(int scr){
    this->score = scr;
}


/**/
    /*
    setColor - Mutator used to set the player's Color

    NAME

        setColor

    SYNOPSIS

        void Player::setColor(int scr)

    DESCRIPTION
        
        Set a player's Color with the value of the char parameter

    RETURNS

        None

    AUTHOR

        Abhinav Thapaliya 

    DATE

        7/3/2019

*/
bool Player::setColor(char clr){
    if( !(clr == Piece::BLACK || clr == Piece::WHITE) )
        return false;

    this->color = clr;
    return true;
}


/**/
    /*
    setQuit - Mutator used to set the value of the member variable, quit

    NAME

        setQuit

    SYNOPSIS

        void Player::setQuit(bool quit)

    DESCRIPTION
        
        Set the value of the memeber variable, quit

    RETURNS

        None

    AUTHOR

        Abhinav Thapaliya 

    DATE

        7/3/2019

*/
void Player::setQuit(bool quit){
    this->quit = quit;
}


/**/
    /*
    incrementNumCaptures - Increment the value of the member variable, numCaptures

    NAME

        incrementNumCaptures

    SYNOPSIS

        void Player::incrementNumCaptures()

    DESCRIPTION
        
        Increment the value of the member variable, numCaptures by 1

    RETURNS

        None

    AUTHOR

        Abhinav Thapaliya 

    DATE

        7/3/2019

*/
void Player::incrementNumCaptures(){
    this->numCaptures++;
}


/**/
    /*
    getColorString - Get the string representation of the player's color

    NAME

        getColorString

    SYNOPSIS

        string Player::getColorString()

    DESCRIPTION
        
        If the player's color is black, the string representation is "black". 
        If the player's color is white, the string representation is "white" 

    RETURNS

        If the player's color is black, return "black". If it is white, return
        "white". Else return an empty string 

    AUTHOR

        Abhinav Thapaliya 

    DATE

        7/3/2019

*/
string Player::getColorString(){
    string colorString;

    switch ( this->getColor() )
    {
    case Piece::BLACK:
        colorString = "black";    
        break;
    
    case Piece::WHITE:
        colorString = "white";
        break;
    }

    return colorString;
}


/**/
    /*
    getPiecesThatCanCapture - Get a collection of pieces that
    have the ability to capture at least one opponent's piece in one move 

    NAME

        getPiecesThatCanCapture

    SYNOPSIS

        vector <Piece*> Player::getPiecesThatCanCapture( Board * gameBoard )

    DESCRIPTION
        
         Get a collection of pointers to Piece objects that
        have the ability to capture at least one opponent's piece in one move 

    RETURNS

        A collection of Piece object pointers 

    AUTHOR

        Abhinav Thapaliya 

    DATE

        7/3/2019

*/
vector <Piece*> Player::getPiecesThatCanCapture( Board * gameBoard ){
    vector<Piece*> result;

    vector <Piece*> ownPieces = gameBoard->getAllPiecesOfAColor( color );
    
    int numOwnPieces = ownPieces.size();

    for(int i = 0; i < numOwnPieces; i++){
        Piece * toCheck = ownPieces[i];

        if( gameBoard->canCaptureInOneMove( toCheck ) )
            result.push_back( toCheck ); 
    }

    return result;
}


/**/
    /*
    computeOptimalMove - Compute optimal move for the player move 

    NAME

        computeOptimalMove

    SYNOPSIS

        bool Player::computeOptimalMove( Board * gameBoard )

    DESCRIPTION
        
        Here is how an optimal move is computed:
            - See if the player can capture at least one of the opponent's piece.
            - If yes
                - See if the player can capture any "deadly" pieces. Deadly pieces 
                are opponent's pieces that can capture the player's own pieces.
                - If the player can't capture any deadly pieces, capture non deadly piece
                that belongs to the opponent player 
            - If no
                - The player can't capture any opponent's pieces 
                - If the player can move towards opponent's home position, do so.
                - If not, see if a player can move any piece 

    RETURNS

        True if the player can make moves. False otherwise  

    AUTHOR

        Abhinav Thapaliya 

    DATE

        7/3/2019

*/
bool Player::computeOptimalMove( Board * gameBoard ) {

    resetOptimalMove();

    // See if the player can capture 
    vector <Piece*> piecesThatCanCapture = getPiecesThatCanCapture( gameBoard );

    if (piecesThatCanCapture.size() > 0 ){

        vector <Piece*> piecesThatCanCaptureDeadlyPieces = getPiecesThatCanCaptureDeadlyPieces( piecesThatCanCapture, gameBoard );
        
        if( piecesThatCanCaptureDeadlyPieces.size() > 0 ){
            // getBestPiece will set optimalDirectionToMoveThePieceIn as well
            // You may need to change the line below
            optimalPieceToMove = getBestPieceThatCanCaptureDeadlyPieces( piecesThatCanCaptureDeadlyPieces, gameBoard );
        }
        else{
            // getBestPiece will set optimalDirectionToMoveThePieceIn as well
            // You may need to change the line below 
            optimalPieceToMove = getBestPieceThatCanCaptureNonDeadlyPieces( piecesThatCanCapture, gameBoard );
        }
         
    }
    else{   // The player can't capture any pieces

        vector<Piece *> allPiecesThatBelongToThePlayer = gameBoard->getAllPiecesOfAColor( this->color );
        optimalPieceToMove = getBestPieceThatCantCapture( allPiecesThatBelongToThePlayer, gameBoard );
    }

    if( optimalPieceToMove == NULL || optimalDirectionToMoveThePieceIn == INVALID_INPUT )
        return false;

    return true;
}


/**/
    /*
    getPiecesThatCanCaptureDeadlyPieces - Get a collection of pieces that can capture opponent's
    deadly pieces 

    NAME

        getPiecesThatCanCaptureDeadlyPieces

    SYNOPSIS

        vector<Piece*> Player::getPiecesThatCanCaptureDeadlyPieces( vector<Piece*> pieces, Board * gameBoard )

    DESCRIPTION
        
        Deadly pieces are opponent's pieces that can capture the player's own pieces.

    RETURNS

        True if the player can make moves. False otherwise  

    AUTHOR

        Abhinav Thapaliya 

    DATE

        7/3/2019

*/
vector<Piece*> Player::getPiecesThatCanCaptureDeadlyPieces( vector<Piece*> pieces, Board * gameBoard ){
    vector<Piece *> result;

    for(int i = 0; i < pieces.size(); i++){
        Piece * onePiece = pieces[i];

        if( gameBoard->canCaptureDeadlyPieceInOneMove( onePiece ) )
            result.push_back( onePiece );
    }

    return result;
}


/**/
    /*
    getBestPieceThatCantCapture - Get the "best" piece that can't capture opponent's piece.

    NAME

        getBestPieceThatCantCapture

    SYNOPSIS

        Piece *Player::getBestPieceThatCantCapture(std::vector<Piece *> pieces, Board *gameBoard)
        
    DESCRIPTION
        
        See if there are pieces pieces that can move to opponent's home position in one move.
        If yes:
            - Select a piece that can move to opponent's most valuable home position
        Else:
            - See if there are pieces that can move in the direction towards opponent's home
            position. For Black pieces, opponent's home position is towards north while for
            white pieces, opponent's home position is towards south.
            - If yes:
                - Select the piece that can move towards the most valuable column.
            - Else:
                - See if the player has pieces that can move
                If yes:
                    - Select the piece that can move towards the most valuable column.

    RETURNS

        A pointer to a piece object if there is a piece that can be moved legitimately 
        in a direction. Return null otherwise    

    AUTHOR

        Abhinav Thapaliya 

    DATE

        7/15/2019

*/
Piece *Player::getBestPieceThatCantCapture(std::vector<Piece *> pieces, Board *gameBoard){

    Piece * bestPiece = NULL;

    if( pieces.empty() ){
        optimalDirectionToMoveThePieceIn = INVALID_INPUT;
        return NULL;
    }

    // See if you have pieces that can move to home positions in one move
    vector<Piece*> oneMoveAwayFromHomePosition = gameBoard->getPiecesThatCanMoveToHomePointInOneMove( this->color ); 

    if( oneMoveAwayFromHomePosition.size() > 0 ){
        bestPiece = getPieceThatCanGoToMostValuableHomePoint( oneMoveAwayFromHomePosition, gameBoard );

        // The function, getPieceThatCanGoToMostValuableHomePoint will set the direction to which
        // the bestPiece needs to be moved
    }
    else{

        vector<Piece *> bestPiecesRowWise = getBestPiecesRowWise( pieces, gameBoard );

        if( bestPiecesRowWise.size() > 0){
            bestPiece = getBestPieceColumnWise( bestPiecesRowWise, gameBoard );
            // getBestPieceColumnWise will set the optimalDirectionToMoveThePieceIn 
        }
        else
            optimalDirectionToMoveThePieceIn = INVALID_INPUT;
    }

    return bestPiece;
}


/**/
    /*
    resetOptimalMove - Reset the optimal move to piece and optimal move direction the
    player is supposed to move in 

    NAME

        resetOptimalMove

    SYNOPSIS

        void Player::resetOptimalMove()

    DESCRIPTION
        
        Reset the optimal move to piece and optimal move direction the player is supposed
        to move in 

    RETURNS

        None  

    AUTHOR

        Abhinav Thapaliya 

    DATE

        7/7/2019

*/
void Player::resetOptimalMove(){
    optimalPieceToMove = NULL;
    optimalDirectionToMoveThePieceIn = INVALID_INPUT;
}


/**/
    /*
    getPieceThatCanGoToMostValuableHomePoint - Compute the player's piece that can go to the 
    most valuable home point that belongs to the opponent

    NAME

        getPieceThatCanGoToMostValuableHomePoint

    SYNOPSIS

        Piece *Player::getPieceThatCanGoToMostValuableHomePoint( vector<Piece *> pieces, Board *gameBoard)

    DESCRIPTION
        
        Reaching some home points will yield higher score for the player than reaching others. This function
        returns a Piece that can move to the most valuable home point, the home point that will 
        yield the highest amount of point for the player  

    RETURNS

        A pointer to a Piece object  

    AUTHOR

        Abhinav Thapaliya 

    DATE

        7/3/2019

*/
Piece *Player::getPieceThatCanGoToMostValuableHomePoint( vector<Piece *> pieces, Board *gameBoard){
    Piece * result = NULL;
    int globalMoveDirection = INVALID_INPUT;
    int globalMaxPoints = 0;

    for( int i = 0; i < pieces.size(); i++ ){
        Piece * onePiece = pieces[i];

        int localMoveDirection = INVALID_INPUT;
        int localMaxPoint = 0;

        int pieceRow = gameBoard->getRowOfAPiece( onePiece );
        int pieceCol = gameBoard->getColumnOfAPiece( onePiece );

        int northeastRow = gameBoard->getNortheastRow( pieceRow );
        int northeastCol = gameBoard->getNortheastCol( pieceCol );

        int northwestRow = gameBoard->getNorthwestRow( pieceRow );
        int northwestCol = gameBoard->getNorthwestCol( pieceCol );

        int southeastRow = gameBoard->getSoutheastRow( pieceRow );
        int southeastCol = gameBoard->getSoutheastCol( pieceCol );

        int southwestRow = gameBoard->getSouthwestRow( pieceRow );
        int southwestCol = gameBoard->getSouthwestCol( pieceCol );

        computeMostValuableHomePieceOccupant( localMaxPoint, localMoveDirection, northeastRow, northeastCol, MOVE_NORTHEAST, onePiece, gameBoard );
        computeMostValuableHomePieceOccupant( localMaxPoint, localMoveDirection, northwestRow, northwestCol, MOVE_NORTHWEST, onePiece, gameBoard );
        computeMostValuableHomePieceOccupant( localMaxPoint, localMoveDirection, southeastRow, southeastCol, MOVE_SOUTHEAST, onePiece, gameBoard );
        computeMostValuableHomePieceOccupant( localMaxPoint, localMoveDirection, southwestRow, southwestCol, MOVE_SOUTHWEST, onePiece, gameBoard );          

        if( localMaxPoint > globalMaxPoints ){
            globalMaxPoints = localMaxPoint;
            globalMoveDirection = localMoveDirection;
            result = onePiece;
        }
    }

    optimalDirectionToMoveThePieceIn = globalMoveDirection;
    return result;
}


/**/
    /*
    computeMostValuableHomePieceOccupant - A helper function to getPieceThatCanGoToMostValuableHomePoint

    NAME

        computeMostValuableHomePieceOccupant

    SYNOPSIS

        void Player::computeMostValuableHomePieceOccupant(int &localMaxPoint, int &localMoveDirection, int rowInDirectionSpecified, int colInDirectionSpecified, int directionType, Piece * piece, Board * gameBoard )

    DESCRIPTION
        
        The variables, localMaxPoint and localMoveDirection are passed by reference because their value is 
        used by the caller function 

    RETURNS

        None   

    AUTHOR

        Abhinav Thapaliya 

    DATE

        7/3/2019

*/
void Player::computeMostValuableHomePieceOccupant(int &localMaxPoint, int &localMoveDirection, int rowInDirectionSpecified, int colInDirectionSpecified, int directionType, Piece * piece, Board * gameBoard ){
    // Find out if the rowInDirectionSpecified and colInDirectionSpecified is a home position
    bool canReachHomePosition = gameBoard->canReachHomePointInOneMove( piece, rowInDirectionSpecified, colInDirectionSpecified );

    if(!canReachHomePosition )
        return;
    
    int pointsForReachingHomePosition = gameBoard->getPointForReachingAHomePosition( rowInDirectionSpecified, colInDirectionSpecified, piece->getColor() ); 

    if( pointsForReachingHomePosition > localMaxPoint ){
        localMaxPoint = pointsForReachingHomePosition;
        localMoveDirection = directionType;
    } 
}


/**/
    /*
    getBestPiecesRowWise - Given a collection of Piece object pointers, return a collection
    of pointers to Piece objects that are in the "best" row.

    NAME

        getBestPiecesRowWise

    SYNOPSIS

        vector<Piece *> Player::getBestPiecesRowWise(vector<Piece *> pieces, Board *gameBoard)

    DESCRIPTION
        
        - If the pieces are not in home position, the best pieces are in the row closest to the 
        home position
        - If the pieces are already in home position, the best pieces are the pieces that are
        either in the 2nd row (if the player's color is Black) or in the 2nd last row (if the 
        player's color is white)

    RETURNS

        A collection of pointers to Piece objects 

    AUTHOR

        Abhinav Thapaliya 

    DATE

        7/7/2019

*/
vector<Piece *> Player::getBestPiecesRowWise(vector<Piece *> pieces, Board *gameBoard){
    vector<Piece*> result; 

    if( pieces.size() > 0) {
        // First, try to get pieces that can move towards the home positions (south or north depending on the playerColor  )
        result = gameBoard->getPiecesThatCanMoveTowardsHomePosition( pieces, this->color );

        if( result.size() == 0 ){
            result = gameBoard->getPiecesAlreadyInOpponentsHomePosition( pieces, this->color );
        }  
    }

    return result;
}


/**/
    /*
    getBestPieceColumnWise - Given a collection of pieces that belong to the same row 
    in the game board, compute the piece that can move towards the most valuable column

    NAME

        getBestPieceColumnWise

    SYNOPSIS

        Piece *Player::getBestPieceColumnWise(std::vector<Piece *> aRowOfpieces, Board *gameBoard)

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

        None   

    AUTHOR

        Abhinav Thapaliya 

    DATE

        7/13/2019

*/
Piece *Player::getBestPieceColumnWise(std::vector<Piece *> aRowOfpieces, Board *gameBoard){
    // All pieces in aRowOfPieces belong to the same row in gameBoard
     if(aRowOfpieces.size() == 0)
        return NULL;

    int rowNumber = gameBoard->getRowOfAPiece( aRowOfpieces[0] );

    Piece * bestPieceThatCanMoveTowardsHomePos = gameBoard->getBestPieceThatCanMoveTowardsHomePos( aRowOfpieces, this->color, optimalDirectionToMoveThePieceIn ); 

    return bestPieceThatCanMoveTowardsHomePos;
}


/**/
    /*
    getBestPieceThatCanCaptureDeadlyPieces - Get a piece that can capture opponent's deadly piece

    NAME

        getBestPieceThatCanCaptureDeadlyPieces

    SYNOPSIS

        Piece *Player::getBestPieceThatCanCaptureDeadlyPieces(std::vector<Piece*> piecesThatCanCaptureDeadlyPieces, Board *gameBoard

    DESCRIPTION
        
        Deadly pieces are opponent's pieces that can capture the player's own pieces.

    RETURNS

        A pointer to a piece object   

    AUTHOR

        Abhinav Thapaliya 

    DATE

        7/13/2019

*/
Piece *Player::getBestPieceThatCanCaptureDeadlyPieces(std::vector<Piece*> piecesThatCanCaptureDeadlyPieces, Board *gameBoard){
    if( piecesThatCanCaptureDeadlyPieces.size() == 0){
        optimalDirectionToMoveThePieceIn = INVALID_INPUT;
        return NULL;
    }

    Piece * toReturn = piecesThatCanCaptureDeadlyPieces[0];
    int pieceRow = gameBoard->getRowOfAPiece( toReturn );
    int pieceCol = gameBoard->getColumnOfAPiece( toReturn );

    int northeastRow = gameBoard->getNortheastRow( pieceRow );
    int northeastCol = gameBoard->getNortheastCol( pieceCol );

    if( gameBoard->isDeadlyPiece( toReturn, northeastRow, northeastCol ) ){
        optimalDirectionToMoveThePieceIn = MOVE_NORTHEAST;
        return toReturn;
    }

    int northwestRow = gameBoard->getNorthwestRow( pieceRow );
    int northwestCol = gameBoard->getNortheastCol( pieceCol );

    if( gameBoard->isDeadlyPiece( toReturn, northwestRow, northwestCol )){
        optimalDirectionToMoveThePieceIn = MOVE_NORTHWEST;
        return toReturn;
    }

    int southeastRow = gameBoard->getSoutheastRow( pieceRow );
    int southeastCol = gameBoard->getSoutheastCol( pieceCol );

    if( gameBoard->isDeadlyPiece( toReturn, southeastRow, southeastCol )){
        optimalDirectionToMoveThePieceIn = MOVE_SOUTHEAST;
        return toReturn;
    }

    int southwestRow = gameBoard->getSouthwestRow(pieceRow);
    int southwestCol = gameBoard->getSouthwestCol( pieceCol);

    if( gameBoard->isDeadlyPiece( toReturn, southwestRow, southwestCol ) ){
        optimalDirectionToMoveThePieceIn = MOVE_SOUTHWEST;
        return toReturn;
    }

    return NULL;
}


/**/
    /*
    getBestPieceThatCanCaptureNonDeadlyPieces - Get a collection of pieces that can capture 
    opponent's piece that is not a deadly piece 

    NAME

        getBestPieceThatCanCaptureNonDeadlyPieces

    SYNOPSIS

        Piece *Player::getBestPieceThatCanCaptureNonDeadlyPieces( vector<Piece *> piecesThatCanCapture, Board *gameBoard )
        
    DESCRIPTION
        
        Deadly pieces are opponent's pieces that can capture the player's own pieces. this function
        tries to capture opponent's pieces that are closer to the player's own position. This makes
        sense because if an opponent's piece reaches the player's home position, the opponent's piece
        will have an ability to capture player's piece. This is risky. So, the player can counterattack
        and capture the opponent's piece instead so that the piece can't reach the player's home
        position

    RETURNS

        A pointer to a piece object   

    AUTHOR

        Abhinav Thapaliya 

    DATE

        7/13/2019

*/
Piece *Player::getBestPieceThatCanCaptureNonDeadlyPieces( vector<Piece *> piecesThatCanCapture, Board *gameBoard ){

    Piece * bestPiece = NULL;

    if( piecesThatCanCapture.empty() ){
        optimalDirectionToMoveThePieceIn = INVALID_INPUT;
        return NULL;
    }

    vector<Piece*> bestPiecesRowWise = gameBoard->getPiecesFromTheRowFarthestFromOpponentsHomePos( piecesThatCanCapture, this->color );

    bestPiece = getBestCapturePieceColumnWise( bestPiecesRowWise, gameBoard );    

    return bestPiece;
}


/**/
    /*
    getBestCapturePieceColumnWise - Get the "best" piece that can capture opponent's non deadly piece.

    NAME

        getBestCapturePieceColumnWise

    SYNOPSIS

        Piece *Player::getBestCapturePieceColumnWise(std::vector<Piece *> pieces, Board *gameBoard)
        
    DESCRIPTION
        
        Deadly pieces are opponent's pieces that can capture the player's own pieces. The best piece 
        is the first piece in the vector (in the parameter passed) that can capture any opponent's
        non-deadly piece 

    RETURNS

        A pointer to a piece object   

    AUTHOR

        Abhinav Thapaliya 

    DATE

        7/13/2019

*/
Piece *Player::getBestCapturePieceColumnWise(std::vector<Piece *> pieces, Board *gameBoard){
    Piece * bestPiece = NULL;

    for(int i = 0; i < pieces.size(); i++){
        Piece * onePiece = pieces[i];
        int pieceRow = gameBoard->getRowOfAPiece( onePiece );
        int pieceCol = gameBoard->getColumnOfAPiece( onePiece );

        if( gameBoard->checkCapture( onePiece, gameBoard->getNortheastRow( pieceRow ), gameBoard->getNortheastCol( pieceCol ) ) ){
            optimalDirectionToMoveThePieceIn = MOVE_NORTHEAST;
            return onePiece;
        }
        else if( gameBoard->checkCapture( onePiece, gameBoard->getNorthwestRow(pieceRow), gameBoard->getNorthwestCol(pieceCol ) ) ){
            optimalDirectionToMoveThePieceIn = MOVE_NORTHWEST;
            return onePiece;
        }
        else if( gameBoard->checkCapture( onePiece, gameBoard->getSoutheastRow(pieceRow), gameBoard->getSoutheastCol(pieceCol ) ) ){
            optimalDirectionToMoveThePieceIn = MOVE_SOUTHEAST;
            return onePiece;
        }
        else if( gameBoard->checkCapture( onePiece, gameBoard->getSouthwestRow(pieceRow), gameBoard->getSouthwestCol(pieceCol ) ) ){
            optimalDirectionToMoveThePieceIn = MOVE_SOUTHWEST;
            return onePiece;
        }
    }

    return bestPiece;
}