/*
File:		khronos/calendar.cpp
Author:		Jeremy Peterson-Katz
Date:		October 21, 2017
*/

#include <khronos/calendar.hpp>
#include <khronos/gregorian_calendar.hpp>
#include <khronos/hebrew_calendar.hpp>
#include <khronos/def.hpp>
#include <array>
#include <cassert> 
#include <cmath>

namespace khronos {
	namespace civil {

		/*  Function:	 days_in_month
			Purpose:	 Get the number of days in a month in the Gregorian or Julian calendars
			Parameters:	 - A month_t : The month [1-12] (0 is unused) 
						 - A bool : Showing if it's a leap year or not
			Returns:	 The number of days in the month, as type day_t		*/	
		day_t days_in_month(month_t month, bool isLeapYear) {
			static std::array<std::array<day_t, 13>, 2> daysInMonth = {
				0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31,
				0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31,
			};
			return daysInMonth[isLeapYear][month];
		}

		/*  Function:	 islamic_days_in_month
			Purpose:	 Get the number of days in a month in the Islamic calendar
			Parameters:	 - A month_t : The month [1-12]
						 - A bool : Showing if it's a leap year or not
			Returns:	 The number of days in the month, as type day_t		*/	
		day_t islamic_days_in_month(month_t month, bool isLeapYear) {
			if ((month % 2 != 0) || (month == 12 && isLeapYear)) 
				return 30;
			 else 
				return 29;			
		}

		/*  Function:	 hebrew_days_in_month
			Purpose:	 Get the number of days in a month in the Hebrew calendar
			Parameters:	 - A year_t : The year
						 - A month_t : The month [1-13]
			Returns:	 The number of days in the month, as type day_t		*/		
		day_t hebrew_days_in_month(year_t year, month_t month) {
			day_t days;
			if (month == 2 || month == 4 || month == 6 || month == 10 || month == 13)
				days = 29;
			else if (month == 12 && is_hebrew_leapyear(year) == false)
				days = 29;
			else if (month == 8 && utility::mod(hebrew_days_in_year(year), 10) != 5)
				days = 29;
			else if (month == 9 && utility::mod(hebrew_days_in_year(year), 10) == 3)
				days = 29;
			else
				days = 30;

			assert(month > 0);
			assert(month < 14);
			return days;

		}

		/*  Function:	 month_name_long
			Purpose:	 Get the long name for a month in the Gregorian or Julian calendars
			Parameters:	 A month_t : The month [1-12] (0 is unused)
			Returns:	 The long month name, as a pointer to a const char	*/
		char const * month_name_long(month_t month) {
			static std::array<char const *, 13> const names = {
				"",
				"January", "February", "March", "April", "May", "June",
				"July", "August", "September", "October", "November", "December"
			};

			assert(month > 0);
			assert(month < 13);
			return names[month];
		}

		/*  Function:	 month_name_short
			Purpose:	 Get the short name for a month in the Gregorian or Julian calendars
			Parameters:	 A month_t : The month [1-12] (0 is unused)
			Returns:	 The short month name, as a pointer to a const char	*/
		char const * month_name_short(month_t month) {
			static std::array<char const *, 13> const names = {
				"",
				"JAN", "FEB", "MAR", "APR", "MAY", "JUN",
				"JUL", "AUG", "SEP", "OCT", "NOV", "DEC"
			};

			assert(month > 0);
			assert(month < 13);
			return names[month];
		}

		/*  Function:	 islamic_month_names
			Purpose:	 Get the name for a month in the Islamic calendar
			Parameters:	 A month_t : The month [1-12] (0 is unused)
			Returns:	 The month name, as a pointer to a const char	*/
		char const * islamic_month_names(month_t month) {
			static std::array<char const *, 13> const names = { "", "Muharram", "Safar", "Rabi'al-Awwal",
				"Rabi'ath-Thani", "Jumada I-Ula", "Jumada t-Tania", "Rajab", "Sha'ban", "Ramadan", "Shawwal",
				"Dhu I-Qa'da", "Dhu I-Hijja" };

			assert(month > 0);
			assert(month < 13);
			return names[month];
		}

		/*  Function:	 hebrew_month_names
			Purpose:	 Get the name for a month in the Hebrew calendar
			Parameters:	 A month_t : The month [1-13] (0 is unused)
			Returns:	 The month name, as a pointer to a const char	*/
		char const * hebrew_month_names(month_t month) {
			static std::array<char const *, 14> const names = { "",
				"Nisan", "Iyyar", "Sivan", "Tammuz",
				"Av", "Elul", "Tishri", "Heshvan",
				"Kislev", "Teveth", "Shevat", "Adar", "Veadar" };

			assert(month > 0);
			assert(month < 14);
			return names[month];
		}

		/*  Function:	 vulcan_month_names
			Purpose:	 Get the name for a month in the Vulcan calendar
			Parameters:	 A month_t : The month [1-12] (0 is unused)
			Returns:	 The month name, as a pointer to a const char	*/
		char const * vulcan_month_names(month_t month) {
			static std::array<char const *, 13> const names = { "", "Z'at",
				"D'ruh", "K'riBrax", "re'T'Khutai", "T'keKhuti", "Khuti",
				"Ta'Krat", "K'ri'lior", "et'khior", "T'lakht", "T'ke'Tas", "Tasmeen" };

			assert(month > 0);
			assert(month < 13);
			return names[month];
		}

		/*  Function:	 day_name
			Purpose:	 Get the name for a day in the Gregorian, Julian, or Hebrew calendars
			Parameters:	 A day_t : The day [0-6]
			Returns:	 The day name, as a pointer to a const char	*/
		char const* day_name(day_t day) {
			static std::array<char const*, 7> const names = {
				"Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"
			};
			assert(day >= 0);
			assert(day < 7);
			return names[day];
		}

		/*  Function:	 islamic_day_name
			Purpose:	 Get the name for a day in the Islamic calendar
			Parameters:	 A day_t : The day [0-6]
			Returns:	 The day name, as a pointer to a const char	*/
		char const* islamic_day_name(day_t day) {
			day++;
			static std::array<char const*, 7> const names = {
				"al-'ahad", "al-'ithnayn", "alth-thalatha", "al-'arb`a'", "al-kharmis", "al-jum`a", "as-sabt"
			};
			assert(day >= 0);
			assert(day < 7);
			return names[day];
		}
	};  // end-of-namespace civil
};  // end-of-namespace khronos
