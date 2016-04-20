//
//  DefaultAgentStrategy.cpp
//  PA4
//
//  Copyright © 2016 Melanie Woe. All rights reserved.
//

#include <iostream>
#include "DefaultAgentStrategy.h"

using namespace std;

namespace Gaming
{
    
    
    DefaultAgentStrategy::DefaultAgentStrategy()
    {
        
    }
    DefaultAgentStrategy::~DefaultAgentStrategy()
    {
        
    }
    ActionType DefaultAgentStrategy::operator()(const Surroundings &s) const
    {
       
        vector<int> pos;
        unsigned int seed;
        default_random_engine rnd(seed);
     
        for (int i = 0; i < 9; ++i)
        {
            if (s.array[i] == PieceType::ADVANTAGE)
            {
                pos.push_back(i);
            }
        }
        
        
        if (pos.size() == 0)
        {
            for (int i = 0; i < 9; ++i)
            {
                if (s.array[i] == PieceType::SIMPLE)
                {
                    pos.push_back(i);
                }
            }
        }
        
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
        

        if (pos.size() == 0)
        {
            for (int i = 0; i < 9; ++i)
            {
                if (s.array[i] == PieceType::FOOD)
                {
                    pos.push_back(i);
                }
            }
        }
        
        if (pos.size() > 0)
        {
            int ind = pos[rnd() % pos.size()];
            if (pos.size() == 1) ind = pos[0];
            
            ActionType act;
            switch (ind)
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
                case 8: act = SE;
                    break;
                default: act = STAY;
            }
            return (act);
        }
        
        return STAY;
    }
}
