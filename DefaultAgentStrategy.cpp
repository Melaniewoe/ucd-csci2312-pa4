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
       
        std::vector<int> pos;
        unsigned int seed = (unsigned int)std::chrono::system_clock::now().time_since_epoch().count();
        std::default_random_engine rnd(seed);
     
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
            int posIndex = pos[rnd() % pos.size()];
            if (pos.size() == 1) posIndex = pos[0];
            
            ActionType ac;
            switch (posIndex) {
                case 0: ac = NW; break;
                case 1: ac = N; break;
                case 2: ac = NE; break;
                case 3: ac = W; break;
                case 4: ac = STAY; break;
                case 5: ac = E; break;
                case 6: ac = SW; break;
                case 7: ac = S; break;
                case 8: ac = SE; break;
                default: ac = STAY;
            }
            return (ac);
        }
        
        return ActionType::STAY;
    }
}
