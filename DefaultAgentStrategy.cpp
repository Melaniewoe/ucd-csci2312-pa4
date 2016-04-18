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
        bool found = true;
        ActionType act;
        
        for (int i = 0; i <9; i++)
        {
            if ((s.array[i] == STRATEGIC || s.array[i] == SIMPLE))
            {
                switch(i)
                {
                    case 0: act = N;
                        found = false;
                        break;
                    case 1: act = NE;
                        found = false;
                        break;
                    case 3: act = NW;
                        found = false;
                        break;
                    case 4: act = E;
                        found = false;
                        break;
                    case 5: act = S;
                        found = false;
                        break;
                    case 6: act = SE;
                        found = false;
                        break;
                    case 7: act = SW;
                        found = false;
                        break;
                    case 8: act = E;
                        found = false;
                        break;
                        
                }
                if (found == false)
                {
                    i = 9;
                }
            }
            else if (s.array[i] == ADVANTAGE)
            {
                switch(i)
                {
                    case 0: act = N;
                        found = false;
                        break;
                    case 1: act = NE;
                        found = false;
                        break;
                    case 3: act = NW;
                        found = false;
                        break;
                    case 4: act = E;
                        found = false;
                        break;
                    case 5: act = S;
                        found = false;
                        break;
                    case 6: act = SE;
                        found = false;
                        break;
                    case 7: act = SW;
                        found = false;
                        break;
                    case 8: act = E;
                        found = false;
                        break;
                        
                }
                if (found == false)
                {
                    i = 9;
                }
                
            }
            else if (s.array[i] == FOOD)
            {
                switch(i)
                {
                    case 0: act = N;
                        found = false;
                        break;
                    case 1: act = NE;
                        found = false;
                        break;
                    case 3: act = NW;
                        found = false;
                        break;
                    case 4: act = E;
                        found = false;
                        break;
                    case 5: act = S;
                        found = false;
                        break;
                    case 6: act = SE;
                        found = false;
                        break;
                    case 7: act = SW;
                        found = false;
                        break;
                    case 8: act = E;
                        found = false;
                        break;
                        
                }
                if (found == false)
                {
                    i = 9;
                }
            }
            else if (s.array[i] == EMPTY)
            {
                switch(i)
                {
                    case 0: act = N;
                        found = false;
                        break;
                    case 1: act = NE;
                        found = false;
                        break;
                    case 3: act = NW;
                        found = false;
                        break;
                    case 4: act = E;
                        found = false;
                        break;
                    case 5: act = S;
                        found = false;
                        break;
                    case 6: act = SE;
                        found = false;
                        break;
                    case 7: act = SW;
                        found = false;
                        break;
                    case 8: act = W;
                        found = false;
                        break;
                        
                }
                if (found == false)
                {
                    i = 9;
                }
            }
            
            
            
            if (found == true)
            {
                act = STAY;
            }
            
            
            
            
            
        }
        
        return act;
    }

}
