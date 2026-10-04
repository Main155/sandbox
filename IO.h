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
#include <cstdlib>

#include "error.h"
#include "log.h"
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



    inline void clear_screen()
    {
        std::cout << "\033[2J\033[3J\033[H" << std::flush;//clear
        system("cls");
    }

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
}