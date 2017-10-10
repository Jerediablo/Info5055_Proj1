/**	@file Julian.cpp
	@author Garth Santor
	@date 2013-09-19

	Julian calendar class implementation.
	*/

#include <khronos/julian_calendar.hpp>

#include <cassert>
#include <sstream>
#include <ctime>
#include <iomanip>
#include <algorithm>

namespace khronos {

	bool is_julian_leapyear(year_t year) {
		return (year % 4 == 0);
	}

	Julian::Julian() {
		time_t nowTime = time(NULL);
		struct tm tmNow;
		localtime_s(&tmNow, &nowTime);
		year_ = year_t(tmNow.tm_year + 1900);
		month_ = month_t(tmNow.tm_mon + 1);
		day_ = day_t(tmNow.tm_mday);
		hour_ = hour_t(tmNow.tm_hour);
		minute_ = minute_t(tmNow.tm_min);
		second_ = second_t(tmNow.tm_sec);
		
	}

	Julian::Julian(has_time_of_day status)
	{
		if (status == 0) {
			time_t nowTime = time(NULL);
			struct tm tmNow;
			localtime_s(&tmNow, &nowTime);
			year_ = tmNow.tm_year + 1900;
			month_ = (tmNow.tm_mon + 1);
			day_ = (tmNow.tm_mday);
		}
		else if (status == 1) {
			time_t nowTime = time(NULL);
			struct tm tmNow;
			localtime_s(&tmNow, &nowTime);
			year_ = tmNow.tm_year + 1900;
			month_ = (tmNow.tm_mon + 1);
			day_ = (tmNow.tm_mday);
			hour_ = (tmNow.tm_hour);
			minute_ = (tmNow.tm_min);
			second_ = (tmNow.tm_sec);

		}
	}

	std::string Julian::to_string() const {
		std::ostringstream oss;

		// day of week
		oss << civil::day_name(day_of_week(to_jd())) << ", ";

		oss << julian_month_name(month_) << ' ' << (unsigned)day_ << ' ';
		if (year_ <= 0)
			oss << (-year_ + 1) << " BCE, ";
		else
			oss << year_ << " CE, ";

		if (hour_ >= 12) {
			if (hour_ > 12)
				oss << hour_ - 12;
			else
				oss << hour_;
			oss << ":" << std::setfill('0') << std::setw(2) << minute_;
			oss << ":" << std::setfill('0') << std::setw(2) << second_;
			oss << " pm";
		}
		else {
			if (hour_ == 0)
				oss << "12";
			else
				oss << hour_;
			oss << ":" << std::setfill('0') << std::setw(2) << minute_;
			oss << ":" << std::setfill('0') << std::setw(2) << second_;
			oss << " am";
		}
		return oss.str();
	}

}