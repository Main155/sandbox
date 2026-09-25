#pragma once

#include "IO.h"
#include "find.h"
#include "MPS.h"
#include "password.h"
#include <functional>
#include <unordered_map>
#include <string>
#include <vector>

namespace ROOT
{
    inline std::unordered_map<std::string,
        std::function<void(const std::vector<std::string>&)>> ROOT_MAIN =
    {
        {"chpassword",[](const std::vector<std::string>&)
        {
            std::string binname = "password.bin";
            if (!PIN::Change_Password(binname))
            {
                return;
            }
        }},
        {"CR --open",[](const std::vector<std::string>& Mytxt_name)
        {
            std::string file_name;
            if (!IO::input_line("Please enter the file name:",file_name))
            {
                return;
            }
            (void)IO::fileopen(file_name);
        }},
        {"CR --overwrite",[](const std::vector<std::string>& Mytxt_overwrite)
        {
            if (!IO::file_option("Please enter the file name to overwrite:",IO::action_file::file_overwrite))
            {
                return;
            }
        }},
        {"CR --append",[](const std::vector<std::string>& Mytxt_append)
        {
            if (!IO::file_option("Please enter the file name to append:",IO::action_file::file_append))
            {
                return;
            }
        }},
        {"CR --delete",[](const std::vector<std::string>& Mytxt_delete)
        {
            if (!IO::file_option("Please enter the file name to delete:",IO::action_file::file_delete))
            {
                return;
            }
        }},
        { "CR --read",[](const std::vector<std::string>& Mytxt_read)
        {
            if (!IO::file_option("Please enter the file name to read:",IO::action_file::read_file))
            {
                return;
            }
        }},
    };
}

