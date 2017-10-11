/**	@file Islamic_to_jd.cpp
	@author Garth Santor
	@date 2013-09-19

	Islamic calendar conversion implementations.
	*/

#include <khronos/islamic_calendar.hpp>
#include <khronos/timeofday.hpp>

#include <algorithm>

namespace khronos {
	jd_t islamic_to_jd(year_t year, month_t month, day_t day) {
		jd_t jdn = day + ceil(29.5 * (month - 1)) + (year - 1) * 354 + floor((3 + 11 * year) / 30.0) + ISLAMIC_EPOCH - 1;
		return jdn;
	}
	jd_t islamic_to_jd(year_t year, month_t month, day_t day, hour_t hour, minute_t minute, second_t second) {
		jd_t jdn = islamic_to_jd(year, month, day);
		double tod = khronos::tod(hour, minute, second);
		if (tod >= 0.5) {
			tod--;
		}
		return jdn + tod;
	}

	void jd_to_islamic(jd_t jd, year_t& year, month_t& month, day_t& day) {
		jd = floor(jd) + 0.5;
		year = static_cast<year_t>(floor((30 * (jd - ISLAMIC_EPOCH) + 10646) / 10631));
		month = static_cast<month_t>(std::min(12.0, ceil((jd - (29 + islamic_to_jd(year, 1, 1)))/29.5)+1));
		day = static_cast<day_t>(jd - islamic_to_jd(year, month, 1) + 1);
	}

	

	void jd_to_islamic(jd_t jd, year_t& year, month_t& month, day_t& day, hour_t& hour, minute_t& minute, second_t& second) {
		jd_to_islamic(jd, year, month, day);
		double tod = (jd + 0.5) - floor(jd + 0.5);
		hms(tod, hour, minute, second);
	}
}