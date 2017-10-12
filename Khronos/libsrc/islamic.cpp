/**	@file Islamic.cpp
	@author Garth Santor
	@date 2013-09-20

	Islamic calendar class implementation.
	*/

#include <khronos/islamic_calendar.hpp>
#include <khronos/utility.hpp>

#include <cassert>
#include <array>
#include <sstream>
#include <ctime>
#include <iomanip>
#include <algorithm>

namespace khronos {

	bool is_islamic_leapyear(year_t year) {
		return utility::mod((11.0 * year) + 14, 30) < 11;
	}

	Islamic::Islamic() {
		from_jd(Jd().jd());
	}

	Islamic::Islamic(has_time_of_day status)
	{
		if (status == 0) {
				from_jd(Jd().jd());
			hour_ = -24;
			minute_ = 0;
			second_ = 0;
		}
		else if (status == 1) {
			from_jd(Jd().jd());
		}
	}

	std::string Islamic::to_string() const {
		std::ostringstream oss;

		// day of week
		oss << civil::day_name(day_of_week(to_jd())) << ", ";

		oss << islamic_month_name(month_) << ' ' << (unsigned)day_ << ' ';
		if (year_ <= 0)
			oss << (-year_ + 1) << " BC, ";
		else
			oss << year_ << " AD, ";

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

	// Add months ( + operator)
	Islamic operator + (Islamic const& dt, detail::packaged_month_integer const& n) {
		year_t y = dt.year() + n.nMonths_ / 12;
		month_t m = dt.month() + n.nMonths_ % 12;
		int adjust = (m - 1) / 12 + (m - 12) / 12;
		y += adjust;
		m -= adjust * 12;
		day_t d = std::min(dt.day(), islamic_days_in_month(m, is_islamic_leapyear(y)));

		hour_t hour = dt.hour();
		minute_t minute = dt.minute();
		second_t second = dt.second();

		return Islamic(y, m, d, hour, minute, second);
	}


	// Add years ( + operator)
	Islamic operator + (Islamic const& dt, detail::packaged_year_integer const& n) {
		year_t y = dt.year() + n.nYears_;
		month_t m = dt.month();
		day_t d = dt.day();

		hour_t hour = dt.hour();
		minute_t minute = dt.minute();
		second_t second = dt.second();

		if (m == 12 && d == 30 && !is_islamic_leapyear(y))
			d = 29;

		return Islamic(y, m, d, hour, minute, second);
	}

	year_t year(Islamic i) {
		return i.year();
	}
	
	month_t month(Islamic i) {
		return i.month();
	}

	day_t day(Islamic i) {
		return i.day();
	}

	hour_t hour(Islamic i) {
		return i.hour();
	}

	minute_t minute(Islamic i) {
		return i.minute();
	}

	second_t second(Islamic i) {
		return i.second();
	}
}