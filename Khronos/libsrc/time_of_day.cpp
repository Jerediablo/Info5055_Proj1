/*
File:		khronos/time_of_day.cpp
Author:		Jeremy Peterson-Katz
Date:		October 21, 2017

Khronos library 'time-of-day' function implementations.
*/

#include <khronos.hpp>
#include <khronos/timeofday.hpp>
namespace khronos {
	double tod(hour_t hour, minute_t min, second_t sec) {
		return (sec + 60 * (min + 60 * hour)) / khronos::SECONDS_PER_DAY;
	}

	void hms(double tod, hour_t& hours, minute_t& minutes, second_t& seconds) {
		int secondsInDay = static_cast<int>(floor(tod * 24 * 60 * 60 + 0.5));
		hours = secondsInDay / (60 * 60);
		minutes = (secondsInDay / 60) % 60;
		seconds = secondsInDay % 60;
	}

};  // end-of-namespace khronos