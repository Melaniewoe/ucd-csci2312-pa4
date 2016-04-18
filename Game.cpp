//
//  Game.cpp
//  PA4
//
//  Copyright © 2016 Melanie Woe. All rights reserved.
//


#include <iostream>
#include <iomanip>
#include "Game.h"
#include "Strategic.h"
#include "Simple.h"
#include "Food.h"
#include "Agent.h"
#include "Advantage.h"

using namespace std;

namespace Gaming
{
    const unsigned Game::MIN_WIDTH = 3;
    const unsigned Game::MIN_HEIGHT = 3;;
    const double Game::STARTING_AGENT_ENERGY = 20;
    const double Game::STARTING_RESOURCE_CAPACITY = 10;
    const unsigned int Game::NUM_INIT_AGENT_FACTOR = 4;
    const unsigned int Game::NUM_INIT_RESOURCE_FACTOR  =2;
    
    PositionRandomizer Game::__posRandomizer = PositionRandomizer();
    
    void Game::populate()  // populate the grid (used in automatic random initialization of a Game)
    {
        default_random_engine gen;
        uniform_int_distribution<int> d(0, __width * __height);
        
        __numInitAgents = (__width * __height) / NUM_INIT_AGENT_FACTOR;
        __numInitResources = (__width * __height) / NUM_INIT_RESOURCE_FACTOR;
        unsigned int numStrategic = __numInitAgents / 2;
        unsigned int numSimple = __numInitAgents - numStrategic;
        unsigned int numAdvantages = __numInitResources / 4;
        unsigned int numFoods = __numInitResources - numAdvantages;
        
        
        while (numStrategic > 0)
        {
            int i = d(gen);
            if (i != (__width * __height) && __grid[i] == nullptr)
            {
                Position pos(i / __width, i % __width);
                __grid[i] = new Strategic(*this, pos, STARTING_AGENT_ENERGY);
                numStrategic--;
            }
        }
        
        while (numFoods > 0)
        {
            int i = d(gen);
            if (i != (__width * __height) && __grid[i] == nullptr)
            {
                Position pos(i / __width, i % __width);
                __grid[i] = new Food(*this, pos, STARTING_RESOURCE_CAPACITY);
                numFoods--;
            }
        }
        
        while (numSimple > 0)
        {
            int i = d(gen);
            if (i != (__width * __height) && __grid[i] == nullptr)
            {
                Position pos(i / __width, i % __width);
                __grid[i] = new Simple(*this, pos, STARTING_AGENT_ENERGY);
                numSimple--;
            }
        }
        
        
        while (numAdvantages > 0)
        {
            int i = d(gen);
            if (i != (__width * __height) && __grid[i] == nullptr)
            {
                Position pos(i / __width, i % __width);
                __grid[i] = new Advantage(*this, pos, STARTING_RESOURCE_CAPACITY);
                numAdvantages--;
            }
        }
    }

    Game::Game() : __width(3), __height(3)
    {
        __numInitAgents = 0;
        __numInitResources = 0;
        
        __status = NOT_STARTED;
        __verbose = false;
        __round = 0;
        
        for (int count = 0; count < __height * __width; count++)
        {
            __grid.push_back(nullptr);
        }
        
    }
    
    Game::Game(unsigned width, unsigned height, bool manual): __width(width), __height(height) // note: manual population by default
    {
        if (height < MIN_HEIGHT || width < MIN_WIDTH)
        {
            throw InsufficientDimensionsEx(MIN_WIDTH, MIN_HEIGHT, width, height);
        }
        //__grid.resize(__width * __height);
        
        __numInitAgents = 0;
        __numInitResources = 0;
        __height = height;
        __width = width;
        __status = NOT_STARTED;
        __verbose = false;
        __round = 0;
        
        for (int count = 0; count < __height * __width; count++)
        {
            __grid.push_back(nullptr);
        }
        
        if (!manual)
        {
            populate();
        }
    }
   
   // Game &operator=(const Game &) = delete;
    Game::~Game()
    {
        for (int i = 0; i < __grid.size(); i++)
        {
            if (__grid[i] != nullptr)
            {
                delete __grid[i];
            }
        }
    }
    
    // getters
    //unsigned int getWidth() const { return __width; }
    //unsigned int getHeight() const { return __height; }
    unsigned int Game::getNumPieces() const
    {
        return getNumResources() + getNumAgents();
    }
    unsigned int Game::getNumAgents() const
    {
        return  getNumStrategic() + getNumSimple();
    }
    
    unsigned int Game::getNumSimple() const
    {
        unsigned int Num = 0;
        for (int i = 0; i < __grid.size(); ++i)
        {
            if(__grid[i] != nullptr)
            {
        
            if (__grid[i] -> getType() == SIMPLE)
            {
                Num++;
            }
            }
            
        }
        return Num;
    }
    unsigned int Game::getNumStrategic() const
    {
        unsigned int Num = 0;
        for (int i = 0; i < __grid.size(); ++i)
        {
            if(__grid[i] != nullptr)
            {
            if (__grid[i] -> getType() == STRATEGIC)
            {
                Num++;
            }
            }
        }
        return Num;
    }
    unsigned int Game::getNumResources() const
    {
        unsigned int Num = 0;
        for (int i = 0; i < __grid.size(); ++i)
        {
            if (__grid[i] != nullptr)
            {
                if (__grid[i] -> getType() == ADVANTAGE || __grid[i] -> getType() == FOOD)
                {
                    Num++;
                }
            }
        }
        return Num;
    }
    //Status getStatus() const { return __status; }
    //unsigned int getRound() const { return __round; }
    const Piece *Game::getPiece(unsigned int x, unsigned int y) const
    {
        if (y >= __width || x >= __height)
        {
            throw OutOfBoundsEx(__width, __height, x, y);
        }
        if (__grid[y + (x * __width)] == nullptr)
        {
            throw PositionEmptyEx(x, y);
        }
        return __grid[y + (x * __width)];
        
        
    }
    
    
    // grid population methods
    void Game::addSimple(const Position &position)
    {
       
        if ((position.x*__width + position.y) > __grid.size())
        {
            throw OutOfBoundsEx(__width, __height, position.x, position.y);
        }
        if (__grid[position.x * __width + position.y] != nullptr)
        {
            throw PositionNonemptyEx(position.x, position.y);
        }
        
        __grid[position.x * __width + position.y] = new Simple(*this, position,STARTING_AGENT_ENERGY);
       
    }
    
    
    void Game::addSimple(const Position &position, double energy) // used for testing only
    {
       
        if ((position.x*__width + position.y) > __grid.size())
        {
            throw OutOfBoundsEx(__width, __height, position.x, position.y);
        }
        if (__grid[position.x * (__width + position.y)] != nullptr)
        {
            throw PositionNonemptyEx(position.x, position.y);
            
            
        }
        __grid[position.x * (__width + position.y)] = new Simple(*this, position,energy);
    }
    
    
    
     void Game::addSimple(unsigned x, unsigned y)
     {
     Position p(x,y);
     this->addSimple(p);
     }
     
     void Game::addSimple(unsigned x, unsigned y, double energy)
     {
     Position p(x,y);
     this->addSimple(p,energy);
     }
    
    
    void Game::addStrategic(const Position &position, Strategy *s)
    {
        if((position.x*__width + position.y)>__grid.size())
        {
            throw OutOfBoundsEx(__width, __height, position.x, position.y);
        }
        
        if((__grid[position.x*__width + position.y])!=nullptr)
        {
            throw PositionNonemptyEx(position.x, position.y);
        }
        
        __grid[position.x*__width + position.y] = new Strategic(*this, position, STARTING_AGENT_ENERGY, s);
    }
    
    void Game::addStrategic(unsigned x, unsigned y, Strategy *s)
    {
        Position p(x,y);
        this -> addStrategic(p,s);
    }
    
     void Game::addFood(const Position &position)
     {
         if((position.x*__width + position.y) > __grid.size())
         {
            throw OutOfBoundsEx(__width, __height, position.x, position.y);
         }
     
         if((__grid[position.x * __width + position.y])!=nullptr)
         {
             throw PositionNonemptyEx(position.x,position.y);
         }
     
         __grid[position.x * __width + position.y] = new Food(*this, position, STARTING_RESOURCE_CAPACITY);
     }
     
    
    
    void Game::addFood(unsigned x, unsigned y)
    {
        Position p(x,y);
        this -> addFood(p);
    }
    
    void Game::addAdvantage(const Position &position)
    {
        if ((position.x * __width + position.y) > __grid.size())
        {
            throw OutOfBoundsEx(__width, __height, position.x, position.y);
        }
        if (__grid[position.x * __width + position.y] != nullptr)
        {
            throw PositionNonemptyEx(position.x, position.y);
            
            
        }
        __grid[position.x * __width + position.y] = new Advantage(*this, position, STARTING_RESOURCE_CAPACITY);

    }
    
    
    void Game::addAdvantage(unsigned x, unsigned y)
    {
        
        Position p(x,y);
        this->addAdvantage(p);
    }
    
    
    const Surroundings Game::getSurroundings(const Position &pos) const
    {
 
        Surroundings temp;
        int i = 0;
        for (int x = -1; x < 2; x++)
        {
            for (int y = -1; y < 2; y++)
            {
                if ((pos.x + x) < 0 || (pos.y + y) < 0 || (pos.x + x) > (__height - 1) || (pos.y + y) > (__width - 1))
                    temp.array[i] = INACCESSIBLE;
                else if (y == 0 && x == 0)
                    temp.array[i] = SELF;
                else if (__grid[(pos.x + x) * __width + (pos.y + y)] == nullptr)
                    temp.array[i] = EMPTY;
                else
                    temp.array[i] = __grid[(pos.x + x) * __width + (pos.y + y)]->getType();
                i++;
            }
        }
        return temp;
    }
    
    // gameplay methods
    const ActionType Game::reachSurroundings(const Position &from, const Position &to) // note: STAY by default
    {
     
        if (from.x > to.x)
        {
            if (from.y > to.y)
                return NW;
            else if (from.y < to.y)
                return NE;
            else
                return N;
        }
        else if (from.x < to.x)
        {
            if (from.y > to.y)
                return SW;
            else if (from.x < to.y)
                return SE;
            else
                return S;
        }
        else
        {
            if (from.y < to.y)
                return E;
            else if (from.y > to.y)
                return W;
            else
                return STAY;
        }
     
    
    }
 
    
    bool Game::isLegal(const ActionType &ac, const Position &pos) const
    {
        int x, y;
        x = pos.x;
        y = pos.y;
        switch (ac)
        {
            case E: y++;
                break;
            case NE: y++;
                     x--;
                break;
            case N: x--;
                break;
            case NW: y--;
                     x--;
                break;
            case W: y--;
                break;
            case SW: y--;
                     x++;
                break;
            case S: x++;
                break;
            case SE: x++;
                     y++;
                break;
            default:
                break;
        }
        Position p((unsigned )x, (unsigned)y);
        if (p.y < __width  && p.x < __height )
            return true;
        return false;
    }
    
    
    const Position Game::move(const Position &pos, const ActionType &ac) const // note: assumes legal, use with isLegal()
    {
        
        if (isLegal(ac, pos)) {
            int x, y;
            x = pos.x;
            y = pos.y;
            switch (ac) {
                case E: y++;
                    break;
                case NE: y++;
                        x--;
                    break;
                case N: x--;
                    break;
                case NW: y--;
                    x--;
                    break;
                case W: y--;
                    break;
                case SW: y--;
                    x++;
                    break;
                case S: x++;
                    break;
                case SE: x++;
                    y++;
                    break;
                default:
                    break;
            }
            Position p((unsigned )x, (unsigned)y);
            return p;
            
        }
        return pos;
        
    }
    void Game::round()  // play a single round
    {
        
        bool lost = false;
        bool win = false;
       
        ActionType act;
        Position pos;
        
        if (__status == NOT_STARTED)
        {
            __status = PLAYING;
        }
        for (int i = 0; i < __grid.size(); i++)
        {
            if (!__grid[i] -> getTurned())
            {
                act = __grid[i] -> takeTurn(getSurroundings(__grid[i] -> getPosition()));
                __grid[i] -> setTurned(true);
                pos = move(__grid[i] -> getPosition(), act);
            }
            else if (__grid[pos.x * (__width + pos.y)]!= nullptr)
            {
                (*__grid[pos.x * (__width +pos.y)]) * *__grid[i];
                if (!__grid[i] -> isViable())
                {
                    delete __grid[i];
                    lost = true;
                }
                else if (!__grid[pos.x * (__width +pos.y)] -> isViable())
                {
                    delete __grid[pos.x * (__width +pos.y)];
                    win = true;
                }
            }
            
            if (lost && win)
                __grid[pos.x * (__width +pos.y)] = nullptr;
            if (!lost)
                __grid[pos.x * (__width +pos.y)] = __grid[i];
            if (act != STAY)
                __grid[i] = nullptr;
        }
        for (int i = 0; i < __grid.size(); i++)
        {
            if (__grid[i] != nullptr)
            {
                __grid[i] -> age();
                __grid[i] -> setTurned(false);
                if (!__grid[i] -> isViable())
                {
                    delete __grid[i];
                }
            }
        }
        
        if (getNumResources() <= 0)
        {
            __status = OVER;
        }
        
        __round++;
    }
    void Game::play(bool verbose)   // play game until over
    {
        verbose = __verbose;
         __status = PLAYING;
        
        while (__status != 0)
        {
            round();
        }
        if (getNumResources() >0 && getNumPieces() > 1)
        {
            play(verbose);
        }
        
    }
    
    //        const Agent &winner(); // what if no winner or multiple winners?
    
    // Print as follows the state of the game after the last round:
    //
    // Round 1:
    // [F0   ][     ][T1   ]
    // [W2   ][     ][F3   ]
    // [     ][S4   ][     ]
    // Status: Playing...
    //
    // Round 5:
    // [     ][     ][     ]
    // [     ][T1   ][     ]
    // [     ][     ][     ]
    // Status: Over!
    //
     
     
    std::ostream &operator<<(std::ostream &os, const Game &game)
    {
        os << "Round " << game.__round << endl;
        for(int w = 0; w < game.__width ; w++)
        {
            for(int h = 0; h < game.__height; h++)
            {
                os << setw(5) << left << *(game.__grid[h *(game.__width + w)]);
               
            
            }
            
            os << endl;
            
        }
        
        if (game.__status == Game::NOT_STARTED)
        {
            os << "Status: Not started..." << endl;
        }
        else if (game.__status == Game::PLAYING)
        {
            os << "Status: Playing... " << endl;
        }
        else
        {
            os << "Status: over! " << endl;
        }
        return os;
    }
   
  
}
 