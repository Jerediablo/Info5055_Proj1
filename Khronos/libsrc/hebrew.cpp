/*
File:		khronos/hebrew.cpp
Author:		Jeremy Peterson-Katz
Date:		October 21, 2017

Hebrew calendar class implementation.
*/

#include <khronos/hebrew_calendar.hpp>
#include <khronos/utility.hpp>

#include <cassert>
#include <array>
#include <sstream>
#include <ctime>
#include <iomanip>
#include <algorithm>

namespace khronos {

	bool is_hebrew_leapyear(year_t year) {
		return utility::mod((7.0 * year) + 1, 19) < 7;
	}

	Hebrew::Hebrew() {
		from_jd(Jd().jd());
	}

	Hebrew::Hebrew(has_time_of_day status)
	{
		if (status == 0) {
			from_jd(Jd().jd());
			if (hour_ >= 12) {
				--day_;
			}
			hour_ = 0;
			minute_ = 0;
			second_ = 0;
		}
		else if (status == 1) {
			from_jd(Jd().jd());
		}
	}

	std::string Hebrew::to_string() const {
		std::ostringstream oss;

		// day of week
	//	oss << civil::hebrew_day_name(day_of_week(to_jd())) << ", ";

		oss << hebrew_month_name(month_) << ' ' << (unsigned)day_ << ' ';

		oss << year_ << ", ";

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

	month_t hebrew_months_in_year(year_t year) {
		month_t months = 12;
		if (is_hebrew_leapyear(year)) {
			++months;
		}
		return months;
	}

	day_t delayOfWeek(year_t year) {
		month_t months = static_cast<month_t>(floor((235 * year - 234) / 19.0));
		long parts = 12084 + 13753 * months;
		day_t days = months * 29 + static_cast<day_t>(floor(parts / 25920.0));
		
		if ( ((3 * (days + 1)) % 7) < 3) {
			++days;
		}
		return days;
	}

	day_t delayAdjacentYear(year_t year) {
		day_t last = delayOfWeek(year - 1);
		day_t present = delayOfWeek(year);
		day_t next = delayOfWeek(year + 1);
		day_t days = 0;
		if (next - present == 356)
			days = 2;
		else if (next - present != 356 && present - last == 382)
			days = 1;

		return days;
	}

	long hebrew_days_in_year(year_t year) {
		return static_cast<long>(hebrew_to_jd(year + 1, 7, 1) - hebrew_to_jd(year, 7, 1));
	}

	day_t hebrew_days_in_month(year_t year, month_t month) {
		day_t days = 0;
		if (month == 2 || month == 4 || month == 6 || month == 10 || month == 13) {
			days = 29;
		}
		else if (month == 12 && is_hebrew_leapyear(year) == false) {
			days = 29;
		}
		else if (month == 8 && (hebrew_days_in_year(year) % 10) != 5) {
			days = 29;
		}
		else if (month == 9 && (hebrew_days_in_year(year) % 10) == 3) {
			days = 29;
		}
		else {
			days = 30;
		}
		return days;

	}

	year_t year(Hebrew i) {
		return i.year();
	}

	month_t month(Hebrew i) {
		return i.month();
	}

	day_t day(Hebrew i) {
		return i.day();
	}

	hour_t hour(Hebrew i) {
		return i.hour();
	}

	minute_t minute(Hebrew i) {
		return i.minute();
	}

	second_t second(Hebrew i) {
		return i.second();
	}
}  // end-of-namespace khronos