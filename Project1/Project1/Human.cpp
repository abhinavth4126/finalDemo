#include "Human.h"

/**/
    /*
    rollADieOnce - Generate a random number between 1 and 6 based on user input

    NAME

        rollADieOnce

    SYNOPSIS

        int Human::rollADieOnce()

    DESCRIPTION
        An implementation of a pure virtual function with the same name in the Player class.
        Ask the user to press a key and generate a random number between 1 and 6

    RETURNS

        The randomly generated number (an integer between 1 and 6)

    AUTHOR

        Abhinav Thapaliya 

    DATE

        7/1/2019

*/
int Human::rollADieOnce(){
    char actionInput;
    string dummyInput;

    do{
        cout << "\nPress 'r' to roll a dice for the human player\n";
        
        while(cin.peek()=='\n')
            cin.ignore();

        getline(cin, dummyInput);

        actionInput = dummyInput[0];

        actionInput = tolower(actionInput);
    } while( actionInput != 'r' );

    srand(time(NULL)); // Seeding the random number generator. More efficient to do this at the start of the tournament
    int dice = rand() % 6 + 1;

    return dice;
}

/**/
    /*
    selectColor - Ask the user to input a character. The character represents the color the user wants to select
    for a game

    NAME

        selectColor

    SYNOPSIS

        char Human::selectColor()

    DESCRIPTION
        
        An implementation of a pure virtual function with the same name in the Player class.
        
        
    RETURNS

        A char variable that denotes the user's color choice. 'B' if the user selected black. 'W'
        if the user selected white 

    AUTHOR

        Abhinav Thapaliya 

    DATE

        7/1/2019

*/
char Human::selectColor(){
    char colorSelection;
    string dummyInput;

    do{
        cout << "\n\tHuman player, please select a color you'd like to play\n";
        cout << "\t\tType 'b' to select black\n";
        cout << "\t\tType 'w' to select white\n";

        while(cin.peek()=='\n')
            cin.ignore();

        getline(cin, dummyInput);

        colorSelection = tolower( dummyInput[0] );
    } while( !(colorSelection == 'b' || colorSelection == 'w') );

    return toupper(colorSelection);
}


/**/
    /*
    showGameOptions - Show the game menu so that the Human player can make moves

    NAME

        showGameOptions

    SYNOPSIS

        void Human::showGameOptions()

    DESCRIPTION
        
        An implementation of a pure virtual function with the same name in the Player class.
        
        
    RETURNS

        None

    AUTHOR

        Abhinav Thapaliya 

    DATE

        7/2/2019

*/
void Human::showGameOptions(){
    cout << "\n\t" << Player::GAME_OPTION_SAVE_GAME << ". Save the game\n";
    cout << "\t" << Player::GAME_OPTION_MAKE_MOVE << ". Make a move \n";
    cout << "\t" << GAME_OPTION_HELP << ". Ask for help \n";
    cout << "\t" << GAME_OPTION_QUIT_GAME << ". Quit the game \n";
}


/**/
    /*
    getGameOption - Make the user select one of the game options listed on the game menu

    NAME

        getGameOption

    SYNOPSIS

        int Human::getGameOption(Board * gameBoard)

    DESCRIPTION
        
        An implementation of a pure virtual function with the same name in the Player class.
        
        
    RETURNS

        An integer value that represents the menu choice the user made

    AUTHOR

        Abhinav Thapaliya 

    DATE

        7/2/2019

*/
int Human::getGameOption(Board * gameBoard){
    int gameOption;
    string potentialInput;

    do{
        cout << "Enter a game option (" << GAME_OPTION_SAVE_GAME << " - " << GAME_OPTION_QUIT_GAME << ")\n";
        cin >> potentialInput;
        gameOption = extractDigitFromText( potentialInput );
    } while( !(gameOption >= GAME_OPTION_SAVE_GAME && gameOption <= GAME_OPTION_QUIT_GAME ) );

    return gameOption;
}

/**/
    /*
    getGameOptionForQuitGame - Get the game menu option for quitting the game

    NAME

        getGameOptionForQuitGame

    SYNOPSIS

        int Human::getGameOptionForQuitGame()

    DESCRIPTION
        
        An implementation of a pure virtual function with the same name in the Player class.
        
    RETURNS

        An integer value that represents the menu choice if the user wants to quit game 

    AUTHOR

        Abhinav Thapaliya 

    DATE

        7/2/2019

*/
int Human::getGameOptionForQuitGame(){
    return GAME_OPTION_QUIT_GAME;
}


/**/
    /*
    getRowForABoardPiece - Get the row number of the piece the player wants to move 

    NAME

        getRowForABoardPiece

    SYNOPSIS

        int Human::getRowForABoardPiece( int maxRow, Board * gameBoard )

    DESCRIPTION
        
        An implementation of a pure virtual function with the same name in the Player class.
        
    RETURNS

        An integer value that represents the row number of the piece the player selected to move

    AUTHOR

        Abhinav Thapaliya 

    DATE

        7/2/2019

*/
int Human::getRowForABoardPiece( int maxRow, Board * gameBoard ){
    return inputRowOrCol( maxRow, "row");
}


/**/
    /*
    getColumnForABoardPiece - Get the column number of the piece the player wants to move 

    NAME

        getColumnForABoardPiece

    SYNOPSIS

        int Human::getColumnForABoardPiece( int maxCol, Board * gameBoard )

    DESCRIPTION
        
        An implementation of a pure virtual function with the same name in the Player class.
        
    RETURNS

        An integer value that represents the column number of the piece the player selected to move

    AUTHOR

        Abhinav Thapaliya 

    DATE

        7/3/2019

*/
int Human::getColumnForABoardPiece( int maxCol, Board * gameBoard ){
    return inputRowOrCol( maxCol, "column");
}


/**/
    /*
    inputRowOrCol - Make the user select a value between 1 and maxRowOrCol

    NAME

        inputRowOrCol

    SYNOPSIS

        int Human::inputRowOrCol(int maxRowOrCol, string prompt)

    DESCRIPTION
        
        The function also verifies any input the user tries to make
        
    RETURNS

        An integer value that represents the row or the column number of the piece the player selected to move

    AUTHOR

        Abhinav Thapaliya 

    DATE

        7/3/2019

*/
int Human::inputRowOrCol(int maxRowOrCol, string prompt){
    int choice;
    string potentialInput;

    do{
        cout << "Enter " << prompt << " of the piece you want to move (1-" << maxRowOrCol<< ")\n";
        cin >> potentialInput;

        choice = extractDigitFromText( potentialInput );
    } while( !(choice > 0 && choice <= maxRowOrCol ) );

    return choice - 1;
}


/**/
    /*
    extractDigitFromText - Extract a one digit integer from a string input specified in the parameter

    NAME

        extractDigitFromText

    SYNOPSIS

        int Human::extractDigitFromText( string potentialNumber)

    DESCRIPTION
        
        A function used to verfiy that the input a player tries to make is a valid one digit integer
        input. In many, if not in all cases where the user needs to enter an integer to continue, the user
        needs to enter a one digit integer
        
    RETURNS

        An one digit integer value if the string, potentialNumber is a valid input, i.e is of
        length 1 and contains a digit. A number denoting invalid input if the input is not valid

    AUTHOR

        Abhinav Thapaliya 

    DATE

        7/3/2019

*/
int Human::extractDigitFromText( string potentialNumber){
    // A string representing a potentialNumber can't be longer than 1 character
    if(potentialNumber.length() > 1 ) 
        return INVALID_INPUT; 

    char firstChar = potentialNumber[0];

    // 48 = asciiCodeFor 0 . 57 = asciiCode for 9  
    if( firstChar >= 48 && firstChar <= 57 ) {
        //Say the user entered 9. Ascii code of 9 is 57. We are returning (57 - 48) = 9, which is the value we should  be returning
        return firstChar - 48; 
    }
        
    return INVALID_INPUT; 
}


/**/
    /*
    getMoveDirection - Get the direction in which the user wants to move a piece in

    NAME

        getMoveDirection

    SYNOPSIS

        int Human::getMoveDirection()

    DESCRIPTION
        
        Get the integer value that is the symbolic representation of the direction the player wants
        to move a piece in
        
    RETURNS

        Return one of the values denoted by the symbolic constants MOVE_NORTHEAST, MOVE_NORTHWEST, MOVE_SOUTHEAST,
        MOVE_SOUTHWEST

    AUTHOR

        Abhinav Thapaliya 

    DATE

        7/3/2019

*/
int Human::getMoveDirection() {
    int moveDirection;
    string potentialInput; 

    do{
        cout << "\n Select the direction in which you want to move the piece \n";
        cout << "\t" << MOVE_NORTHEAST << ") Move northeast \n";
        cout << "\t" << MOVE_NORTHWEST << ") Move northwest \n";
        cout << "\t" << MOVE_SOUTHEAST << ") Move southeast \n";
        cout << "\t" << MOVE_SOUTHWEST << ") Move southwest \n";

        cin >> potentialInput;
        moveDirection = extractDigitFromText( potentialInput );
    } while( !(moveDirection == MOVE_NORTHEAST || moveDirection == MOVE_NORTHWEST || moveDirection == MOVE_SOUTHEAST || moveDirection == MOVE_SOUTHWEST) );

    return moveDirection;
}


/**/
    /*
    getHelp - Print the instructions so that the human player can make efficient moves

    NAME

        getHelp

    SYNOPSIS

        void Human::getHelp(Board *gameBoard)

    DESCRIPTION
        
        The "efficient moves" printed here are based on the computations made in the Player class
        
    RETURNS

        None

    AUTHOR

        Abhinav Thapaliya 

    DATE

        7/20/2019

*/
void Human::getHelp(Board *gameBoard){
    cout << "\nThe player should ";

    if( computeOptimalMove( gameBoard ) ){
        Piece * optimalPiece = getOptimalPiece();
        int row = gameBoard->getRowOfAPiece(optimalPiece) + 1;
        int col = gameBoard->getColumnOfAPiece(optimalPiece) + 1;
        int optimalDirection = getOptimalMoveDirection();

        cout << "move the piece at row, " << row << " and column, " << col << " " << gameBoard->getDirectionString(optimalDirection) << ".\n\n";
    }
    else{
        cout << "quit the game as there are no remaining moves they can make \n";
    }
}