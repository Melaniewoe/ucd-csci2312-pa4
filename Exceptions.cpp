//
//  Exceptions.cpp
//  PA4
//
//  Copyright © 2016 Melanie Woe. All rights reserved.
//


#include <iostream>
#include "Exceptions.h"

using namespace std;

namespace Gaming
{

    void GamingException::setName(string name)
    {
        __name = name;
    }
                

    std::ostream &operator<<(std::ostream &os, const GamingException &ex)
    {
        os << ex.__name<< endl;
        return os;
    }

    DimensionEx::DimensionEx(unsigned expWidth, unsigned expHeight, unsigned width, unsigned height)
    {
       
        expWidth = __exp_width;
        expHeight = __exp_height;
        width = __width;
        height = __height;
        setName("DimensionEx");
        
    }

    unsigned DimensionEx::getExpWidth() const
    {
        return __exp_width;
    }
    unsigned DimensionEx::getExpHeight() const
    {
        return __exp_height;
    }
    unsigned DimensionEx::getWidth() const
    {
        return __width;
    }
    unsigned DimensionEx::getHeight() const
    {
        return __height;
    }
    
    void InsufficientDimensionsEx::__print_args(std::ostream &os) const
    {
        os <<"Name: " << __name << endl;
        os << "Minimum height: " << getExpHeight() << "minimum width: " << getExpWidth() << endl;
        os << "Width: " << __width << "Height: " << __height << endl;
    }
    
    
    InsufficientDimensionsEx::InsufficientDimensionsEx(unsigned minWidth, unsigned minHeight, unsigned width, unsigned height):DimensionEx(minWidth, minHeight, width, height)
    {
        setName("InsufficientDimensionsEx");
    }
    
    void OutOfBoundsEx::__print_args(ostream &os) const
    {
        os <<"Name: " << __name << endl;
        os << "Minimum height: " << getExpHeight() << "minimum width: " << getExpWidth() << endl;
        os << "Width: " << __width << "Height: " << __height << endl;
        
    }
    
    OutOfBoundsEx::OutOfBoundsEx(unsigned maxWidth, unsigned maxHeight, unsigned width, unsigned height):
    DimensionEx(maxWidth, maxHeight, width, height)
    {
        setName("OutOfBoundsEx");
    }
    
    void PositionEx::__print_args(std::ostream &os) const
    {
        os << "Name: " << __name << endl;
        os << "x" << __x << "y " << __y << endl;
    }
    PositionEx::PositionEx(unsigned x, unsigned y)
    {
        __x = x;
        __y = y;
        setName("PositionEx");
    }
    PositionNonemptyEx::PositionNonemptyEx(unsigned x, unsigned y):PositionEx(x,y)
    {
        setName("PositionNonemptyEx");
    }
    PositionEmptyEx::PositionEmptyEx(unsigned x, unsigned y):PositionEx(x,y)
    {
        setName("PositionEmptyEx");
    }
    void PosVectorEmptyEx::__print_args(std::ostream &os) const
    {
        os << "Name: " << __name;
    }
    
    PosVectorEmptyEx::PosVectorEmptyEx() : GamingException()
    {
        setName("PosVectorEmptyEx");
    }
    
    
}


