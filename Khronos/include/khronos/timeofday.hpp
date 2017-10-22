#pragma once

/*
File:		khronos/timeofday.hpp
Author:		Jeremy Peterson-Katz
Date:		October 21, 2017

Khronos library 'time-of-day' declarations.
*/

#include <khronos/calendar.hpp>
#include <khronos/utility.hpp>

namespace khronos {


	// AM and PM conversions
	constexpr hour_t operator ""_PM(unsigned long long pmHour) {
		return static_cast<int>(pmHour % 12 + 12);
	}
	constexpr hour_t operator ""_pm(unsigned long long pmHour) {
		return static_cast<int>(pmHour % 12 + 12);
	}

	constexpr hour_t operator ""_AM(unsigned long long amHour) {
		return static_cast<int>(amHour % 12);
	}
	constexpr hour_t operator ""_am(unsigned long long amHour) {
		return static_cast<int>(amHour % 12);
	}

	double tod(hour_t hour, minute_t min, second_t sec);

	void hms(double tod, hour_t& hours, minute_t& minutes, second_t& seconds);
	
}  // end-of-namespace khronos
