#include "MapleParser.hpp"
#include "Filesystem.hpp"
#include "Logger.hpp"

#include <fstream>

int getAppInfo(std::string settingsfile)
{
	if (environment::filesystem::exists(settingsfile))
	{
		std::ifstream get_settings(settingsfile);

		if (get_settings.is_open())
		{
			return true;
		}
		else
		{
			logger::CUSTOM("MMAPLE-ERROR", "Failed to open settings file!");

			return false;
		}
	}
	else
	{
		return false;
	}
}

namespace parser
{
	bool loadApp(std::string appdir)
	{
		logger::CUSTOM("MAPLE", "Attempting to load app '" + appdir + "'...");

		if (environment::filesystem::exists(appdir))
		{
			std::string dir = appdir + "//";

			if (environment::filesystem::exists(dir + "main.mpl"))
			{
				logger::CUSTOM("MAPLE", "Found main.mpl for `" + appdir + "`.");

				if (environment::filesystem::exists(dir + "main.mpl"))
				{
					logger::CUSTOM("MAPLE", "Gathering settings...");

					return true;
				}
				else
				{
					logger::CUSTOM("MAPLE", "No settings.cfg file was found for '" + appdir + "', aborting.");

					return false;
				}
			}
			else
			{
				logger::CUSTOM("MAPLE", "Folder for `" + appdir + "` was found, but main.mpl was not. Aborting.");

				return false;
			}
		}
		else
		{
			logger::CUSTOM("MAPLE", "Could not find main.mpl for `" + appdir + "`.");

			return false;
		}

		logger::ERROR("This code should never have had the chance to be executed! (Maple)");
	}
}
