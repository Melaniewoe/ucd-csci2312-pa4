//
//  Piece.cpp
//  PA4
//
//  Copyright © 2016 Melanie Woe. All rights reserved.
//

#include <iostream>
#include "Piece.h"

namespace Gaming
{
    unsigned int Piece::__idGen = 1000;
    
    Piece::Piece(const Game &g, const Position &p): __game(g)
    {
        __position = p;
        __finished = false;
        __turned = false;
        __id = __idGen++;
    }
    Piece::~Piece()
    {
        
        
        
    }
    
    std::ostream &operator<<(std::ostream &os, const Piece &piece)
    {
        if (&piece != nullptr)
        {
            piece.print(os);
        }
        piece.print(os);
        return os;
    }
}
