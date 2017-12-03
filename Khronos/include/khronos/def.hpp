#pragma once

/*
File:		khronos/def.hpp
Author:		Jeremy Peterson-Katz
Date:		October 21, 2017

Khronos library definitions.
*/

namespace khronos {

	// Types
	using jd_t = double;		// Julian date (JD)
	using jdn_t = long long;	// Julian day number (JDN)

	using year_t = long long;	// year +/- 24 billion
	using month_t = int;		// month [1..12]
	using day_t = int;			// day [1..31]
	using hour_t = int;			// hour [0..24]
	using minute_t = int;		// minute [0..60]
	using second_t = double;	// second [0..60]

	// Constants
	long constexpr SECONDS_PER_DAY = 86'400;
	double constexpr EARTH_ORBITAL_PERIOD_DAYS = 365.256'363'004;

	// Epochs (Constants)
	jd_t constexpr GREGORIAN_EPOCH = 1'721'425.5;
	jd_t constexpr JULIAN_EPOCH = 1'721'423.5;
	jd_t constexpr ISLAMIC_EPOCH = 1'948'439.5;
	jd_t constexpr HEBREW_EPOCH = 347'995.5	;
	jd_t constexpr VULCAN_EPOCH = 173'651.6;

	// Enum for if a constructor should include time of day or not
	enum has_time_of_day { NOTIMEOFDAY, WTIMEOFDAY };

} // end-of-namespace khronos