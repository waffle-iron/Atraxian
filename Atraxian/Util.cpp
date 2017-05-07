#include "Util.hpp"
#include "Filesystem.hpp"

#include <ctime>

namespace environment {

namespace util
{
	std::string getTimestamp()
	{
		time_t $time = time(0);

		int seconds = $time % 60;
		$time /= 60;

		int minutes = $time % 60;
		$time /= 60;

		int hours = $time % 24;
		$time /= 24;

		std::string seconds_s(std::to_string(seconds));
		std::string minutes_s(std::to_string(minutes));
		std::string hours_s(std::to_string(hours));

		if (seconds < 10)
			seconds_s.insert(0, "0");

		if (minutes < 10)
			minutes_s.insert(0, "0");

		if (hours < 10)
			hours_s.insert(0, "0");

		std::string timestamp = hours_s + ":" + minutes_s + ":" + seconds_s;

		return timestamp;
	}

	bool fs_ready()
	{
		if (filesystem::exists(".//root"))
			return true;
		else
			return false;
	}

	void ready_fs()
	{
		filesystem::create_dir("root", ".//");
	}
}

} // enviroment
