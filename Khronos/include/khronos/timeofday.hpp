#pragma once

/*
khronos\timeofday.hpp
(c) Garth Santor
Created: 2015-09-22
Last Updated: 2015-09-22

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
	
}
