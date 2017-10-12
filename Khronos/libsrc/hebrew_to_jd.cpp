/**	@file Hebrew_to_jd.cpp
	@author Garth Santor
	@date 2012-09-14

	Hebrew calendar conversion implementations.
	*/

#include <khronos/hebrew_calendar.hpp>
#include <khronos/timeofday.hpp>

#include <algorithm>

namespace khronos {

	jd_t hebrew_to_jd(year_t year, month_t month, day_t day) {
		jd_t jdn = HEBREW_EPOCH + delayOfWeek(year) + delayAdjacentYear(year) + day + 1;
		return jdn;
	}
	jd_t hebrew_to_jd(year_t year, month_t month, day_t day, hour_t hour, minute_t minute, second_t second) {
	
		// TO DO
		return 0;
	}

}