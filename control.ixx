module;

#include "IO.h"
#include "password.h"
#include <vector>
#include <map>
#include <functional>

export module Run;

import command;

namespace control
{
	static void Menu()
	{
		IO::print_function("--->~Menu bar=============\n");
		IO::print_function("----------Quick Command -----------Open----------------\n");
		IO::print_function("[MPS_]       LS               Terminal operation\n");
		IO::print_function("[ROOT]       SU               Superuser\n");
		IO::print_function("[MPS_]       cls              Clear screen\n");
		IO::print_function("[STBN]       STBN             Shutdown\n");
	}
	//menu

	static bool Table(const std::string & token)
	{
		std::map<std::string,
			std::function<void(const std::vector<std::string>&)>> Table_option
		{
			{"LS",[](const std::vector<std::string>&)
			{                           //Terminal command
				command::mps();
			}},
			{"SU",[](const std::vector<std::string>&)
			{
				command::root();   //root
			}},
			{"cls",[](const std::vector<std::string>&)
			{
				IO::clear_screen();   //cls
			}}
		};

		auto Transmission = Table_option.find(token);
		std::vector<std::string> A;
		A.push_back(token);
		if (Transmission != Table_option.end())
		{
			Transmission->second(A);
			return true;   //find
		}
		return false;
	}

}

export namespace BOOT
{
	export class Run
	{
	private:
		std::string input;
	public:
		~Run() = default;
		bool Start()
		{
			Verification::Password_Verifcation_return();
			IO::clear_screen();
			control::Menu();
			while (true)
			{
				if (!IO::input_line("\nPlease enter a menu command:", input))
				{
					continue;
				}
				if (input == "STBN")
				{    //Shutdown
					IO::clear_screen();
					return true;
				}
				if (!control::Table(input))
				{  //find 
					IO::print_function("Command error\n", IO::action_io::print_error);
					continue;
				}
				IO::clear_screen();
				control::Menu();
				continue;
			}
		}
	};
}