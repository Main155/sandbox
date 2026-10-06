#pragma once

#include "IO.h"
#include "error.h"
#include "log.h"

namespace IO
{
    enum class action_file
    {
        read_file,
        file_open,
        file_append,
        file_overwrite,
        file_delete
    };
    //File Selection & Create
    enum class file_stream { ofstream_file, ifstream_file };
    //file


    [[nodiscard]] inline bool file_exists_check(const std::string& path)             //Enter file name
    {
        if (!std::filesystem::exists(path))
        {    //file exist
            IO::Error("File does not exist\n", IO::error_option::File_error);
            return false; //error 
        }
        return true;
    }
    //Confirm whether the file exists

    inline bool fileopen(const std::string& file_name, file_stream opt = file_stream::ofstream_file)  //Create file name
    {
        switch (opt)
        {
        case file_stream::ofstream_file:
        {
            std::ofstream file(file_name);
            if (!file.is_open())
            {  //error
                return false;
            };
            return true;
        }
        break;
        case file_stream::ifstream_file:
        {
            std::ifstream in(file_name); //read
            if (!in.is_open()) { return false; }
            return true;
        }
        default:
            bool log_error_fileopen(IO::log("File_open  - Error : Parameter mismatch", IO::logger::Error));//error
            break;
        }
        return true;
    }
    //file

    [[nodiscard]] inline bool Direct_read_file(const std::string& file_name_read)
    {
        if (!file_exists_check(file_name_read))
        {
            IO::Error("File does not exist\n", IO::error_option::File_error);
            //error
            return false;
        }
        std::ifstream file(file_name_read);
        std::string line;
        while (std::getline(file, line)) //write
        {
            IO::print_function(line, IO::action_io::print_str);
            IO::print_function("\n");
        }
        file.close();
        return true;
    }
    //-Print- file


    [[nodiscard]] inline bool file_option(std::string_view input_f, action_file act_foption = action_file::file_open) //Guidance,File name,Parameter
    {
        std::string file_;
        std::string line_i;
        if (!IO::input_line(input_f, file_) || file_.empty())
        {              //input file_ error || empty
            IO::Error("No filename provided.\n", IO::error_option::empty);
            return false;//error
        }
        switch (act_foption)
        {
        case action_file::file_open : return fileopen(file_);
        case action_file::file_append:
        {
            if (!file_exists_check(file_)) //exists 
            {
                IO::Error("File does not exist\n", IO::error_option::File_error);
                return false;
            }
            std::ofstream file(file_, std::ios::app); //append
            if (!file.is_open())
            {
                IO::Error("File exception.\n", IO::error_option::File_error); //error
                return false;
            }
            while (IO::input_line(">", line_i) && line_i != "exit") //append
            {
                file << line_i << '\n';
            }
            file.close();
            return true;
        }
        //Additional


        case action_file::file_overwrite:
        {
            if (!file_exists_check(file_))
            {  //exists
                IO::Error("File does not exist\n", IO::error_option::File_error);
                return false;//error
            }
            std::ofstream file(file_, std::ios::trunc);
            if (!file.is_open())
            {
                IO::Error("Unable to open file.\n", IO::error_option::File_error);//error
                return false;
            }
            while (IO::input_line(">", line_i) && line_i != "exit") //write && exit
            {
                file << line_i << '\n';
            }
            file.close();
            return true;
        }
        //Override

        case action_file::read_file:
        {
            if (!Direct_read_file(file_))  //Direct_read_file (file name)
            {
                IO::Error("The file cannot be read.\n", IO::error_option::File_error);
                //error
                return false;
            }
            return true;
        }
        //Read

        case action_file::file_delete:
        {
            std::string T;
            if (!file_exists_check(file_))
            {
                IO::Error("File does not exist\n",IO::error_option::File_error);
                return false;
            }
            bool option_delete(IO::input_line("Confirm (T/F)", T));
            if (T == "T")
            {
                if (!std::filesystem::remove(file_))
                {   //File delete
                    IO::Error("Deletion failed.\n", IO::error_option::File_error);
                    return false;
                }
                IO::print_function("Delete file successful.\n"); //Successful
                bool ok_log_delete(IO::log("Delete file successful\n", IO::logger::Do_not_show_error));
                //log
                return true;
            }
            else if (T == "F")
            {
                IO::print_function("Cancel operation\n");
                return true;
            }
            else
            {
                IO::print_function("Invalid input", IO::action_io::print_error);//error
                return false;
            }
        }
        default:
            bool log_error_file_option(IO::log("File_option  - Error : Parameter mismatch", IO::logger::Error));
            //error
            return false; 
        }
    }
}

//file
