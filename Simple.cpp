//
//  Simple.cpp
//  PA4
//
//  Copyright © 2016 Melanie Woe. All rights reserved.
//

#include <iostream>
#include "Simple.h"

using namespace std;

namespace Gaming
{
    const char Simple::SIMPLE_ID = 'S';
    
    Simple::Simple(const Game &g, const Position &p, double energy):Agent (g, p, energy)
    {
        
    }
    Simple::~Simple()
    {
        
    }
    
    //PieceType getType() const override { return PieceType::SIMPLE; }
    
    void Simple::print(std::ostream &os) const
    {
        os << SIMPLE_ID <<__id;
    }
    
    ActionType Simple::takeTurn(const Surroundings &s) const
    {
        vector<int> pos;
        default_random_engine re;
        
        for (int i = 0; i < 9; i++)
        {
            if (s.array[i] == PieceType::FOOD || s.array[i] == PieceType ::ADVANTAGE)
            {
                pos.push_back(i);
            }
            else if (pos.size() == 0)
            {
                if (s.array[i] == PieceType::EMPTY)
                {
                    pos.push_back(i);
                }
            }
        }
        
        if (pos.size() > 0)
        {
            int ind = pos[re() % pos.size()];
            if (pos.size() == 1)
            {
                ind = pos[0];
            }
            
            ActionType act;
            switch(ind)
            {
                case 0: act = N;
                    break;
                case 1: act = NE;
                    break;
                case 3: act = NW;
                    break;
                case 4: act = E;
                    break;
                case 5: act = S;
                    break;
                case 6: act = SE;
                    break;
                case 7: act = SW;
                    break;
                case 8: act = E;
                    break;
                    
            }
            return (act);
        }
        return STAY;
    }

}
