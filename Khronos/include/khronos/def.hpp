#pragma once

/*
khronos\def.hpp
(c) Garth Santor
Created: 2015-09-22
Last Updated: 2015-09-22

Khronos library definitions.
*/

namespace khronos {
	// Types
	using jd_t = double;		// Julian date (JD)
	using jdn_t = long long;	// Julian day number (JDN)

	using year_t = long long;	// year +/- 24 billion
	using month_t = int;		// month [1..12]
	using day_t = int;			// day [1..31]
	using hour_t = int;
	using minute_t = int;
	using second_t = double;

	// Constants
	long constexpr SECONDS_PER_DAY = 86'400;
	double constexpr EARTH_ORBITAL_PERIOD_DAYS = 365.256'363'004;
	jd_t constexpr GREGORIAN_EPOCH = 1'721'425.5;

	enum has_time_of_day { NOTIMEOFDAY, WTIMEOFDAY };
}