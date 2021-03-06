//
//  Resource.cpp
//  PA4
//
//  Copyright © 2016 Melanie Woe. All rights reserved.
//

#include "Resource.h"

using namespace std;

namespace Gaming
{
    
    const double Resource::RESOURCE_SPOIL_FACTOR = 1.2;
    
    Resource::Resource(const Game &g, const Position &p, double capacity):Piece(g, p)
    {
        __capacity = capacity;
    }
    
    Resource::~Resource()
    {
        
    }
    
    
    
    double Resource::consume()
    {
        
        double cap = __capacity;
        __capacity = 0;
        finish();
        return cap;
        

    }
    
    void Resource::age()
    {
        
        __capacity -= RESOURCE_SPOIL_FACTOR;
        if (__capacity < 0.01)
        {
            //__capacity = 0.0;
            finish();
            
        }
         
    }
    
    
    ActionType Resource::takeTurn(const Surroundings &s) const
    {
        return STAY;
        
    }
    
    // note: these won't be called while resources don't move
    Piece &Resource::operator*(Piece &other)
    {
        return *this;
    }
    Piece &Resource::interact(Agent *)
    {
        return *this;
    }
    Piece &Resource::interact(Resource *)// note: no interaction between resources
    {
        return *this;
    }
}
