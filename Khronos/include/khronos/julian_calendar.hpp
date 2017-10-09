#pragma once

/**	@file khronos/julian_calendar.hpp
	@author Garth Santor
	@date 2013-09-19

	Julian calendar functions and class declaration.
	*/

#include <khronos/def.hpp>
#include <khronos/calendar.hpp>

namespace khronos {

	bool is_julian_leapyear(year_t year);

	inline day_t julian_days_in_month(month_t month, bool isLeapYear) {
		return civil::days_in_month(month, isLeapYear);
	}

	inline char const * julian_month_name(month_t month) {
		return civil::month_name_long(month);
	}

	inline char const * julian_short_month_name(month_t month) {
		return civil::month_name_short(month);
	}

}