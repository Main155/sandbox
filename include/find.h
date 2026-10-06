#pragma once

#include "IO.h"
#include "MPS.h"
#include "color.h"
#include "root.h"

namespace InputHandler
{	   //find command
    inline bool check_and_suggest(const std::string & name ,const std::string& input,
        const std::unordered_map<std::string,
        std::function<void(const std::vector<std::string>&)>>&cmd_map)
    {
        std::vector<std::string> matches;
        for (const auto& [cmd, _] : cmd_map)
        {
            if (cmd.find(input) != std::string::npos)
            {
                matches.push_back(cmd);
                if (matches.size() >= 3) break;
            }
        }

        if (matches.empty())
        {   //empty
            for (const auto& [cmd, _] : cmd_map)
            {
                if (cmd.compare(0, input.size(), input) == 0)
                {
                    matches.push_back(cmd);
                    if (matches.size() >= 3) break;
                }
            }
        }

        if (!matches.empty())
        {
			IO::set_color(IO::Color::Yellow);
            IO::print_function("Did you mean:\n");
            IO::print_function(name);
            for (const auto& m : matches)
            {               //print
                std::cout << "   " << m << '\n';
            }
			IO::reset_color();
            return true;
        }
        else
        {
            return false;
        }
    }
}
// namespace calibrate
