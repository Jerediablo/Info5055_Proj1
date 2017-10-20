#pragma once

/**	@file vulcan.hpp
	@author Garth Santor
	@date 2014-09-29

	Vulcan calendar class and functions.
	*/

#include <khronos/calendar.hpp>
#include <khronos/def.hpp>
#include <khronos/julian_day.hpp>

#include <type_traits>
#include <string>


namespace khronos {

	inline day_t vulcan_days_in_month() {
		return 21;
	}

	inline char const * vulcan_month_name(month_t month) {
		return civil::vulcan_month_names(month);
	}

	jd_t vulcan_to_jd(year_t year, month_t month, day_t day);
	jd_t vulcan_to_jd(year_t year, month_t month, day_t day, hour_t hour, minute_t minute, second_t second);
	void jd_to_vulcan(jd_t jd, year_t& year, month_t& month, day_t& day);
	void jd_to_vulcan(jd_t jd, year_t& year, month_t& month, day_t& day, hour_t& hour, minute_t& minute, second_t& second);

}