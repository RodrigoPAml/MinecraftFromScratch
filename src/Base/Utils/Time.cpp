#include <BuildCraft.hpp>
#include "Time.hpp"

namespace BuildCraft
{
	namespace Base
	{
		double Time::GetTimestamp()
		{
			return glfwGetTime();
		}

		Date Time::GetDate()
		{
			time_t now = time(0);

			tm* ltm = localtime(&now);

			Date date = {1900 + ltm->tm_year, 1 + ltm->tm_mon, ltm->tm_mday, ltm->tm_hour,  ltm->tm_min, ltm->tm_sec};

			return date;
		}

		std::ostream& operator<<(std::ostream& os, const Date& date)
		{
			os << date.day << '/' << date.month << '/' << date.year << ' ' << date.hour << ':' << date.minute << ':' << date.second;

			return os;
		}
	}
}
