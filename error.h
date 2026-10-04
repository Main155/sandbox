#pragma once

#include "IO.h"
#include "log.h"

namespace IO
{
    enum class error_option
    {
        Input_error,
        File_error,
        empty,
        Display_error,
    };
    //error
    
    inline void Error(std::string_view err, error_option option_err)
    {
        switch (option_err)
        {
        case error_option::Input_error:
        { std::cerr << "[Input error]" << err; } //Input error
        break;
        case error_option::File_error:
        { std::cerr << "[File error]" << err; } //File error
        break;
        case error_option::empty:
        { std::cerr << "[Empty]" << err; }       //Empty
        break;
        case error_option::Display_error:
        { std::cerr << "[Error]" << err; }      //Incorrect label
        break;
        default:
            bool log_error_Error_option(IO::log("Error option  - Error : Parameter mismatch", IO::logger::Error)); //error
            return;
        }
    }
}