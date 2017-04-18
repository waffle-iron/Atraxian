#include <fstream>
#include <iostream>
#include <string>

#include "Environment.hpp"

void write_log(const std::string output)
{
	std::ofstream log("environment.log", std::ios::app);

	if (log.is_open())
	{
		log << output << std::endl;

		log.close();

		if (log.bad())
		{
			std::cerr << "failed to write to log!" << std::endl;
		}
	}
	else
	{
		std::cerr << "\n" << "unable to open log file for writing!" << std::endl;
	}
}

namespace logger
{
	void INFO(std::string output)
	{
		output = environment::getTimestamp() + " INFO: " + output;
		std::cout << output << std::endl;

		write_log(output);
	}

	void WARNING(std::string output)
	{
		output = environment::getTimestamp() + " WARNING: " + output;
		std::cout << output << std::endl;

		write_log(output);
	}

	void ERROR(std::string output)
	{
		output = environment::getTimestamp() + " ERROR: " + output;
		std::cout << output << std::endl;

		write_log(output);
	}

	void SILENT(std::string output)
	{
		output = environment::getTimestamp() + " SILENT: " + output;

		write_log(output);
	}
}
