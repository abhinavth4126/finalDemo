#include "Computer.h"
#include "Human.h"
#include <stdlib.h>     /* srand, rand */
#include <time.h>


/**/
    /*
    rollADieOnce - Generate a random number between 1 and 6 based on user input

    NAME

        rollADieOnce

    SYNOPSIS

        int Computer::rollADieOnce()

    DESCRIPTION
        An implementation of a pure virtual function with the same name in the Player class.

    RETURNS

        The randomly generated number (an integer between 1 and 6)

    AUTHOR

        Abhinav Thapaliya 

    DATE

        7/2/2019

*/
int Computer::rollADieOnce(){
    srand(time(0)); // Seeding the random number generator. More efficient to do this at the start of the tournament
    int dice = rand() % 6 + 1;

    return dice;
}


/**/
    /*
    selectColor - Randomly determine the color the Computer player wants to select

    NAME

        selectColor

    SYNOPSIS

        char Computer::selectColor()

    DESCRIPTION
        
        An implementation of a pure virtual function with the same name in the Player class.
        
    RETURNS

        A char variable that denotes the computer player's color choice. The returned value is based on the
        value the function generates

    AUTHOR

        Abhinav Thapaliya 

    DATE

        7/2/2019

*/
char Computer::selectColor(){
    cout << "\n\tComputer player, please select a color you'd like to play\n";
    int colorChoice = rand() % 2;

    if( colorChoice == 0 )
        return Piece::BLACK;
    
    return Piece::WHITE;
}


/**/
    /*
    showGameOptions - Show the game menu so that the Computer player can make moves

    NAME

        showGameOptions

    SYNOPSIS

        void Computer::showGameOptions()

    DESCRIPTION
        
        An implementation of a pure virtual function with the same name in the Player class
        
    RETURNS

        None

    AUTHOR

        Abhinav Thapaliya 

    DATE

        7/2/2019

*/
void Computer::showGameOptions(){
    cout << "\n\t" << Player::GAME_OPTION_SAVE_GAME << ". Save the game\n";
    cout << "\t" << Player::GAME_OPTION_MAKE_MOVE << ". Make a move \n";
    //cout << "\t" << GAME_OPTION_QUIT_GAME << ". Quit the game \n"; 
}


/**/
    /*
    getGameOption - Make the user select one of the game options listed on the game menu

    NAME

        getGameOption

    SYNOPSIS

        int Computer::getGameOption(Board * gameBoard)

    DESCRIPTION
        
        An implementation of a pure virtual function with the same name in the Player class.
        The computer player chooses to make a move if it can make any legitimate moves. If there are 
        no valid moves remaining, the computer player will choose to quit the game so that
        the game can end
        
        
    RETURNS

        An integer value that represents the game option the computer player selected
    AUTHOR

        Abhinav Thapaliya 

    DATE

        7/2/2019

*/
int Computer::getGameOption( Board * gameBoard ){
    computeOptimalMove( gameBoard );
    int gameOption;
	int choice;
	string potentialInput;


    cout << "Enter a game option (" << GAME_OPTION_SAVE_GAME << " - " << GAME_OPTION_MAKE_MOVE << ")\n";
	do {
		cin >> potentialInput;

		choice = Human::extractDigitFromText(potentialInput);
	} while (choice!= 1 && choice != 2);
        
    if( getOptimalPiece() == NULL && getOptimalMoveDirection() == INVALID_INPUT ){
        gameOption = getGameOptionForQuitGame();
    }
	else if (choice == 2)
	{
		gameOption = GAME_OPTION_MAKE_MOVE;
	}
	else if (choice == 1)
	{
		gameOption = GAME_OPTION_SAVE_GAME;
	}
        
    
    cout << gameOption << endl;

    // Freeze the screen for a bit. So that the players can see the option the computer selected
    
    return gameOption;
}


/**/
    /*
    getGameOptionForQuitGame - Get the game menu option for quitting the game

    NAME

        getGameOptionForQuitGame

    SYNOPSIS

        int Computer::getGameOptionForQuitGame()

    DESCRIPTION
        
        An implementation of a pure virtual function with the same name in the Player class.
        
    RETURNS

        An integer value that represents the menu choice if the computer player wants to quit game 

    AUTHOR

        Abhinav Thapaliya 

    DATE

        7/2/2019

*/
int Computer::getGameOptionForQuitGame(){
    return GAME_OPTION_QUIT_GAME;
}


/**/
    /*
    getRowForABoardPiece - Get the row number of the piece the player wants to move 

    NAME

        getRowForABoardPiece

    SYNOPSIS

        int Computer::getRowForABoardPiece( int maxRow, Board * gameBoard )

    DESCRIPTION
        
        An implementation of a pure virtual function with the same name in the Player class.
        The value to be returned is computed in the Player class. 
        
    RETURNS

        An integer value that represents the row number of the piece the player selected to move

    AUTHOR

        Abhinav Thapaliya 

    DATE

        7/2/2019

*/
int Computer::getRowForABoardPiece( int maxRow, Board * gameBoard ){
    // computeOptimalMove( gameBoard );
    Piece * optimalPiece = getOptimalPiece(); 

    return gameBoard->getRowOfAPiece(optimalPiece);
}


/**/
    /*
    getColumnForABoardPiece - Get the column number of the piece the player wants to move 

    NAME

        getColumnForABoardPiece

    SYNOPSIS

        int Computer::getColumnForABoardPiece( int maxCol, Board * gameBoard )

    DESCRIPTION
        
        An implementation of a pure virtual function with the same name in the Player class. 
        The value to be returned is computed in the Player class. 
        
    RETURNS

        An integer value that represents the column number of the piece the player selected to move

    AUTHOR

        Abhinav Thapaliya 

    DATE

        7/3/2019

*/
int Computer::getColumnForABoardPiece( int maxCol, Board * gameBoard ){
    Piece * optimalPiece = getOptimalPiece();
    return gameBoard->getColumnOfAPiece(optimalPiece);
}


/**/
    /*
    getMoveDirection - Get the direction in which the user wants to move a piece in

    NAME

        getMoveDirection

    SYNOPSIS

        int Computer::getMoveDirection()

    DESCRIPTION
        
        Get the integer value that is the symbolic representation of the direction the player wants
        to move a piece in. The value to be returned is computed in the Player class. 
        
    RETURNS

        Return one of the values denoted by the symbolic constants MOVE_NORTHEAST, MOVE_NORTHWEST, MOVE_SOUTHEAST,
        MOVE_SOUTHWEST

    AUTHOR

        Abhinav Thapaliya 

    DATE

        7/3/2019

*/
int Computer::getMoveDirection(){
    return getOptimalMoveDirection();
}

/**/
    /*
    getHelp - Simply print an empty line because the computer player can't ask for help

    NAME

        getHelp

    SYNOPSIS

        void Computer::getHelp(Board *gameBoard)

    DESCRIPTION

        An implementation of a pure virtual function with the same name in the Player class. 
        It was necessary to create this function so that the code already written did not break.
        
    RETURNS

        None

    AUTHOR

        Abhinav Thapaliya 

    DATE

        7/20/2019

*/
void Computer::getHelp(Board *gameBoard){
    cout << endl;
}