/**	@file Julian.cpp
	@author Garth Santor
	@date 2013-09-19

	Julian calendar class implementation.
	*/

#include <khronos/julian_calendar.hpp>

namespace khronos {

	bool is_julian_leapyear(year_t year) {
		if (year % 4 == 0)
			return true;
		return false;
	}

}