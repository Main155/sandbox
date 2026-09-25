module;

#include "IO.h"
#include "password.h"
#include <vector>
#include <map>
#include <functional>

export module Run;

import math;
import command;

namespace control
{
	static void Menu()
	{
		IO::print_function("--->~Menu bar=============\n");
		IO::print_function("----------Quick Command -----------Open----------------\n");
		IO::print_function("[MPS_]       LS               Terminal operation\n");
		IO::print_function("[ROOT]       SU               Superuser\n");
		IO::print_function("[MATH]       MATH             Math operation\n");
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
			{"MATH",[](const std::vector<std::string>&)
			{
				IO::clear_screen();
				math_main();
				  //math
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
	class run_
	{
	public:
		virtual ~run_() = default;
		virtual bool Start() = 0;
	};


	export class Run : public run_
	{
	private:
		std::string input;
	public:
		bool Start() override
		{
			Verification::Password_Verifcation_return();//Password verification
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