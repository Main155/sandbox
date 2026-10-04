#pragma once

#include "IO.h"

namespace IO
{
    enum class Color
    {
        Black = 30,
        Red = 31,
        Green = 32,
        Yellow = 33,
        Blue = 34,
        Magenta = 35,
        Cyan = 36,
        White = 37,
        BrightBlack = 90,
        BrightRed = 91,
    };
    //Color
    
    inline void set_color(Color fg)//Color settings
    {
        std::cout << "\033[" << static_cast<int>(fg) << "m";  
    }
    //Color set


    inline void reset_color() //Color Reset
    {
        std::cout << "\033[0m";
    }
    //reset_color
} 


