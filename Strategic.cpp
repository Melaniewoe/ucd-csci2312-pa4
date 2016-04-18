//
//  Strategic.cpp
//  PA4
//
//  Copyright © 2016 Melanie Woe. All rights reserved.
//

#include <iostream>
#include <sstream>

#include "Strategic.h"


using namespace  std;
namespace Gaming
{
    const char Strategic::STRATEGIC_ID = 'T';
    
    Strategic::Strategic(const Game &g, const Position &p, double energy, Strategy *s): Agent(g, p, energy)
    {
        __strategy = s;
    }
    Strategic::~Strategic()
    {
        delete __strategy;
    }
    
    //PieceType getType() const override { return PieceType::STRATEGIC; }
    
    void Strategic::print(std::ostream &os) const
    {
        stringstream ss;
        string s;
        s = to_string(__id);
        ss << STRATEGIC_ID;
        ss << s;
        getline(ss, s);
        for (int i = 0; i < s.length(); ++i)
        {
            os << s[i];
        }
        
    }
    
    ActionType Strategic::takeTurn(const Surroundings &s) const
    {
        return (*__strategy)(s);
    }

}
