#include "Piece.h"

// Default constructor
Piece::Piece(){
    color = ' ';
    canCapture = false;
}


/**/
    /*
    Piece - Custom constructor

    NAME

        Piece

    SYNOPSIS

        Piece::Piece(char color, bool capture)

    DESCRIPTION

        Initialize the value of member variables based on the parameters received  

    RETURNS

        None

    AUTHOR

        Abhinav Thapaliya 

    DATE

        6/27/2019

*/
Piece::Piece(char color, bool capture){
    setColor( color );
    setCapture( capture );
}

/**/
    /*
    setColor - A mutator used to set the value of member variable, color

    NAME

        setColor

    SYNOPSIS

        bool Piece::setColor(char color)

    DESCRIPTION

        Set the value of member variable, color based on the parameter received       

    RETURNS

        None

    AUTHOR

        Abhinav Thapaliya 

    DATE

        6/27/2019

*/
bool Piece::setColor(char color){
    if( !(color == BLACK || color == WHITE) )
        return false;

    this->color = color;
    return true;
}

/**/
    /*
    setCapture - A mutator used to set the value of member variable, canCapture

    NAME

        setCapture

    SYNOPSIS

        void Piece::setCapture(bool capture)

    DESCRIPTION

        Set the value of member variable based on the parameter received       

    RETURNS

        None

    AUTHOR

        Abhinav Thapaliya 

    DATE

        6/27/2019

*/
void Piece::setCapture(bool capture){
    this->canCapture = capture;
}


/**/
    /*
    print - To display how a Piece looks

    NAME

        print

    SYNOPSIS

        void Piece::print()

    DESCRIPTION

        Color of the piece is used to represent how a piece looks. If the color of a piece is Piece::BLACK,
        'B' will be printed. If it is Piece::WHITE, 'W' will be printed       

    RETURNS

        None

    AUTHOR

        Abhinav Thapaliya 

    DATE

        6/27/2019

*/
void Piece::print(){
    cout << this->color;
}

/**/
    /*
    getOpponentsColor - To get the color that does not belong to the piece referred

    NAME

        getOpponentsColor

    SYNOPSIS

        char Piece::getOpponentsColor()

    DESCRIPTION

        If the color of the current piece(piece referred to by 'this' pointer) is Piece::BLACK, opponent's color
        would be Piece::WHITE and vice versa     

    RETURNS

        If the color of the current piece(piece referred to by 'this' pointer) is Piece::BLACK, return, if it is Piece::WHITE,
        return Piece::BLACK. Else return an Invalid character (a space character) 

    AUTHOR

        Abhinav Thapaliya 

    DATE

        6/27/2019

*/
char Piece::getOpponentsColor(){
    if( this->color == BLACK )
        return WHITE;

    if( this->color == WHITE )
        return BLACK;

    return ' '; // invalid
}