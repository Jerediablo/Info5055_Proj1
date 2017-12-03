/*
File:		khronos/gregorian.cpp
Author:		Jeremy Peterson-Katz
Date:		October 21, 2017

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

	/*  Function:	 is_gregorian_leapyear
		Purpose:     Determine if a year in the Gregorian calendar is a leapyear or not
		Parameters:	 A year_t : A year in the Astronomical year (1 CE = 1, 1 BCE = 0, 2 BCE = -1, etc.)
		Returns:	 A bool : true if leapyear, false if not	*/
	bool is_gregorian_leapyear(year_t year) {
		return (year % 4 == 0) && (year % 100 != 0) || (year % 400 == 0);
	}

	// Gregorian default constructor.  Initialize to the current local time.	
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

	// Gregorian constructor taking the has_time_of_day enum.
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

	// Print the Gregorian Date as a string. 
	std::string Gregorian::to_string() const {
		std::ostringstream oss;

		// Day name
		oss << civil::day_name(day_of_week(to_jd())) << ", ";

		// Month name
		oss << gregorian_month_name(month_) << ' ' << (unsigned)day_ << ' ';

		// Determine whether to use BCE or CE
		if (year_ <= 0)
			oss << (-year_ + 1) << " BCE, ";
		else
			oss << year_ << " CE, ";

		// Change from 24 hour clock to 12 hour
		if (hour_ >= 12) {

			if (hour_ > 12)
				oss << hour_ - 12;

			// If the hour is 12 (ie. noon) don't subtract 12
			else
				oss << hour_;

			// Print minutes and seconds, formatting to 2 digits, left filling with zeros
			oss << ":" << std::setfill('0') << std::setw(2) << minute_;
			oss << ":" << std::setfill('0') << std::setw(2) << second_;
			oss << " pm";
		}
		else {
			// If the hour is 0 (ie. midnight) print 12
			if (hour_ == 0) 
				oss << "12";
			else
				oss << hour_;

			// Print minutes and seconds, formatting to 2 digits, left filling with zeros
			oss << ":" << std::setfill('0') << std::setw(2) << minute_;
			oss << ":" << std::setfill('0') << std::setw(2) << second_;
			oss << " am";
		}

		return oss.str();
	}

	// Gregorian + (integer year) operator. 
	Gregorian operator + (Gregorian const& dt, detail::packaged_year_integer const& year) {
		year_t y = dt.year() + year.nYears_;
		month_t m = dt.month();
		day_t d = dt.day();

		hour_t hour = dt.hour();
		minute_t minute = dt.minute();
		second_t second = dt.second();

		if (m == February && d == 29 && !is_gregorian_leapyear(y))
			d = 28;

		return Gregorian(y, m, d, hour, minute, second);
	}

	// Gregorian + (integer month) operator. 
	Gregorian operator + (Gregorian const& dt, detail::packaged_month_integer const& month) {
		year_t yearsToAdd = month.nMonths_ / 12;
		month_t monthsToAdd = month.nMonths_ % 12;
		year_t y = dt.year() + yearsToAdd;
		month_t m = dt.month() + monthsToAdd;

		hour_t hour = dt.hour();
		minute_t minute = dt.minute();
		second_t second = dt.second();

		int adjustment = (m - 1) / 12 + (m - 12) / 12;
		y += adjustment;
		m -= month_t(adjustment * 12);

		day_t d = std::min(dt.day(), gregorian_days_in_month(m, is_gregorian_leapyear(y)));

		return Gregorian(y, m, d, hour, minute, second);
	}

	year_t year(Gregorian g) {
		return g.year();
	}

	month_t month(Gregorian g) {
		return g.month();
	}

	day_t day(Gregorian g) {
		return g.day();
	}

	hour_t hour(Gregorian g) {
		return g.hour();
	}

	minute_t minute(Gregorian g) {
		return g.minute();
	}

	second_t second(Gregorian g) {
		return g.second();
	}

}; // end-of-namespace khronos