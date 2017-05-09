#include "MapleParser.hpp"
#include "Filesystem.hpp"
#include "Logger.hpp"

#include <fstream>
#include <limits>

std::ifstream& GotoLine(std::ifstream& file, unsigned int num)
{
    file.seekg(std::ios::beg);

    for(size_t i = 0; i < num - 1; ++i)
	{
        file.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
    }

    return file;
}

// --PUBLIC

MapleParser::MapleParser(std::string app)
{
	logger::CUSTOM("MAPLE", "MapleParser initialised.");

	loadApp(app);
}

MapleParser::~MapleParser()
{
	logger::CUSTOM("MAPLE", "Finished.");
}

// --PRIVATE

bool MapleParser::loadApp(std::string appdir)
{
	logger::CUSTOM("MAPLE", "Attempting to load app '" + appdir + "'...");

	if (environment::filesystem::exists(appdir))
	{
		std::string dir = appdir + "//";

		if (environment::filesystem::exists(dir + "main.mpl"))
		{
			logger::CUSTOM("MAPLE", "Found main.mpl for `" + appdir + "`.");

			if (environment::filesystem::exists(dir + "settings.cfg"))
			{
				if (getAppInfo(dir + "settings.cfg"))
					return true;
				else
					return false;
			}
			else // settings.cfg
			{
				logger::CUSTOM("MAPLE", "No settings.cfg file was found for '" + appdir + "', aborting.");

				return false;
			}
		}
		else // main.mpl
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
}

int MapleParser::getAppInfo(std::string settingsfile)
{
	logger::CUSTOM("MAPLE", "Gathering app settings...");

	if (environment::filesystem::exists(settingsfile))
	{
		std::ifstream get_settings(settingsfile);

		if (get_settings.is_open())
		{
			GotoLine(get_settings, 1);
			std::string name;
			getline(get_settings, name);
			name.erase(0, 10);
			name.erase(name.end() - 1, name.end());

			logger::CUSTOM("MAPLE", name);
			app_name = name;

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
		logger::CUSTOM("MMAPLE-ERROR", "Could not find settings.cfg!");

		return false;
	}
}