#include "MapleParser.hpp"
#include "Filesystem.hpp"
#include "Logger.hpp"

namespace parser
{
	int getInfo(std::string thing)
	{
		if (environment::filesystem::exists(thing))
		{
			logger::CUSTOM("MAPLE", "the thing does exist!");
			return 1;
		}
		else
		{
			logger::CUSTOM("MAPLE", "the thing does not exist!");
			return 0;
		}
	}
}

MapleParser::MapleParser()
{

}

MapleParser::~MapleParser()
{

}
