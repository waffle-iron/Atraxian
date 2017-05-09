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
	sf::Vector2f pane_dimensions;

private:
	bool loadApp(std::string appdir);
	int getAppInfo(std::string settingsfile);
};

#endif /* MAPLE_PARSER_HPP */
