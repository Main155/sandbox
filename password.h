#pragma once

#include "IO.h"
#include <string>
#include <sstream>
#include <fstream>

namespace PIN
{
    enum class password_option { read_password, password_change };
    //password

    inline std::string hash(const std::string& password) //Conversion
    {
        std::string salt = "root_cr_salt_v_AC_201_mps_rigorous_root_main_155_v0.1.0.1_1pc.cussoopl_2026";
        size_t h = std::hash<std::string>{}(std::string(salt) + password);
        std::ostringstream oss;
        oss << std::hex << h;    //hash
        return oss.str();
    }
    //Hash 

    [[nodiscard]] inline bool Change_Password(const std::string& password_file_name)//file name
    {
        std::string input_old_password, old_password, new_password, hash_in, hash_op;
        if (password_file_name.empty())
        {     //empty
            IO::Error("The file name is empty.\n", IO::error_option::empty);
            return false; //error
        }
        std::ifstream in(password_file_name);   
        if (!in.is_open()) { IO::Error("File error,Creating automatically...\n", IO::error_option::File_error); }  //No file
        std::getline(in, input_old_password);   //Size
        if (input_old_password.size() == 0)
        {    // size == 0
            std::ofstream openPIN(password_file_name, std::ios::trunc);
            IO::print_function("Please enter the original password: 123456\n");
            openPIN << hash("123456");   //Default is 123456
            openPIN.close();              //password now
        }
        in.close();
        input_old_password = IO::get_hidden_stars("Please enter your password");
        hash_in = hash(input_old_password);
        std::ifstream Align(password_file_name);  //file name
        std::getline(Align, old_password);
        Align.close();
        while (hash_in == old_password)
        {
            std::string Re;
            IO::print_function("Please enter a new password of 6 to 12 characters:\n");
            new_password = IO::get_hidden_stars("");               //Hide
            if (new_password.size() < 6 || new_password.size() > 12)
            {                               //size
                IO::print_function("Password length does not meet the requirements\n", IO::action_io::print_error);
                continue;
            }
            std::cout << "Re-enter:";         //Re
            Re = IO::get_hidden_stars("");
            if (!(new_password == Re))
            {
                IO::print_function("The new password does not match the previous entry!\n", IO::action_io::print_error);
                continue;  //error
            }
            std::string hs = hash(Re);
            std::ofstream input_PIN(password_file_name, std::ios::trunc);
            if (!input_PIN)
            {
                IO::Error("File exception\n", IO::error_option::File_error);
                return false;
            }         //error
            input_PIN << hs;
            input_PIN.close();
            IO::print_function("Creation successful!\n");
            bool log_change_password(IO::log("Change password.", IO::logger::Do_not_show));
            return true;
        }
        IO::print_function("Incorrect password entered\n", IO::action_io::print_error);
        return false;  //error
    }

    [[nodiscard]] inline bool password(const std::string& passwordfile)//Password file, Guidance, Password
    {
        std::string PIN, assignment;
        if (!IO::file_exists_check(passwordfile)) return false;
        PIN = IO::get_hidden_stars("Please enter your password");
        if (PIN.size() > 12 || PIN.size() < 6)
        {  //size
            IO::print_function("Input too long\n", IO::action_io::print_error);
            return false;
        }
        std::string hash_str{ hash(PIN) };
        std::ifstream in(passwordfile);
        if (!in.is_open())
        {
            IO::Error("File error\n", IO::error_option::File_error);
            return false;  //error
        }
        std::getline(in, assignment);
        in.close();
        if (hash_str == assignment) { return true; }
        IO::print_function("Incorrect password\n",IO::action_io::print_error);
        return false;
    }
    //Password processing 
}

namespace Verification
{
    inline bool  Password_Verifcation_return()
    {
        while (true)
        {
            const std::string file_name{ "password.bin" };
            if (!IO::file_exists_check(file_name))
            {
                IO::clear_screen();
                return true;
            }
            std::ifstream read(file_name);
            std::string line;
            read >> line;
            if (line.size() == 0)
            {
                return true;
            }
            if (!PIN::password(file_name))
            {
                continue;
            }
            return true;
        }
    }
}