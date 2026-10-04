#pragma once

#include "IO.h"

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

    
    [[nodiscard]] inline bool file_exists_check(const std::string& path)             //Enter file name
    {
        if (!std::filesystem::exists(path))
        {    //file exist
            Error("File does not exist\n", error_option::File_error);
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
            bool log_error_fileopen(log("File_open  - Error : Parameter mismatch", logger::Error));//error
            break;
        }
    }
    //file

    
    [[nodiscard]] inline bool Direct_read_file(const std::string& file_name_read)
    {
        if (!file_exists_check(file_name_read))
        {
            Error("File does not exist\n", error_option::File_error);
            //error
            return false;
        }
        std::ifstream file(file_name_read);
        std::string line;
        while (std::getline(file, line)) //write
        {
            print_function(line, action_io::print_str);
            print_function("\n");
        }
        file.close();
        return true;
    }
    //-Print- file


    [[nodiscard]] inline bool file_option(std::string_view input_f, action_file act_foption = action_file::file_open) //Guidance,File name,Parameter
    {
        std::string file_;  
        std::string line_i;
        if (!input_line(input_f, file_) || file_.empty())
        {              //input file_ error    & empty
            Error("No filename provided.\n", error_option::empty);
            return false;//error
        }
        switch (act_foption)
        {
        case action_file::file_open: return fileopen(file_);
        case action_file::file_append:
        {
            if (!file_exists_check(file_)) //exists 
            {
                Error("File does not exist\n", error_option::File_error);
                return false;
            }
            std::ofstream file(file_, std::ios::app); //append
            if (!file.is_open())
            {
                Error("File exception.\n", error_option::File_error); //error
                return false;
            }
            while (input_line("=", line_i) && line_i != "exit") //append
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
                Error("File does not exist\n", error_option::File_error);
                return false;//error
            }
            std::ofstream file(file_, std::ios::trunc);
            if (!file.is_open())
            {
                Error("Unable to open file.\n", error_option::File_error);//error
                return false;
            }
            while (input_line("=", line_i) && line_i != "exit") //write && exit
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
                Error("The file cannot be read.\n", error_option::File_error);
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
                Error("File does not exist\n", error_option::File_error);
                return false;
            }
            bool option_delete(IO::input_line("Confirm (T/F)", T));
            if (T == "T")
            {
                if (!std::filesystem::remove(file_))
                {   //File delete
                    Error("Deletion failed.\n", error_option::File_error);
                    return false;
                }
                print_function("Delete file successful.\n"); //Successful
                bool ok_log_delete(log("Delete file successful\n", logger::Do_not_show_error));
                //log
                return true;
            }
            else if (T == "F")
            {
                print_function("Cancel operation\n");
                return true;
            }
            else
            {
                print_function("Invalid input", action_io::print_error);//error
                return false;
            }
        }
        default:
            bool log_error_file_option(IO::log("File_option  - Error : Parameter mismatch", logger::Error));
            //error
            return false;
        }
    }
}