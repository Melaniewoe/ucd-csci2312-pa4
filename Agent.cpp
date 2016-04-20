//
//  Agent.cpp
//  PA4
//  Copyright © 2016 Melanie Woe. All rights reserved.
//


#include <iostream>
#include "Agent.h"
#include "Food.h"


using namespace std;

namespace Gaming
{
    const double Agent::AGENT_FATIGUE_RATE = 0.3;
    
    Agent::Agent(const Game &g, const Position &p, double energy):Piece(g, p)
    {
        __energy = energy;
    }
    
    Agent::~Agent()
    {
        
    }
    
   
    void Agent::age()
    {
        __energy -= AGENT_FATIGUE_RATE;
    }
    
    //bool isViable() const override final { return !isFinished() && __energy > 0.0; }
    
    Piece &Agent::operator*(Piece &other)
    {
        
        Agent *agent = dynamic_cast<Agent*>(&other);
        if (agent)
        {
            interact(agent);
        }
        Resource *res = dynamic_cast<Resource*>(&other);
        if (res)
        {
            interact(res);
        }
        
        return *this;
      
    }
    
    Piece &Agent::interact(Agent *other)
    {
        if (this -> __energy == other -> __energy)
        {
            this -> finish();
            other -> finish();
        }
        else if (this -> __energy < other -> __energy)
        {
            this -> finish();
        }
        else if (this -> __energy > other -> __energy)
        {
            other -> finish();
        }
        
        return *this;
    }
    
    Piece &Agent::interact(Resource *other)
    {
        this->addEnergy(other -> consume());
        return *this;
    }
}



