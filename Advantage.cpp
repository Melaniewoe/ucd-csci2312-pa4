//
//  Advantage.cpp
//  PA4
//
//  Copyright © 2016 Melanie Woe. All rights reserved.
//

#include <iostream>
#include <sstream>
#include "Advantage.h"

using namespace std;

namespace Gaming
{
    const double Advantage::ADVANTAGE_MULT_FACTOR = 2.0;
    const char Advantage::ADVANTAGE_ID = 'D';
    
    Advantage::Advantage(const Game &g, const Position &p, double capacity):Resource(g, p, capacity)
    {
        __capacity *=  ADVANTAGE_MULT_FACTOR;
    }
    Advantage::~Advantage()
    {
        
    }
    
    //PieceType getType() const override { return PieceType::ADVANTAGE; }
    
    void Advantage::print(std::ostream &os) const
    {
        stringstream ss;
        
        string s;
        s = to_string(__id);
        
        ss << ADVANTAGE_ID;
        ss << s;
    }
    
    double Advantage::getCapacity() const
    {
        return (__capacity*ADVANTAGE_MULT_FACTOR) ;
    }
    double Advantage::consume()
    {
        double cap = getCapacity();
        __capacity = -1;
        finish();
        return cap;
    }
}