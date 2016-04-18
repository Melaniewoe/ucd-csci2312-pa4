//
//  food.cpp
//  PA4
//
//  Copyright © 2016 Melanie Woe. All rights reserved.
//

#include "Food.h"
#include <iostream>
using namespace std;


namespace Gaming
{
   
    const char Food::FOOD_ID = 'F';
    
    Food::Food(const Game &g, const Position &p, double capacity):Resource(g,p,capacity)
    {
        //Game = g;
        //Position = p;
       // capacity = 0;
    }
    
    Food::~Food()
    {
        //delete[];
    }
    
    PieceType getType() 
    {
        return PieceType::FOOD;
    }
        
    void Food::print(std::ostream &os) const
    {
        os << FOOD_ID << __id;  //???????
    }
 
    
}
