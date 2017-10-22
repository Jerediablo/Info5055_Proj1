/*
File:		khronos/julian_to_jd.cpp
Author:		Jeremy Peterson-Katz
Date:		October 21, 2017

Date and time library Julian conversion implementations.
*/

#include <khronos/julian_calendar.hpp>
#include <khronos/timeofday.hpp>

namespace khronos {

	jd_t julian_to_jd(year_t year, month_t month, day_t day) {
		long long a = (14 - month) / 12;
		long long y = year + 4800 - a;
		long long m = month + 12 * a - 3;
		return day + (153 * m + 2) / 5 + 365 * y + y / 4 - 32083.5;
	}

	jd_t julian_to_jd(year_t year, month_t month, day_t day, hour_t hour, minute_t minute, second_t second) {
		jd_t jdn = julian_to_jd(year, month, day);
		double tod = khronos::tod(hour, minute, second);
		return jdn + tod;
	}

	void jd_to_julian(jd_t jd, year_t& year, month_t& month, day_t& day) {
		double a = floor(jd + 0.5);
		double b = a + 1524;
		double c = floor((b - 122.1) / 365.25);
		double d = floor(365.25 * c);
		double e = floor((b - d) / 30.6001);
		
		if (e < 14)
			month = static_cast<month_t>(floor(e - 1));
		else
			month = static_cast<month_t>(floor(e - 13));

		if (month > 2)
			year = static_cast<year_t>(floor(c - 4716));
		else
			year = static_cast<year_t>(floor(c - 4715));

		day = static_cast<day_t>(b - d - floor(30.6001 * e));
	}

	void jd_to_julian(jd_t jd, year_t& year, month_t& month, day_t& day, hour_t& hour, minute_t& minute, second_t& second) {
		double a = floor(jd + 0.5);
		double b = a + 1524;
		double c = floor((b - 122.1) / 365.25);
		double d = floor(365.25 * c);
		double e = floor((b - d) / 30.6001);

		if (e < 14)
			month = static_cast<month_t>(floor(e - 1));
		else
			month = static_cast<month_t>(floor(e - 13));

		if (month > 2)
			year = static_cast<year_t>(floor(c - 4716));
		else
			year = static_cast<year_t>(floor(c - 4715));

		day = static_cast<day_t>(b - d - floor(30.6001 * e));

		double tod = (jd + 0.5) - floor(jd + 0.5);
		hms(tod, hour, minute, second);
	}
}  // end-of-namespace khronos