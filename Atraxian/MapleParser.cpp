#include "MapleParser.hpp"
#include "Filesystem.hpp"
#include "Logger.hpp"

namespace parser
{
	bool loadApp(std::string appdir)
	{
		if (environment::filesystem::exists(appdir))
		{
			std::string dir = appdir + "//";

			if (environment::filesystem::exists(dir + "main.mpl"))
			{
				logger::CUSTOM("MAPLE", "Found main.mpl for " + appdir + ".");

				return 1;
			}
		}
		else
		{
			logger::CUSTOM("MAPLE", "Could not find main.mpl for " + appdir + ".");

			return 0;
		}
	}
}
