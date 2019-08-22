#include "Game.h"

class Championship{
public:
    Championship();
    ~Championship();
    void startChampionship();

private:

    // Member variables
    Human * humanPlayer;
    Computer * computerPlayer;

    // Utitility member functions
    void printWelcomeMessage();
    void loadTheChampionship();

    string getValidFilePath();
    bool pathValid( string filePath );
    int parseNumber( stringstream & stream );
    char getColorInitial( string colorFull );
    string parseNextWord( stringstream & stream );
    string parseNextPlayer( stringstream & stream );
    void parsePlayer( ifstream & inFile, int & playerScore, char & playerColor );
    void parseBoard( ifstream & inFile, int dimension, vector <vector <string> > & boardString );
    vector <string> parseOneBoardRow( stringstream & lineStream );

    Board * createBoard( const vector <vector <string> > & boardString, int boardDimension );
    vector <vector <Piece*> > getBoardWithActualPieces( const vector <vector <string> > & boardString, int boardDimension );

    void updatePlayerScores( Human * human, Computer * computer );
    void displayPlayerScores();

    void playChampionshipWithoutLoading();

    bool championshipOver();

    int getBoardDimension();

    void announceTheWinner();
};