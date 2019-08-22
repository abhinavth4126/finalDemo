#include "Championship.h"

/**/
    /*
    Championship - Default constructor

    NAME

        Championship

    SYNOPSIS

        Championship::Championship()

    DESCRIPTION
        
        Initialize references to new Human and Computer player 

    RETURNS

        None

    AUTHOR

        Abhinav Thapaliya 

    DATE

        7/16/2019

*/
Championship::Championship(){
    humanPlayer = new Human();
    computerPlayer = new Computer();
}


/**/
    /*
    ~Championship - Destructor

    NAME

        ~Championship

    SYNOPSIS

        Championship::~Championship()

    DESCRIPTION
        
        Deallocate heap space used by member variables 

    RETURNS

        None

    AUTHOR

        Abhinav Thapaliya 

    DATE

        7/16/2019

*/
Championship::~Championship(){
    delete humanPlayer;
    delete computerPlayer;
}


/**/
    /*
    startChampionship - Load a saved championship or start a new one based on user choice

    NAME

        startChampionship

    SYNOPSIS

        void Championship::startChampionship()

    DESCRIPTION
        
        Load a saved championship or start a new one based on user choice 

    RETURNS

        None

    AUTHOR

        Abhinav Thapaliya 

    DATE

        7/16/2019

*/
void Championship::startChampionship(){
    printWelcomeMessage();

    bool loadChampionshipFromASavedFile = false;
    char loadChampionship;

    do{
        cout << "\nDo you want to load the championship from an existing file (y/n) \n";
        cin >> loadChampionship;
        loadChampionship = tolower(loadChampionship);
    } while( !(loadChampionship == 'y' || loadChampionship == 'n') );

    if( loadChampionship == 'y' ){
        loadTheChampionship();
    }
    else{
        // Play the championship without loading from a saved file 
        playChampionshipWithoutLoading();
    }  
}


/**/
    /*
    printWelcomeMessage - Print a message that welcomes the player playing the championship

    NAME

        printWelcomeMessage

    SYNOPSIS

        void Championship::printWelcomeMessage()

    DESCRIPTION
        
        Print a message 

    RETURNS

        None

    AUTHOR

        Abhinav Thapaliya 

    DATE

        7/16/2019

*/
void Championship::printWelcomeMessage(){
    cout << "\n\n Welcome to FiveFieldCono \n\n";
}


/**/
    /*
    loadTheChampionship - Load a saved championship by parsing a text file that has details 
    needed to configure a game 

    NAME

        loadTheChampionship

    SYNOPSIS

        void Championship::loadTheChampionship()

    DESCRIPTION
        
        The text file that needs to be parsed has the following info:
            - Board dimension
            - Pieces in the board
            - Details about the player 
            - Game count 
            - Next player 

    RETURNS

        None

    AUTHOR

        Abhinav Thapaliya 

    DATE

        7/16/2019

*/
void Championship::loadTheChampionship(){
    int gameNumber; 
    int computerScore; 
    int humanScore;

    char computerColor;
    char humanColor;

    string nextPlayer; 
    int boardDimension;

    ifstream inFile;
    string oneLine;

    vector <vector <string> > boardString;

    string fileName = getValidFilePath();
    inFile.open( fileName.c_str() );

    while( getline(inFile, oneLine) ){
        stringstream lineStream( oneLine );

        string firstWord;
        lineStream >> firstWord;

        if( firstWord.find("Game") != string::npos ){
            gameNumber = parseNumber( lineStream );
        }
        else if( firstWord.find("Dimension") != string::npos ){
            boardDimension = parseNumber( lineStream );
        }
        else if( firstWord.find("Next") != string::npos ){
            nextPlayer = parseNextPlayer( lineStream );
        }
        else if( firstWord.find("Computer") != string::npos ){
            parsePlayer( inFile, computerScore, computerColor );
        }
        else if( firstWord.find("Human") != string::npos ){
            parsePlayer( inFile, humanScore, humanColor );
        }
        else if( firstWord.find("Board") != string::npos ){
            parseBoard( inFile, boardDimension, boardString );
        }       
    }

    Human * human = new Human();
    Computer * computer = new Computer();
    Board * board = createBoard( boardString, boardDimension );

    human->setColor(humanColor);
    computer->setColor(computerColor);

    computerPlayer->setScore( computerScore );
    humanPlayer->setScore( humanScore );

    Game loadedGame = Game( board, computer, human, gameNumber, nextPlayer, humanScore, computerScore );

    // Update players score after round ends
    updatePlayerScores( loadedGame.getHumanPlayer(), loadedGame.getComputerPlayer() );
    displayPlayerScores();

    // Play additional "unloaded" games
    if( !championshipOver() )
        playChampionshipWithoutLoading();
    else
        announceTheWinner();
}


/**/
    /*
    getValidFilePath - Get valid path to a file that contains information needed to load a game 

    NAME

        getValidFilePath

    SYNOPSIS

        string Championship::getValidFilePath()

    DESCRIPTION
        
        Get valid path to a file that contains information needed to load a game 

    RETURNS

        A string variable - Valid path to a file that contains information needed to load a game 

    AUTHOR

        Abhinav Thapaliya 

    DATE

        7/16/2019

*/
string Championship::getValidFilePath(){
    //Get file path from the player
    string path;
    bool validPath = false;

    do{
        cout << "\nEnter the path of the file you want to load: \n";

        while(cin.peek()=='\n'){
            cin.ignore();
        }
        getline(cin, path);

        validPath = pathValid( path );

        if( ! validPath )
            cout << "Oops. You entered an invalid path. Try again \n";

    } while( !validPath ); // Check validity of the file path

    return path;
}


/**/
    /*
    pathValid - Determine if the user entered a valid file path 

    NAME

        pathValid

    SYNOPSIS

        bool Championship::pathValid( string filePath )

    DESCRIPTION
        
         Check if the user entered a valid path 

    RETURNS

        True if the user entered a valid file path. False otherwise 

    AUTHOR

        Abhinav Thapaliya 

    DATE

        7/16/2019

*/
bool Championship::pathValid( string filePath ){
    ifstream inFile;

    inFile.open( filePath.c_str() );

    if (!inFile) 
        return false;

    return true;
}


/**/
    /*
    parseNumber - Given a reference to a text file, parse the next integer

    NAME

        parseNumber

    SYNOPSIS

        int Championship::parseNumber(stringstream &stream)

    DESCRIPTION
        
         Given a reference to a text file, parse the next integer

    RETURNS

        An integer 

    AUTHOR

        Abhinav Thapaliya 

    DATE

        7/16/2019

*/
int Championship::parseNumber(stringstream &stream){
    int number;

    stream >> number;

    return number;
}


/**/
    /*
    getColorInitial - Return the first letter a string parameter 

    NAME

        getColorInitial 

    SYNOPSIS

        char Championship::getColorInitial(string colorFull)

    DESCRIPTION
        
        Return the first letter a string parameter

    RETURNS

        If the parameter is not an empty string, return the first letter of the string.
        Else return an empty character(' ')

    AUTHOR

        Abhinav Thapaliya 

    DATE

        7/16/2019

*/
char Championship::getColorInitial(string colorFull){
    char initial = ' ';

    if( colorFull.length() > 0 )
        initial = colorFull[0];

    return initial;
}


/**/
    /*
    parseNextWord -  Get the next word, given a reference to a text file 

    NAME

        parseNextWord 

    SYNOPSIS

        string Championship::parseNextWord(std::stringstream &stream)

    DESCRIPTION
        
        Get the next word 

    RETURNS

        A string variable 

    AUTHOR

        Abhinav Thapaliya 

    DATE

        7/16/2019

*/
string Championship::parseNextWord(std::stringstream &stream){
    string word;

    stream >> word;

    return word;
}


/**/
    /*
    parseNextPlayer -  Used to find out who the next player is in the championship.
    Player's turn is determied depending on who the next player is. If the next player
    is Computer player, it is computer's turn to make moves. Else it is human's turn to
    make his move 
    
    NAME

        parseNextPlayer 

    SYNOPSIS

        string Championship::parseNextPlayer(std::stringstream &stream)

    DESCRIPTION
        
        Get the second word given a reference to a text file 

    RETURNS

        A string variable 

    AUTHOR

        Abhinav Thapaliya 

    DATE

        7/16/2019

*/
string Championship::parseNextPlayer(std::stringstream &stream){
    string ignoreThisWord = parseNextWord(stream);
    
    return parseNextWord( stream );
}


/**/
    /*
    parsePlayer -  Parse the details needed to initialize a human or a computer player 
    
    NAME

        parsePlayer 

    SYNOPSIS

        void Championship::parsePlayer(std::ifstream &inFile, int &playerScore, char &playerColor)

    DESCRIPTION
        
        Extract the details like the player's tournament and the player's colr   

    RETURNS

        None 

    AUTHOR

        Abhinav Thapaliya 

    DATE

        7/16/2019

*/
void Championship::parsePlayer(std::ifstream &inFile, int &playerScore, char &playerColor){
    string oneLine;

    // Get the line that will contain information about player's score
    getline(inFile, oneLine );

    stringstream lineStream( oneLine );
    string firstWord;
        
    lineStream >> firstWord;

    // At this point, firstWord will look something like Score: 14
    playerScore = parseNumber( lineStream );

    getline(inFile, oneLine);

    stringstream lineStreamPlayerColor(oneLine);
    lineStreamPlayerColor >> firstWord;

    // At this point, firstWord will look something like Color: White
    string playerColorStr = parseNextWord( lineStreamPlayerColor );
    playerColor = getColorInitial( playerColorStr );
}


/**/
    /*
    parseBoard -  Parse the details needed to initialize a game board
    
    NAME

        parseBoard

    SYNOPSIS

        void Championship::parseBoard( ifstream & inFile, int dimension, vector <vector <string> > & boardString )

    DESCRIPTION
        
        Extract the details like the board's dimension and the pieces in the board 

    RETURNS

        None 

    AUTHOR

        Abhinav Thapaliya 

    DATE

        7/16/2019

*/
void Championship::parseBoard( ifstream & inFile, int dimension, vector <vector <string> > & boardString ){
    string oneLine;

    for(int i = 0; i < dimension; i++ ){
        // Get the line that will contain information about the items in a row of the board 
        getline(inFile, oneLine );
        stringstream lineStream( oneLine );

        vector <string> oneRow; 
        oneRow = parseOneBoardRow( lineStream );

        boardString.push_back( oneRow );
    }
}


/**/
    /*
    parseOneBoardRow -  Extract the pieces to be put in a row of the game board 
    
    NAME

        parseOneBoardRow

    SYNOPSIS

        vector <string> Championship::parseOneBoardRow( stringstream & lineStream )

    DESCRIPTION
        
        Extract the pieces to be put in a row of the game board

    RETURNS

        None 

    AUTHOR

        Abhinav Thapaliya 

    DATE

        7/16/2019

*/
vector <string> Championship::parseOneBoardRow( stringstream & lineStream ){
    string oneWord;
    vector <string> res;

    while( lineStream >> oneWord) {
        res.push_back(oneWord);
    }

    return res;
}


/**/
    /*
    createBoard -  Initialize a new board object and return the reference to the object 
    
    NAME

        createBoard

    SYNOPSIS

        Board * Championship::createBoard( const vector <vector <string> > & boardString, int boardDimension )

    DESCRIPTION
        
        Initialize a new board object and return the reference to the object 

    RETURNS

        Reference to the newly created board  

    AUTHOR

        Abhinav Thapaliya 

    DATE

        7/16/2019

*/
Board * Championship::createBoard( const vector <vector <string> > & boardString, int boardDimension ){
    vector <vector <Piece*> > actualBoard = getBoardWithActualPieces( boardString, boardDimension );

    Board * newBoard = new Board( actualBoard, boardDimension ); 
    
    return newBoard; 
}


/**/
    /*
    getBoardWithActualPieces -  Given a vector of vector of char variables, return a vector of vector of Piece object 
    reference. The returned vector is needed to initialize a board object 
    
    NAME

        getBoardWithActualPieces

    SYNOPSIS

        vector <vector <Piece*> > Championship::getBoardWithActualPieces( const vector <vector <string> > & boardString, int boardDimension )

    DESCRIPTION
        
        Given a vector of vector of char variables, return a vector of vector of Piece object 
        reference. The returned vector is needed to initialize a board object

    RETURNS

        A vector of vector of Pieces  

    AUTHOR

        Abhinav Thapaliya 

    DATE

        7/16/2019

*/
vector <vector <Piece*> > Championship::getBoardWithActualPieces( const vector <vector <string> > & boardString, int boardDimension ){
    vector <vector <Piece*> > outer;

    for(int i = 0; i < boardDimension; i++){
        vector <Piece*> inner;
        for(int j = 0; j < boardDimension; j++){

            string pieceString = boardString[i][j];
            Piece * actualPiece = NULL;

            if(pieceString == "W") // Use symbolic constants
                actualPiece = new Piece(Piece::WHITE, false);
            else if( pieceString == "B")
                actualPiece = new Piece( Piece::BLACK, false);
            else if( pieceString == "WW")
                actualPiece = new Piece( Piece::WHITE, true);
            else if( pieceString == "BB")
                actualPiece = new Piece( Piece::BLACK, true);

            inner.push_back( actualPiece );
        }

        outer.push_back(inner);
    }

    return outer;
}


/**/
    /*
    updatePlayerScores - Update the championship scores of the players denoted by the member variables
    humanPlayer and computerPlayer  
    
    NAME

        updatePlayerScores

    SYNOPSIS

        void Championship::updatePlayerScores(Human *human, Computer *computer)

    DESCRIPTION
        
        The championship players' scores are updated on the basis of the scores
        gained by the human and computer players in the latest game. 

    RETURNS

        None  

    AUTHOR

        Abhinav Thapaliya 

    DATE

        7/16/2019

*/
void Championship::updatePlayerScores(Human *human, Computer *computer){

    humanPlayer->updateScore( human->getScore() );
    computerPlayer->updateScore( computer->getScore() );
}


/**/
    /*
    displayPlayerScores - Display the players' championship scores 
    
    NAME

        displayPlayerScores

    SYNOPSIS

        void Championship::displayPlayerScores()

    DESCRIPTION
        
        Display the players' championship scores 

    RETURNS

        None  

    AUTHOR

        Abhinav Thapaliya 

    DATE

        7/16/2019

*/
void Championship::displayPlayerScores(){
    cout << "\nHuman player championship score: " << humanPlayer->getScore() << endl;
    cout << "Computer player championship score: " << computerPlayer->getScore() << "\n\n\n";
}


/**/
    /*
    playChampionshipWithoutLoading - Start ad pkay a new championship
    
    NAME

        playChampionshipWithoutLoading

    SYNOPSIS

        void Championship::playChampionshipWithoutLoading()

    DESCRIPTION
        
        Called when the player wants to play a new championship, istead of a loaded one 

    RETURNS

        None  

    AUTHOR

        Abhinav Thapaliya 

    DATE

        7/16/2019

*/
void Championship::playChampionshipWithoutLoading(){
    do{
        int boardDim = getBoardDimension();
        Game newGame( boardDim, humanPlayer->getScore(), computerPlayer->getScore() );

        // Update players' scores after each game ends
        updatePlayerScores( newGame.getHumanPlayer(), newGame.getComputerPlayer() );
        displayPlayerScores();

    } while( !championshipOver() );

    // Determine the winner
    announceTheWinner();
}


/**/
    /*
    championshipOver - Ask user to choose if they want to end the championship or start
    a new game and continue playing 
    
    NAME

        championshipOver

    SYNOPSIS

        bool Championship::championshipOver()

    DESCRIPTION
        
        Ask user to choose if they want to end the championship or start a new game and 
        continue playing 

    RETURNS

        True if the championship is over. False otherwise 

    AUTHOR

        Abhinav Thapaliya 

    DATE

        7/16/2019

*/
bool Championship::championshipOver(){
    char anotherGame;

    do{
        cout << "Do you want to play another game? (y/n)\n";
        cin >> anotherGame;
        anotherGame = tolower(anotherGame);
    } while( !(anotherGame == 'y' || anotherGame == 'n') );

    if( anotherGame == 'n')
        return true;

    return false;
}


/**/
    /*
    getBoardDimension - Get the user's choice for the dimension they want the board in the
    new game to have 
    
    NAME

        getBoardDimension

    SYNOPSIS

        int Championship::getBoardDimension()

    DESCRIPTION
        
        Before every new game starts, the user is asked to select the dimension for the 
        board. The selected dimension is the board dimension for the new game 

    RETURNS

        An integer value  

    AUTHOR

        Abhinav Thapaliya 

    DATE

        7/16/2019

*/
int Championship::getBoardDimension(){
    int boardDim;
    string potentialInput;

    do{
        cout << "\nEnter board dimension you would like for this game \n";
        cout << "\tEnter 5 to select a 5 * 5 board\n";
        cout << "\tEnter 7 to select a 7 * 7 board \n";
        cout << "\tEnter 9 to select a 9 * 9 board \n";
   
        cin >> potentialInput;
        boardDim = Human::extractDigitFromText( potentialInput );
   
    } while( !(boardDim == 5 || boardDim == 7 || boardDim == 9) );

    return boardDim;
}


/**/
    /*
    announceTheWinner - Announce the championship result 
    
    NAME

        announceTheWinner

    SYNOPSIS

        void Championship::announceTheWinner()

    DESCRIPTION
        
        Determine if one of the players won the game or the game ended in a draw.
        Display the result on the screen

    RETURNS

        None

    AUTHOR

        Abhinav Thapaliya 

    DATE

        7/16/2019

*/
void Championship::announceTheWinner(){
    cout << "**************************CHAMPIONSHIP OVER **************************\n";
    displayPlayerScores();
    
    if( humanPlayer->getScore() > computerPlayer->getScore() ){
        cout << "The human player won the tournament\n";
    }
    else if( computerPlayer->getScore() > humanPlayer->getScore() ){
        cout << "The computer player won the tournament \n";
    }
    else{
        cout << "The tournament ended in a draw. No one won \n";
    }

    cout << "\n Goodbye. Thank you for playing \n";
}