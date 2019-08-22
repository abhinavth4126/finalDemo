#ifndef PIECE_H_INCLUDED
#define PIECE_H_INCLUDED



#endif // PIECE_H_INCLUDED

#pragma once

#include <iostream>
#include <cstdlib>

using namespace std;

class Piece
{
public:
    // Symbolic constants
    static const char BLACK = 'B';
    static const char WHITE = 'W';

    // Constructors
    Piece();
    Piece( char color, bool capture);

    // Mutators
    bool setColor(char color);
    void setCapture( bool capture );

    // Selectors
    inline char getColor() const { 
        return this->color;
    }
    
    inline bool getCapture() const { 
        return this->canCapture;
    }

    // Utility functions
    void print();
    char getOpponentsColor();


private:
    //Member variables
    char color;
    bool canCapture; // Some pieces can capture opponent's pieces while some pieces can't
};