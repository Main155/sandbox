#pragma once

#include "IO.h"  //IO.h  
#include <unordered_map>
#include <string>
#include <vector>
#include <functional>
#include <filesystem>
#include <chrono>
#include <thread>

namespace MPS
{
	inline std::unordered_map<std::string,
		std::function<void(const std::vector<std::string>&)>> ROOT_MPS =
	{
		{"mkdir", [](const std::vector<std::string>& args)   // Create directory
		{
			if (args.size() < 2)
			{ //Length
				IO::print_function("Usage: mkdir <dirname>\n");
				return; //Prompt
			}
			std::error_code ec;
			if (std::filesystem::create_directory(args[1], ec))
			{
			   IO::print_function("Directory created.\n");
			   bool log_mkdir_(IO::log(args[1],IO::logger::Do_not_show));
			   bool log_mkdir_ok(IO::log("Directory created.", IO::logger::Do_not_show));
			}
			else
			{
				IO::print_function("Error: ",IO::action_io::print_error); //error
				IO::print_function(ec.message());
				IO::print_function("\n");
			}
		}},

		{"ls",[](const std::vector<std::string>&)//List files
		{
			for (const auto& entry : std::filesystem::directory_iterator(std::filesystem::current_path()))
			{
			   IO::print_function(entry.path().filename().string());
			   IO::print_function("\n");                //print
			   bool log_ls_(IO::log("Ls path", IO::logger::Do_not_show)); //log
			}
		}},

		{"pwd", [](const std::vector<std::string>&)
		{
			std::error_code ec;                    // Show current path
			auto path = std::filesystem::current_path(ec);
			if (ec)
			{
				IO::print_function("",IO::action_io::print_error);   //error
				IO::print_function(ec.message());
				IO::print_function("\n");
				return;
			}
			IO::print_function(path.string());  //print
			IO::print_function("\n");
			bool log_pwd_(IO::log("Print path", IO::logger::Do_not_show)); //log
		}},

		{"help", [](const std::vector<std::string>&)   //help
		{
			IO::print_function("Available commands:\n");
			IO::print_function("  mkdir <dir>    Create directory\n");
			IO::print_function("  ls             List files\n");
			IO::print_function("  pwd            Show current path\n");
			IO::print_function("  touch <file>   Create empty file\n");
			IO::print_function("  cat <file>     Show file content\n");
			IO::print_function("  rm <file>      Remove file\n");
			IO::print_function("  rmdir <dir>    Remove empty directory\n");
			IO::print_function("  cd <path>      Change directory\n");
			IO::print_function("  echo <text>    Print text\n");
			IO::print_function("  whoami         Show current user\n");
			IO::print_function("  date           Show current date\n");
			IO::print_function("  cls            Clear screen\n");
			IO::print_function("  sleep <s>      Sleep for seconds\n");
		}},

		{"cls",[](const std::vector<std::string>&)  //Clear screen
		{
			IO::clear_screen();                //IO.h
		}},

		{"sleep", [](const std::vector<std::string>& args)
		{
		if (args.size() < 2) {            //Length
			IO::print_function("Usage: sleep <seconds>\n",IO::action_io::print_error);
			return;
		}
		try {
			long long time = std::stoll(args[1]);
			if (time <= 0)
			{    //Length
				IO::print_function("positive number required\n", IO::action_io::print_error);
				return;
			}
			std::this_thread::sleep_for(std::chrono::seconds(time));   //s
			IO::print_function("Done\n");
			bool log_sleep_(IO::log("Sleep s", IO::logger::Do_not_show)); //log
			}
			catch (const std::exception&)
			{
			IO::print_function("invalid number\n", IO::action_io::print_error);  //error
		}
		}},

		{"touch", [](const std::vector<std::string>& args)  //create
		{
			if (args.size() < 2)
			{
				IO::print_function("Usage: touch <filename>\n",IO::action_io::print_error);
				return;
			}
			if (!IO::fileopen(args[1]))
			{
				return;
			}
			IO::print_function("File created\n");
		}},

		{"cd", [](const std::vector<std::string>& args) // Change directory
		{
		   if (args.size() < 2) {
// Length
		   IO::print_function("Usage: cd <path>\n",IO::action_io::print_error);
		   return;
		}
		   std::error_code ec;
		   std::filesystem::current_path(args[1], ec);
		   if (ec)
		   {
			   IO::print_function("",IO::action_io::print_error);
			   IO::print_function(ec.message(),IO::action_io::print_error);
			   IO::print_function("\n");
		   }
		   else
		   {
			   IO::print_function("Changed directory to\n");
			   IO::print_function(args[1]);
		   }
		}},

		{"cat", [](const std::vector<std::string>& args)
		{    //Show file content
			if (args.size() < 2)    
			{
				IO::print_function("Usage: cat <filename>\n",IO::action_io::print_error);
				return;
			}
			if (!IO::file_exists_check(args[1]))
			{
				IO::print_function("The file does not exist.\n",IO::action_io::print_error);
				return;
			}
			bool ok_read(IO::Direct_read_file(args[1]));
		}},

		{"rm", [](const std::vector<std::string>& args)
		{   //delete file
			if (args.size() < 2)
			{
				IO::print_function("Usage: rm <filename>\n",IO::action_io::print_error);
				return;
			}
			if (!IO::file_exists_check(args[1]))
			{
				IO::print_function("File does not exist\n",IO::action_io::print_error);
				return;
			}
			std::error_code ec;
			std::string option;
			bool rm_option(IO::input_line("High-risk operation, please enter T/F: ",option));
			if (option == "F")
			{
				IO::print_function("Operation canceled successfully\n");  
				return;   //F
			}
			if (option == "T" && std::filesystem::remove(args[1], ec))
			{
				IO::print_function("Removed\n");
				bool log_rm_(IO::log("rm file", IO::logger::Do_not_show));
				return;
			}
			else
			{
				IO::print_function("Input\n",IO::action_io::print_error);  //error
			}
		}},

		{"rmdir", [](const std::vector<std::string>& args)
		{     //delete dir
			if (args.size() < 2)
			{
				//Length
				IO::print_function("rmdir <dir>\n",IO::action_io::print_error);
				return;
			}
			std::error_code ec;
			if (std::filesystem::remove(args[1], ec))
			{
				IO::print_function("Directory removed");
				bool log_rmdir(IO::log("Directory removed", IO::logger::Do_not_show));
			}
			else
			{
				IO::print_function("",IO::action_io::print_error);
				IO::print_function(ec.message());
				IO::print_function("\n"); //error
			}
		}},
		{"echo", [](const std::vector<std::string>& args)
		{
			std::string out;
			for (size_t i = 1; i < args.size(); ++i) out += args[i] + " ";
			IO::print_function(out);
			IO::print_function("\n");
		}},

		{"whoami", [](const std::vector<std::string>&)
		{
			IO::print_function("mps\n");   //user 
		}},
	};
}
//Regular user
