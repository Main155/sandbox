#pragma once

#include "IO.h"

namespace IO
{
    enum class logger
    { 
        Error,
        Ordinary,
        Do_not_show,
        Do_not_show_error
    };

    [[nodiscard]] inline bool log(std::string_view val, logger options = logger::Ordinary)   //log 
    {
        const std::string& name{ "io_logger.log" };    //log file
        std::ofstream open(name, std::ios::app);
        if (!open.is_open())
        {
            std::cerr << "File error\n";   //error
            return false;
        }
        switch (options)
        {
        case logger::Ordinary: { std::cout << val; open << val << '\n'; open.close(); } //Output logs and write logs
                     break;
        case logger::Error: { std::cout << val; open << "[ERR]:" << val << '\n';open.close(); } // 
                     break;
        case logger::Do_not_show: { open << val << '\n';open.close(); }                 //write log
                       break;                                                
        case logger::Do_not_show_error: { open << "[ERR]:" << val << '\n';open.close(); }
                      break;
        default:
            break;
        }
        return true;
    }
    //log
}
