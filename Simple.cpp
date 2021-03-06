//
//  Simple.cpp
//  PA4
//
//  Copyright © 2016 Melanie Woe. All rights reserved.
//

#include <iostream>
#include <sstream>

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
        stringstream ss;
        string s;
        ss << SIMPLE_ID << __id;
        ss << s;
        
        getline(ss, s);
        
        for (int i = 0; i < s.length(); ++i)
        {
            os << s[i];
        }
        
    }
    
    ActionType Simple::takeTurn(const Surroundings &s) const
    {
        std::vector<int> pos;
        unsigned seed;
        std::default_random_engine rnd(seed);
        
        for (int i = 0; i < 9; ++i)
        {
            if (s.array[i] == PieceType::ADVANTAGE || s.array[i] == PieceType::FOOD)
            {
                pos.push_back(i);
                
            }
        }
        //Check for Empty
        if (pos.size() == 0)
        {
            for (int i = 0; i < 9; ++i)
            {
                if (s.array[i] == PieceType::EMPTY)
                {
                    pos.push_back(i);
                    
                }
            }
        }
        
        if (pos.size() > 0)
        {
            int i = pos[rnd() % pos.size()];
            if (pos.size() == 1) i = pos[0];
            
            
            ActionType act;
            switch (i)
            {
                case 0: act = NW;
                    break;
                case 1: act = N;
                    break;
                case 2: act = NE;
                    break;
                case 3: act = W;
                    break;
                case 4: act = STAY;
                    break;
                case 5: act = E;
                    break;
                case 6: act = SW;
                    break;
                case 7: act = S;
                    break;
                case 8: act= SE;
                    break;
                default: act = STAY;
            }
            return (act);
        }
        
        return ActionType::STAY;
    
    }
         

}
