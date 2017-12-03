#pragma once

/*
File:		khronos/calendar.hpp
Author:		Jeremy Peterson-Katz
Date:		October 21, 2017

Khronos library 'civil' declarations.
*/

#include <cmath>
#include <khronos/def.hpp>
#include <khronos/utility.hpp>


namespace khronos {

	// Enum's for month names and weekday names
	enum civil_month_codes_long { January = 1, February, March, April, May, June, July, August, September, October, November, December };

	enum civil_month_codes_short { JAN = January, FEB, MAR, APR, MAY, JUN, JUL, AUG, SEP, OCT, NOV, DEC };

	enum civil_weekday_codes_long { Monday = 0, Tuesday, Wednesday, Thursday, Friday, Saturday, Sunday };

	enum civil_weekday_codes_short { MON = Monday, TUE, WED, THU, FRI, SAT, SUN };

	enum civil_islamic_month_names { Muharram = 1, Safar, RabialAwwal, RabiathThani, JumadaIUla, 
		JumadatTania, Rajab, Shaban, Ramadan, Shawwal, DhulQadah, DhulHijja};

	enum civil_hebrew_month_names {	Nisan = 1, Iyyar, Sivan, Tammuz, Av, Elul, Tishri, Heshvan, Kislev, Teveth, Shevat, Adar, Veadar};

	enum civil_vulcan_month_names { Zat = 1, Druh, KriBrax, reTKhutai, TkeKhuti, Khuti,
		TaKrat, Krilior, etkhior, Tlakht, TkeTas, Tasmeen };

	namespace civil {

		// Declarations of functions to find month names in various calendars
		char const* month_name_long(month_t month);
		char const* month_name_short(month_t month);
		char const* islamic_month_names(month_t month);
		char const* hebrew_month_names(month_t month);
		char const* vulcan_month_names(month_t month);

		// Declarations of functions to find the day names in various calendars
		char const* day_name(day_t day);
		char const* islamic_day_name(day_t day);

		// Function to find the day of the week from a jd
		inline day_t day_of_week(jd_t jd) { return static_cast<day_t>(utility::mod(jd + 0.5, 7)); }

		// Declarations of functions to find the days in a month in various calendars
		day_t days_in_month(month_t month, bool isLeapYear);
		day_t islamic_days_in_month(month_t month, bool isLeapYear);
		day_t hebrew_days_in_month(year_t year, month_t month);

	}; // end-of-namespace civil
}; // end-of-namespace khronos