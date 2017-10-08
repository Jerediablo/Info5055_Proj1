/**	@file gregorian.cpp
	@author Garth Santor
	@date 2013-09-19

	Gregorian calendar class implementation.
	*/

#include <khronos/gregorian_calendar.hpp>
#include <khronos/calendar.hpp>

#include <cassert>
#include <sstream>
#include <ctime>
#include <iomanip>
#include <algorithm>


namespace khronos {

	/**	Leap year test for Proleptic Gregorian Calendar.
	@return 'true' if leap year, 'false' if not.
	@param year [in] Astronomical year (1 CE = 1, 1 BCE = 0, 2 BCE = -1, etc.)
	*/
	bool is_gregorian_leapyear(year_t year) {
		return (year % 4 == 0) && (year % 100 != 0) || (year % 400 == 0);
	}

	/**	Gregorian default constructor.  Initialize to the current local time. */

	Gregorian::Gregorian() {
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

	Gregorian::Gregorian(has_time_of_day status)
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


	/** Print the Gregorian Date as a string. */
	std::string Gregorian::to_string() const {
		std::ostringstream oss;

		// day of week
		oss << civil::day_name(day_of_week(to_jd())) << ", ";

		oss << gregorian_month_name(month_) << ' ' << (unsigned)day_ << ' ';
		if (year_ <= 0)
			oss << (-year_ + 1) << " BCE";
		else
			oss << year_ << " CE";

		return oss.str();
	}



	/** Gregorian + (integer year) operator. */
	Gregorian operator + (Gregorian const& dt, detail::packaged_year_integer const& year) {
		year_t y = dt.year() + year.nYears_;
		month_t m = dt.month();
		day_t d = dt.day();

		if (m == February && d == 29 && !is_gregorian_leapyear(y))
			d = 28;

		return Gregorian(y, m, d);
	}



	/** Gregorian + (integer month) operator. */
	Gregorian operator + (Gregorian const& dt, detail::packaged_month_integer const& month) {
		year_t yearsToAdd = month.nMonths_ / 12;
		month_t monthsToAdd = month.nMonths_ % 12;
		year_t y = dt.year() + yearsToAdd;
		month_t m = dt.month() + monthsToAdd;

		int adjustment = (m - 1) / 12 + (m - 12) / 12;
		y += adjustment;
		m -= month_t(adjustment * 12);

		day_t d = std::min(dt.day(), gregorian_days_in_month(m, is_gregorian_leapyear(y)));

		return Gregorian(y, m, d);
	}

}; // end-of-namespace calendar