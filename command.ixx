module;

#include "IO.h"
#include "root.h"
#include "MPS.h"
#include "find.h"

export module command;

namespace find_command
{ 
	inline bool find_MPS(const std::vector<std::string>& find_X) //find mps 
	{
		if (find_X.empty())return false; //empty
		auto it_1 = MPS::ROOT_MPS.find(find_X[0]); 
		if (it_1 != MPS::ROOT_MPS.end())
		{
			it_1->second(find_X);
			return true;  //true
		}
		return false; //error
	}
	static bool command_find(const std::string& MAIN_ROOT_FIND)
	{   

		std::istringstream iss(MAIN_ROOT_FIND);
		std::vector <std::string> find_ro;
		std::string token;
		while (iss >> token)
		{
			find_ro.push_back(token);
		}
		if (find_ro.empty())
		{
			IO::print_function("Empty\n");
			return false;
		}
		auto it_rx = ROOT::ROOT_MAIN.find(find_ro[0]);
		if (it_rx != ROOT::ROOT_MAIN.end())
		{  //find ROOT    file >> root.h
			it_rx->second(find_ro);
			return true;
		}
		if (!find_MPS(find_ro))
		{
			return false;  //error
		}
		return true;
	}

	//help          ----file >>find.h
	static void help(const std::string& help_mps)
	{
		IO::print_function("Error:Command not found\n", IO::action_io::print_error);      
		IO::print_function("\nROOT:\n");
		InputHandler::check_and_suggest(help_mps, ROOT::ROOT_MAIN);  //root

		IO::print_function("\nMPS:\n");
		InputHandler::check_and_suggest(help_mps, MPS::ROOT_MPS);     //mps
	}
}

export namespace command
{
	bool root()  //root command
	{
		IO::clear_screen();
		while (true)
		{
			std::string root_command;
			if (!IO::input_line("\n[ROOT]command:", root_command))return false;
			if (root_command == "exit")   //exit
			{
				IO::clear_screen();
				return true;
			}
			auto it_1 = ROOT::ROOT_MAIN.find(root_command);
			if (it_1 != ROOT::ROOT_MAIN.end())
			{
				std::vector<std::string> arge = { root_command };
				it_1->second(arge);
				continue;
			}
			std::istringstream iss(root_command);
			std::vector<std::string> token;
			std::string t;
			while (iss >> t) token.push_back(t);
			if (find_command::find_MPS(token)) { continue; }   //command find

			//help
			find_command::help(root_command);
			continue;
		}
	}

	bool mps()   //find mps
	{
		IO::clear_screen();   //claer screen
		while (true)
		{
			std::string mps_command;
			if (!IO::input_line("\ncommand:", mps_command))return false;
			if (mps_command == "exit")  //exit
			{
				IO::clear_screen();
				return true;
			}
			if (mps_command == "sudo su" || mps_command == "su")   //root user
			{
				root();
				continue;
			}
			std::istringstream iss(mps_command);
			std::vector<std::string> tokens;
			std::string tok;
			while (iss >> tok) tokens.push_back(tok);

			auto it_rx = ROOT::ROOT_MAIN.find(tokens[0]);   //block
			if (it_rx != ROOT::ROOT_MAIN.end())
			{
				IO::print_function("Please switch to the root user.\n", IO::action_io::print_error);
				continue;
			}
			if (find_command::find_MPS(tokens)) { continue; }  //find mps

			if (find_command::command_find(mps_command)) { continue; }  

			//help
			find_command::help(mps_command);
			continue;
		}
	}
}