#include "Game.h"

// Game count is a static variable because this variable needs to exist
// even when a game is over and another game starts. The scope of this variable
// is not just a game, but the entire championship
int Game::gameCount = 1;

// If turn is true, it is computer's turn. Else, it is human's turn
bool Game::turn = false; 

string Game::previousGameWinner = ""; 

/**/
    /*
    Game - Custom construtor 1

    NAME

        Game

    SYNOPSIS

        Game::Game( int boardDimension, int championshipScoreHuman, int championshipScoreComputer )

    DESCRIPTION
        
        Executed when a new game is started 

    RETURNS

        None

    AUTHOR

        Abhinav Thapaliya 

    DATE

        7/1/2019

*/
Game::Game( int boardDimension, int championshipScoreHuman, int championshipScoreComputer ){
    // The board dimension, 5 in this case, should actually be determined in the championship class
    // either by asking the user for a dimension or by reading the dimension from the file used to load the game 
    gameBoard = new Board( boardDimension );
    computerPlayer = new Computer();
    humanPlayer = new Human();
    moveSummary = "";
    aPlayerQuitGame = false;
    this->championshipScoreHuman = championshipScoreHuman;
    this->championshipScoreComputer = championshipScoreComputer;
    setUpGame(); // Maybe move this to playAGame 
}


/**/
    /*
    Game - Custom construtor 2. Load a game based on the state reflected by the values passed in
    the parameters. 

    NAME

        Game

    SYNOPSIS

        Game::Game( int boardDimension, int championshipScoreHuman, int championshipScoreComputer )

    DESCRIPTION
        
        Executed when a game is loaded.

    RETURNS

        None

    AUTHOR

        Abhinav Thapaliya 

    DATE

        7/1/2019

*/
Game::Game(Board * board, Computer *compPlayer, Human *humanPlayer, int gameCount, string nextPlayer, int championshipScoreHuman, int championshipScoreComputer ){
    gameBoard = board;
    this->computerPlayer = compPlayer; 
    this->humanPlayer = humanPlayer;
    this->gameCount = gameCount;
    this->turn = nextPlayer == "Computer"? true: false;
    this->championshipScoreHuman = championshipScoreHuman;
    this->championshipScoreComputer = championshipScoreComputer;
    previousGameWinner = "none";
    moveSummary = "";
    aPlayerQuitGame = false;
    setUpGame( true );
}

/**/
    /*
    setUpGame - Set up a game 

    NAME

        rollADieOnce

    SYNOPSIS

        void Game::setUpGame( bool gameLoaded = false  )

    DESCRIPTION
        
        Set the first player for the game. Let the first player select color. Then
        start the game

    RETURNS

        None

    AUTHOR

        Abhinav Thapaliya 

    DATE

        7/1/2019

*/
void Game::setUpGame( bool gameLoaded /* = false */ ){

    if( !gameLoaded ){
        if( gameCount == 0 || previousGameWinner == "")
            rollDices();

        cout << "\n--Start of new game--------------------------\n";
        assignColor();
        summarizeColorSelection();
    }

    playAGame();
}


/**/
    /*
    getCurrentPlayer - Get reference to the player whose turn it is to make moves

    NAME

        getCurrentPlayer

    SYNOPSIS

        Player *Game::getCurrentPlayer()

    DESCRIPTION
        
        Get a reference to the computer player if it is Computer's turn to make moves.
        Else get a reference to the human player 

    RETURNS

        a Player pointer 

    AUTHOR

        Abhinav Thapaliya 

    DATE

        7/1/2019

*/
Player *Game::getCurrentPlayer(){
    if( turn)
        return computerPlayer;
    
    return humanPlayer;
}


/**/
    /*
    rollDices - Make the two players roll dices to determine who plays first

    NAME

        rollDices

    SYNOPSIS

        void Game::rollDices()

    DESCRIPTION
        
        The point of this function is to determine the first player for the first game 
        of the championship

    RETURNS

        None 

    AUTHOR

        Abhinav Thapaliya 

    DATE

        7/1/2019

*/
void Game::rollDices() {
    bool rollDicesAgain = false;
    
    do{
        cout << "\n ******************************************************\n";

        int sumOfDiceHumanPlayer = rollDiceOneRound( humanPlayer );
        int sumOfDiceComputerPlayer = rollDiceOneRound( computerPlayer );

        summarizeDiceThrow( sumOfDiceHumanPlayer, sumOfDiceComputerPlayer );

        rollDicesAgain = sumOfDiceHumanPlayer == sumOfDiceComputerPlayer? true: false;

        cout << "\n ******************************************************\n";
    } while( rollDicesAgain );
}


/**/
    /*
    assignColor - Make the first player of the game select color for the game 

    NAME

        assignColor

    SYNOPSIS

        void Game::assignColor()

    DESCRIPTION
        
        The first player gets to select the color for the game. The other player
        selects the color the first player did not select

    RETURNS

        None 

    AUTHOR

        Abhinav Thapaliya 

    DATE

        7/1/2019

*/
void Game::assignColor(){

    
    Player * currentPlayer = getCurrentPlayer();

    char firstPlayerColor = currentPlayer->selectColor();
    currentPlayer->setColor( firstPlayerColor );

    char secondPlayerColor = firstPlayerColor == Piece::BLACK? Piece::WHITE: Piece::BLACK;
    getOpponentPlayer( currentPlayer )->setColor( secondPlayerColor );
}


/**/
    /*
    summarizeColorSelection - Summarize the colors the players chose to select

    NAME

        summarizeColorSelection

    SYNOPSIS

        void Game::summarizeColorSelection()

    DESCRIPTION
        
        Summarize the colors the players chose to select

    RETURNS

        None 

    AUTHOR

        Abhinav Thapaliya 

    DATE

        7/1/2019

*/
void Game::summarizeColorSelection(){
    Player * currentPlayer = getCurrentPlayer();
    Player * opponent = getOpponentPlayer( getCurrentPlayer() );

    string currentPlayerColor = currentPlayer->getColor() == Piece::BLACK? "black" : "white";
    string opponentPlayerColor = opponent->getColor() == Piece::BLACK? "black" : "white";

    cout << "\n\nThe " << currentPlayer->getPlayerType() << " player will be playing " << currentPlayerColor
        << " pieces\n";
    cout << "The " << opponent->getPlayerType() << " player will be playing " << opponentPlayerColor
        << " pieces. \n"; 
}


/**/
    /*
    getOpponentPlayer - Given a player, get the reference to the player's opponent

    NAME

        getOpponentPlayer

    SYNOPSIS

        Player *Game::getOpponentPlayer(Player * player)

    DESCRIPTION
        
        If the parameter passed is a reference to the computer player, return reference to the human
        player. Else return reference to the computer player

    RETURNS

        A player pointer  

    AUTHOR

        Abhinav Thapaliya 

    DATE

        7/1/2019

*/
Player *Game::getOpponentPlayer(Player * player){
    if(player == computerPlayer)
        return humanPlayer;
    return computerPlayer;
}


/**/
    /*
    rollDiceOneRound - Make the player throw a pair of dices and return the sum of dice throws

    NAME

        rollDiceOneRound

    SYNOPSIS

        int Game::rollDiceOneRound( Player * player )

    DESCRIPTION
        
        Return the combination of dice throws for a turn of dice throws 

    RETURNS

        An integer value between 7 and 12 

    AUTHOR

        Abhinav Thapaliya 

    DATE

        7/1/2019

*/
int Game::rollDiceOneRound( Player * player ){
    int sumOfDice = 0;

    for(int i = 0; i < 2; i++ ){
        int rolledDie = player->rollADieOnce();
        cout << "The " << player->getPlayerType() << " player got " << rolledDie << " when they rolled a die \n";

        sumOfDice += rolledDie;
    }
    cout << "\n ------------------------------------------------------\n";
    
    return sumOfDice;
}


/**/
    /*
    summarizeDiceThrow - Summarize the sum of players' dice throws 

    NAME

        summarizeDiceThrow

    SYNOPSIS

        void Game::summarizeDiceThrow(int sumOfDiceHumanPlayer, int sumOfDiceComputerPlayer)

    DESCRIPTION
        
        Print the the sum of players' dice throws and set the first player depending
        on what player has the greater sum of dice

    RETURNS

        None 

    AUTHOR

        Abhinav Thapaliya 

    DATE

        7/1/2019

*/
void Game::summarizeDiceThrow(int sumOfDiceHumanPlayer, int sumOfDiceComputerPlayer){
    cout << "\nThe sum of dice throws for the human player is " << sumOfDiceHumanPlayer << endl;
    cout << "The sum of dice throws for the computer player is " << sumOfDiceComputerPlayer << endl;

    string diceThrowWinner;

    if( sumOfDiceHumanPlayer == sumOfDiceComputerPlayer ){
        cout << "Since the sum of dice throws for both players is equal, the first player could not be determined\n";
        cout << "\nRepeating the dice throw process again...............\n";
        return;
    }
    else if (sumOfDiceHumanPlayer > sumOfDiceComputerPlayer ){
        diceThrowWinner = humanPlayer->getPlayerType();
        turn = false;
    }
    else{
        diceThrowWinner = computerPlayer->getPlayerType();
        turn = true; 
    }

    cout << "Since the " << diceThrowWinner << " player has greater sum of dice, the " << diceThrowWinner 
    << " player won the toss and will be playing first. " << endl; 
}


/**/
    /*
    playAGame - Play an entire game 

    NAME

        playAGame

    SYNOPSIS

        void Game::playAGame()

    DESCRIPTION
        
        Play an entire game from a player making the first move to ending the game 

    RETURNS

        None 

    AUTHOR

        Abhinav Thapaliya 

    DATE

        7/1/2019

*/
void Game::playAGame(){
    // Play a turn. firstPlayer plays the turn first followed by the second player
    while( !gameOver() ){
        playATurn( getCurrentPlayer() );
    }

    // At this point, the round is over. Time to update players' score.
    endGame();
}


/**/
    /*
    playATurn - Allow a player to play a turn 

    NAME

        playATurn

    SYNOPSIS

        void Game::playATurn( Player *player )

    DESCRIPTION
        
        Play a turn for a player 

    RETURNS

        None 

    AUTHOR

        Abhinav Thapaliya 

    DATE

        7/1/2019

*/
void Game::playATurn( Player *player ){
    cout << "\n---------------------------------------------------------------------------------\n";
    cout << "\nIt is " << player->getPlayerType() << " player's turn \n";
    cout << "The " << player->getPlayerType() << " is playing " << player->getColorString() << endl;
    gameBoard->print();

    int gameOption;

    do{
        player->showGameOptions();
        gameOption = player->getGameOption( gameBoard );

        // Write code below to implement help feature
        if( !turn && gameOption == Human::GAME_OPTION_HELP )
            askForHelp( player );

        // Write code here to implement save game feature
        if( gameOption == Player::GAME_OPTION_SAVE_GAME )
            saveGame();

    } while( !(gameOption == Player::GAME_OPTION_MAKE_MOVE || gameOption == player->getGameOptionForQuitGame() ));

    if( gameOption == Player::GAME_OPTION_MAKE_MOVE )
        makeMove( player );
    else{
        quitGame( player );  // Need to end the game properly when quitting the game
    }
}


/**/
    /*
    makeMove - Allow a player to make move during their turn 

    NAME

        makeMove

    SYNOPSIS

        void Game::makeMove(Player *player)

    DESCRIPTION
        
        Allow a player to make move during their turn and print move summary 

    RETURNS

        None 

    AUTHOR

        Abhinav Thapaliya 

    DATE

        7/1/2019

*/
void Game::makeMove(Player *player){
    moveSummary = "";
    cout << "\n The " << player->getPlayerType() << " player chose to make a move \n";
    gameBoard->print();

    int originRow = player->getRowForABoardPiece( gameBoard->getDimension(), gameBoard );
    int originCol = player->getColumnForABoardPiece( gameBoard->getDimension(), gameBoard );

    Piece * pieceUserSelected = gameBoard->getPiece( originRow, originCol );

    if( pieceUserSelected == NULL ){
        cout << "Invalid piece selection. You tried to select a piece that is not in the board.\n";
        cout << "Please try again \n";
        return;
    } 

    if( pieceUserSelected->getColor() != player->getColor() ){
        cout << "\nYou can't move a piece that does not belong to you. Please select a piece that belongs to you\n";
        cout << "(same color) you were assigned to at the start of the game \n";
        return;
    }

    int moveDirection = player->getMoveDirection();

    if ( verifyMove( moveDirection, pieceUserSelected, originRow, originCol, player ) ){
        turn = !turn;
        cout << moveSummary << endl;
    }

    gameBoard->print();

    // Pause the screen so that the player can read and comprehend move the player just made
    cout << "-----------Press enter to continue------------- \n";
    cin.ignore();
}   


/**/
    /*
    verifyMove - Verify the move the player decided to make 

    NAME

        verifyMove

    SYNOPSIS

        bool Game::verifyMove(int moveDirection, Piece * pieceUserSelected, int originRow, int originCol, Player * player )

    DESCRIPTION
        
        Verify that the player selected a valid piece to move in a valid direction

    RETURNS

        true if the player made valid move. false otherwise  

    AUTHOR

        Abhinav Thapaliya 

    DATE

        7/1/2019

*/
bool Game::verifyMove(int moveDirection, Piece * pieceUserSelected, int originRow, int originCol, Player * player ){
    bool validMoveNortheast = false,
        validMoveNorthwest = false,
        validMoveSoutheast = false,
        validMoveSouthwest = false,
        capturedAPiece = false; // This variable is passed by reference to move functions below. May be modified
                                // because of side effect

    updateMoveSummaryWithRowAndColDescription( player, originRow, originCol );

    switch( moveDirection ){
        case Player::MOVE_NORTHEAST: 
            validMoveNortheast = gameBoard->moveNorthEast( pieceUserSelected, originRow, originCol, capturedAPiece );
            moveSummary += " northeast. \n";
            break;
        case Player::MOVE_NORTHWEST:
            validMoveNorthwest = gameBoard->moveNorthWest( pieceUserSelected, originRow, originCol, capturedAPiece );
            moveSummary += " northwest. \n";
            break;
        case Player::MOVE_SOUTHEAST:
            validMoveSoutheast = gameBoard->moveSouthEast( pieceUserSelected, originRow, originCol, capturedAPiece );
             moveSummary += " southeast. \n";
            break;
        case Player::MOVE_SOUTHWEST:
            validMoveSouthwest = gameBoard->moveSouthWest( pieceUserSelected, originRow, originCol, capturedAPiece );
            moveSummary += " southwest. \n";
            break;
    }

    if( !(validMoveNortheast || validMoveNorthwest || validMoveSoutheast || validMoveSouthwest ) ){
        cout << "\n Invalid selection of move direction. You are not permitted\n";
        cout << "to move the piece you selected in the direction you chose \n";
        cout << "Please try again...\n";
        moveSummary = "";    
    }

    if( capturedAPiece )
        player->incrementNumCaptures();

    return validMoveNortheast || validMoveNorthwest || validMoveSoutheast || validMoveSouthwest;
}


/**/
    /*
    updateMoveSummaryWithRowAndColDescription - Let the user know the exact row and column the player 
    making moves decided to place his moved piece in 

    NAME

        updateMoveSummaryWithRowAndColDescription

    SYNOPSIS

        void Game::updateMoveSummaryWithRowAndColDescription( Player * player, int originRow, int originCol )

    DESCRIPTION
        
        Let the user know the exact row and column the player making moves decided to place his moved piece in 

    RETURNS

        None   

    AUTHOR

        Abhinav Thapaliya 

    DATE

        7/1/2019

*/
void Game::updateMoveSummaryWithRowAndColDescription( Player * player, int originRow, int originCol ){
    moveSummary += "\nThe " + player->getPlayerType() + " chose to move the piece at row, ";
    moveSummary += to_string(originRow + 1);
    moveSummary += " and column, ";
    moveSummary += to_string(originCol + 1);
}


/**/
    /*
    gameOver - Check if the game is over 

    NAME

        gameOver

    SYNOPSIS

        bool Game::gameOver()

    DESCRIPTION
        
        The game ends when one of the following conditions are satisfied:
            - a player explicitly decides to quit the game.
            - a player reaches all of his opponent's home positions in the game board
            - one of the players has 0 pieces (that belongs to him)
            - one of the players can't move a piece anywhere in the board 

    RETURNS

        True if the game is over. false otherwise   

    AUTHOR

        Abhinav Thapaliya 

    DATE

        7/1/2019

*/
bool Game::gameOver(){
    if( aPlayerQuitGame )
        return true;

    if( gameBoard->hasReachedAllHomePoints( humanPlayer->getColor() ) || gameBoard->hasReachedAllHomePoints( computerPlayer->getColor() ) ) 
        return true;

    if( !(gameBoard->atLeastOnePieceExists( humanPlayer->getColor() ) && gameBoard->atLeastOnePieceExists( computerPlayer->getColor() ) ) )
        return true;

    if( !(gameBoard->canMoveAtLeastOnePieceLegitimately(humanPlayer->getColor() ) || gameBoard->canMoveAtLeastOnePieceLegitimately( computerPlayer->getColor() ) )  )
        return true;

    return false;
}


/**/
    /*
    endGame - End the game properly 

    NAME

        endGame

    SYNOPSIS

        void Game::endGame()

    DESCRIPTION
        
        Compute points for both players, determine and announce the winner and increase 
        the gameCount at the end 

    RETURNS

        None 

    AUTHOR

        Abhinav Thapaliya 

    DATE

        7/3/2019

*/
void Game::endGame(){
    cout << "**************************GAME OVER **************************\n";

    int humanPlayerPoints = computePoints( humanPlayer );
    int computerPlayerPoints = computePoints( computerPlayer );
    
    humanPlayer->setScore( humanPlayerPoints );
    computerPlayer->setScore( computerPlayerPoints );

    determineWinner();
    gameCount++;
}


/**/
    /*
    quitGame - Gets executed when one of the player choose to quit the game while playing
        their turns

    NAME

        quitGame

    SYNOPSIS

        void Game::quitGame(Player * player)

    DESCRIPTION
        
        Gets executed when one of the player choose to quit the game while playing
        their turns

    RETURNS

        None 

    AUTHOR

        Abhinav Thapaliya 

    DATE

        7/3/2019

*/
void Game::quitGame(Player * player){
    cout << "\n\n The " << player->getPlayerType() << " player chose to quit the game \n";
    player->setQuit(true);
    aPlayerQuitGame = true;
}


/**/
    /*
    computePoints - Compute points for a player

    NAME

        computePoints

    SYNOPSIS

        int Game::computePoints(Player *player)

    DESCRIPTION
        
        Compute points for a player and describe how a player got those points.
        The number of points a player earns in a game depends upon the following factors:
        - points the player earned by reaching "home positions" of the opponent
        - number of opponents' pieces the player captured. the player made. 5 point per capture
        - if the player quit the game. If he did, he will be penalized 5 points   

    RETURNS

        An integer value that states the number of points the player got

    AUTHOR

        Abhinav Thapaliya 

    DATE

        7/3/2019

*/
int Game::computePoints(Player *player){
    int pointsByReachingOppHomePositions = gameBoard->computePointsBasedOnHomePositions( player->getColor() );
    int pointsEarnedThroughCaptures = player->getNumCaptures() * POINT_PER_CAPTURE;
    int pointsEarnedByQuitting = player->getQuit()? QUITTING_PENALTY: 0;
    int totalPoints = (pointsByReachingOppHomePositions + pointsEarnedThroughCaptures + pointsEarnedByQuitting);

    cout << "\n\nThe " << player->getPlayerType() << " got " << pointsByReachingOppHomePositions << " by reaching opponent's home pieces \n";
    cout << "The " << player->getPlayerType() << " got " << pointsEarnedThroughCaptures << " points by capturing " << player->getNumCaptures()
        << " opponent's pieces\n";
    cout << "The " << player->getPlayerType() << " was penalized " << -1 * pointsEarnedByQuitting << " for quitting the game\n";
    cout << "Total points earned by " << player->getPlayerType() << " in this round: " << totalPoints << " \n\n";

    return totalPoints;
}


/**/
    /*
    determineWinner - Announce the game result

    NAME

        determineWinner

    SYNOPSIS

        void Game::determineWinner()

    DESCRIPTION
        
        Determine if one of the players won the game or the game ended in a draw.
        Display the result on the screen

    RETURNS

        None

    AUTHOR

        Abhinav Thapaliya 

    DATE

        7/9/2019

*/
void Game::determineWinner(){
    int humanPlayerPoints = humanPlayer->getScore();
    int computerPlayerPoints = computerPlayer->getScore();

    if( humanPlayerPoints > computerPlayerPoints ){
        cout << "The human player won this game because they got the better score in this game \n";
        // Setting turn for the next game as the winner of this game gets to play first in the next game
        turn = false; 
        previousGameWinner = humanPlayer->getPlayerType();
    }
    else if( computerPlayerPoints > humanPlayerPoints ) {
        cout << "The computer player won this game because they got the better score in this game \n";
        // Setting turn for the next game as the winner of this game gets to play first in the next game
        turn = true; 
        previousGameWinner = computerPlayer->getPlayerType();
    }
    else {
        cout << "The game ended in a tie because both players have the same scores\n\n";
        previousGameWinner = "";
    }
}


/**/
    /*
    saveGame - Save the key game stats in a text file 

    NAME

        saveGame

    SYNOPSIS

        void Game::saveGame()

    DESCRIPTION
        
       Save players' tournament scores, the pieces on the board, board dimension, gameCount and who plays next 

    RETURNS

        None

    AUTHOR

        Abhinav Thapaliya 

    DATE

        7/9/2019

*/
void Game::saveGame(){
    string saveFileName = "savedChampionship.txt";
    ofstream saveFile;

    saveFile.open( saveFileName.c_str() );
    saveFile << "Game: " << gameCount << "\n\n";

    savePlayerStats( saveFile, computerPlayer, championshipScoreComputer );
    savePlayerStats( saveFile, humanPlayer, championshipScoreHuman );
    saveBoard( saveFile );
    saveNextPlayer( saveFile );

    cout << "\nSaved the game. The name of the saved game file is " << saveFileName << "\n\n";
	exit(0);
}


/**/
    /*
    savePlayerStats - Save the players' stats in a text file

    NAME

        savePlayerStats

    SYNOPSIS

        void Game::savePlayerStats(std::ofstream &saveFile, Player *player, int playerChampionshipScore)

    DESCRIPTION
        
       Save players' tournament scores and players' color 

    RETURNS

        None

    AUTHOR

        Abhinav Thapaliya 

    DATE

        7/9/2019

*/
void Game::savePlayerStats(std::ofstream &saveFile, Player *player, int playerChampionshipScore){
    string colorString = player->getColor() == Piece::BLACK? "Black" : "White";
    
    saveFile << player->getPlayerType() << ":\n";
    saveFile << "\t" << "Score: " << playerChampionshipScore << endl;
    saveFile << "\t" << "Color: " << colorString << "\n\n";
}


/**/
    /*
    saveBoard - Save the details about the game board in a text file 

    NAME

        saveBoard

    SYNOPSIS

        void Game::saveBoard(std::ofstream &saveFile)

    DESCRIPTION
        
       Save the pieces in a board and the board dimension. The saved data looks like this:

        Dimension: 5

        Board:
        O  W  O  O  W  
        O  O  WW  W  W
        W  W  B  B  O
        B  B  B  O  O  
        O  B  O  O  B  

        Here W represents White pieces while B represents Black pieces. WW or BB represent white or black
        pieces that can capture opponent's pieces respectively

    RETURNS

        None

    AUTHOR

        Abhinav Thapaliya 

    DATE

        7/9/2019

*/
void Game::saveBoard(std::ofstream &saveFile){
    saveFile << "Dimension: " << gameBoard->getDimension() << "\n\n";
    gameBoard->writeToFile( saveFile );
}


/**/
    /*
    saveNextPlayer - Save the turn details 

    NAME

        saveNextPlayer

    SYNOPSIS

        void Game::saveNextPlayer(std::ofstream &saveFile)

    DESCRIPTION
        
       Save who plays next in the game 

    RETURNS

        None

    AUTHOR

        Abhinav Thapaliya 

    DATE

        7/9/2019

*/
void Game::saveNextPlayer(std::ofstream &saveFile){
    Player * currentPlayer = getCurrentPlayer();

    saveFile << "Next Player: " << currentPlayer->getPlayerType() << endl;
}


/**/
    /*
    askForHelp - Make sure the human player gets help when he asks for it 

    NAME

        askForHelp

    SYNOPSIS

        void Game::askForHelp( Player * player )

    DESCRIPTION
        
       Make sure the human player gets help when he asks for it 

    RETURNS

        None

    AUTHOR

        Abhinav Thapaliya 

    DATE

        7/9/2019

*/
void Game::askForHelp( Player * player ){
    player->getHelp( gameBoard );
}