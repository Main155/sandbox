#pragma once
//Environment:
// GCC 9+ ,Clang 7+ ,VS 2019+  ,Xcode 10+ ,Support C++ 17...
#include <iostream>  
#include <string_view>
#include <string>
#include <fstream>
#include <filesystem>
#include <limits>
#include <sstream>

#ifdef _WIN32
#include <conio.h>
#include <windows.h> //windows
#else
#include <termios.h>  //linux
#include <unistd.h>   //mac os
#endif

namespace IO
{
    enum class action_io { print_str, print_error };
    //Print & Input 

    enum class action_file { read_file, file_open, file_append, file_overwrite, file_delete };
    //File Selection & Create

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

    enum class logger { Error, Ordinary, Do_not_show, Do_not_show_error };
    //logger

    enum class file_stream { ofstream_file, ifstream_file };
    //file

    enum class error_option
    {
        Input_error,
        File_error,
        empty,
        Display_error
    };
    //error


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


    inline void Error(std::string_view err, error_option option_err)
    {
        switch (option_err)
        {
        case error_option::Input_error:
        { std::cerr << "[Input error]" << err; } //Input error
        break;
        case error_option::File_error:
        { std::cerr << "[File_error]" << err; } //File error
        break;
        case error_option::empty:
        { std::cerr << "[Empty]" << err; }       //Empty
        break;
        case error_option::Display_error:
        { std::cerr << "[Error]" << err; }      //Incorrect label
        break;
        default:
            bool log_error_Error_option(log("Error option  - Error : Parameter mismatch", logger::Error)); //error
            return;
        }
    }
    //Error option

    inline void clear_screen()
    {
        std::cout << "\033[2J\033[3J\033[H" << std::flush;//clear
    }
    //Clear Screen


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

    inline void line_error_clear()
    {
        std::cin.clear();
        std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
    }
    //Correct input errors

//========================================================

// Hidden input handling

    namespace internal
    {
#ifndef _WIN32
        struct TerminalGuard                    //Liunx
        {
            termios old{};
            bool ok{ false };

            TerminalGuard() {
                ok = (tcgetattr(STDIN_FILENO, &old) == 0);
                if (ok)
                {
                    termios raw = old;
                    raw.c_lflag &= ~(ICANON | ECHO);
                    tcsetattr(STDIN_FILENO, TCSANOW, &raw);
                }
            }
            ~TerminalGuard() {
                if (ok) tcsetattr(STDIN_FILENO, TCSANOW, &old);
            }
        };


        inline char getch() {
            char ch;
            if (read(STDIN_FILENO, &ch, 1) != 1) return 0;
            return ch;
        }

#else
        struct TerminalGuard
        {
            DWORD old{};
            HANDLE h{ GetStdHandle(STD_INPUT_HANDLE) };
            TerminalGuard()
            {
                GetConsoleMode(h, &old);
                SetConsoleMode(h, old & ~(ENABLE_ECHO_INPUT | ENABLE_LINE_INPUT));
            }
            ~TerminalGuard() { SetConsoleMode(h, old); }
        };
        inline char getch() { return _getch(); }                    //Windows
#endif

    } // namespace internal
    [[nodiscard]] inline std::string get_hidden_stars(std::string_view prompt)
    {
        std::cout << prompt << '\n' << std::flush;
#ifndef _WIN32
        internal::TerminalGuard guard;      //Hide
#endif
        std::string result;
        while (true)
        {
            char ch = internal::getch();
            if (ch == '\n' || ch == '\r')
            {
                std::cout << std::flush;
                break;
            }
            else if (ch == '\b' || ch == 127)
            {
                if (!result.empty())
                {
                    result.pop_back();
                    std::cout << "\b \b" << std::flush;
                }
            }
            else if (ch == 3) { throw std::runtime_error("Cancelled"); }
            else
            {
                result.push_back(ch);            //Hide
                std::cout << "*" << std::flush; //Display *
            }
        }
        std::cout << '\n';
        return result;
    }

    //Hidden feature
    //============================================================



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

    inline void print_function(std::string_view str, action_io act = action_io::print_str)//Print & Parameter
    {
        if (str.empty())
        {
            Error("Error: Empty string provided.\n", error_option::empty);//error
            return;
        }
        switch (act)
        {
        case action_io::print_str: std::cout << str; // True (No parameters)
            break;
        case action_io::print_error: Error(str, error_option::Display_error);
            break; //error
        }
    }
    //print

    [[nodiscard]] inline bool input_line(std::string_view print_msg, std::string& input_)           //Guidance,Input
    {
        if (print_msg.empty())
        {            //empty   
            Error("Empty string provided.\n", error_option::empty); //error
            return false;
        }
        print_function(print_msg);    //print
        if (!std::getline(std::cin, input_))
        {
            print_function("Input error.\n", action_io::print_error);
            line_error_clear();    //Clean up
            return false;
        }
        return true;
    }
    //print : input

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
            bool log_error_file_option(log("File_option  - Error : Parameter mismatch", logger::Error));
            //error
            return false;
        }
    }
}