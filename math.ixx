module;

#include "math.h"
#include "IO.h"

export module math;

namespace math_center
{
	static void math_Menu()
	{
		IO::print_function("Calculator      C\n");
		IO::print_function("Statistics      S\n");
	}//Menu
	static bool Calculator_d()
	{               //Calculator
		IO::clear_screen();
		while (true)
		{
			std::string write_;
			bool input_ok(IO::input_line("Calculation:", write_));
			if (write_ == "exit")return true;
			if (write_ == "cls")
			{
				IO::clear_screen();
				continue;
			}
			math::Process(write_);
		}
	}

	static bool Statistics_d()
	{                 //Statistics
		IO::clear_screen();
		std::vector<long double> Statistics_data;
		long double l;
		std::string data_input;
		while (true)
		{
			if (!IO::input_line("Data: ", data_input)) continue;
			if (data_input == "exit")return true;
			if (data_input == "cls")
			{
				IO::clear_screen();
				Statistics_data.clear();
				IO::print_function("cls           Reset and clear screen\n");
				continue;
			}
			try
			{
				std::istringstream iss(data_input);
				while (iss >> l)
				{
					Statistics_data.push_back(l);
				}
			}
			catch (const std::exception& e)
			{
				std::cerr << "ERR: Invalid input '" << data_input << "' - " << e.what() << "\n";
				continue;
			}
			math::Statistics(Statistics_data);
			continue;
		}
	}
}
export void math_main()
{
	math_center::math_Menu();
	while (true)
	{
		std::string math_command;
		bool option(IO::input_line("Please enter a math command:", math_command));
		if (math_command == "exit")return;
		if (math_command == "cls")
		{
			IO::clear_screen();
			math_center::math_Menu();
			continue;
		}
		if (math_command == "C")
		{
			math_center::Calculator_d();
			IO::clear_screen();
			math_center::math_Menu();
			continue;
		}
		else if (math_command == "S")
		{
			math_center::Statistics_d();
			IO::clear_screen();
			math_center::math_Menu();
			continue;
		}
		else
		{
			std::cerr << "ERR: Unknown math command '" << math_command << "'\n";
			continue;
		}
	}
}
