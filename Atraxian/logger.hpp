#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <string>

namespace logger
{
	void INFO(std::string output);

	void INFO(std::string output, int);

	void WARNING(std::string output);

	void ERROR(std::string output);

	void SILENT(std::string output, std::string type);

	void BREAK();
}

#endif /* LOGGER_HPP */
