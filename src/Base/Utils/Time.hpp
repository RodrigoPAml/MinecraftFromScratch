#pragma once
#include <BuildCraft.hpp>

namespace BuildCraft
{
	namespace Base
	{
		struct Date
		{
			unsigned int year = 0;

			unsigned short month = 0;

			unsigned short day = 0;

			unsigned short hour = 0;

			unsigned short minute = 0;

			unsigned short second = 0;

			std::string to_string() const
			{
				return std::to_string(this->day) + '/' + std::to_string(this->month) + '/' + std::to_string(this->year) + ' ' + std::to_string(this->hour) + ':' + std::to_string(this->minute) + ':' + std::to_string(this->second);
			}
		};

		std::ostream& operator<<(std::ostream& os, const Date& date);

		class Time
		{
		public:
			static double GetTimestamp();

			static Date GetDate();
		};
	}
}
