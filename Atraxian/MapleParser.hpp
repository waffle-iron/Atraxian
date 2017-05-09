#ifndef MAPLE_PARSER_HPP
#define MAPLE_PARSER_HPP

#include <SFML\System\Vector2.hpp>
#include <string>

class MapleParser
{
public:
	MapleParser(std::string app);
	~MapleParser();

	std::string app_name;
	std::string app_description;
	sf::Vector2f app_dimensions;

private:
	bool loadApp(std::string appdir);
	std::string getAppName(std::string settingsfile);
	std::string getAppDescription(std::string settingsfile);
	sf::Vector2f getAppDimensions(std::string settingsfile);
	void createApp();
};

#endif /* MAPLE_PARSER_HPP */
