#pragma once

/**	@file khronos/hebrew_calendar.hpp
	@author Garth Santor
	@date 2013-09-26

	Hebrew calendar class.
	*/

#include <khronos/def.hpp>
#include <khronos/calendar.hpp>
#include <khronos/julian_day.hpp>

#include <type_traits>
#include <string>

namespace khronos {

	bool is_hebrew_leapyear(year_t year);

	inline char const * hebrew_month_name(month_t month) {
		return civil::hebrew_month_names(month);
	}

	jd_t hebrew_to_jd(year_t year, month_t month, day_t day);
	jd_t hebrew_to_jd(year_t year, month_t month, day_t day, hour_t hour, minute_t minute, second_t second);
	void jd_to_hebrew(jd_t jd, year_t& year, month_t& month, day_t& day);
	void jd_to_hebrew(jd_t jd, year_t& year, month_t& month, day_t& day, hour_t& hour, minute_t& minute, second_t& second);

	day_t delayOfWeek(year_t year);
	day_t delayAdjacentYear(year_t year);

}