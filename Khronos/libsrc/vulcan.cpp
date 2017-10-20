/**	@file vulcan.cpp
	@author Garth Santor
	@date 2014-09-29

	Vulcan calendar class implementation.
	*/

#include <khronos/vulcan_calendar.hpp>

namespace khronos {

	jd_t vulcan_to_jd(year_t year, month_t month, day_t day) {
		double y = 266.4;
		double m = y / 12;
		double d = m / 21;
		return (year * y) + (month * m) + (day * d) + VULCAN_EPOCH - (y+m+d);
		
	}

	jd_t vulcan_to_jd(year_t year, month_t month, day_t day, hour_t hour, minute_t minute, second_t second) {
		jd_t jdn = vulcan_to_jd(year, month, day);
		double h = ((266.4 / 12) / 21) / 18;
		double min = h / 54;
		double s = min / 54;
		return jdn + (hour * h) + (minute * min) + (second * s);
	}

	void jd_to_vulcan(jd_t jd, year_t& year, month_t& month, day_t& day) {

	}

	void jd_to_vulcan(jd_t jd, year_t& year, month_t& month, day_t& day, hour_t& hour, minute_t& minute, second_t& second) {

	}
}