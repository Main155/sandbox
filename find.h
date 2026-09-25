#pragma once

#include "IO.h"
#include "MPS.h"
#include "root.h"
#include <unordered_map>
#include <functional>
#include <vector>
#include <string>

namespace InputHandler
{	   //find command
    inline void check_and_suggest(const std::string& input,
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
            IO::print_function("Did you mean:\n");
            for (const auto& m : matches)
            {               //print
                IO::print_function(m);
                IO::print_function("\n");
            }
        }
        else
        {
            IO::print_function("No similar commands found\n", IO::action_io::print_error);  //error
        }
    }
}
// namespace calibrate