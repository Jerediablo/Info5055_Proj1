/**	@file Hebrew.cpp
	@author Garth Santor
	@date 2013-10-20

	Hebrew calendar class implementation.
	*/

#include <khronos/hebrew_calendar.hpp>
#include <khronos/utility.hpp>

#include <cassert>
#include <array>
#include <sstream>
#include <ctime>
#include <iomanip>
#include <algorithm>

namespace khronos {

	bool is_hebrew_leapyear(year_t year) {
		return utility::mod((7.0 * year) + 1, 30) < 7;
	}

	day_t delayOfWeek(year_t year) {
		month_t months = floor((235 * year - 234) / 19);
		long parts = 12084 + 13753 * months;
		day_t days = months * 29 + floor(parts / 25920);
		
		if (utility::mod((3 * (days + 1)), 7) < 3) {
			++days;
		}
		return days;
	}

	day_t delayAdjacentYear(year_t year) {
		day_t last = delayOfWeek(year - 1);
		day_t present = delayOfWeek(year);
		day_t next = delayOfWeek(year + 1);
		day_t days = 0;
		if (next - present == 365)
			days = 2;
		else if (next - present != 365 && present - last == 382)
			days = 1;

		return days;
	}
}