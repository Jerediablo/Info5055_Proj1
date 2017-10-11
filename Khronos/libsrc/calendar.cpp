#include <khronos/calendar.hpp>
#include <khronos/gregorian_calendar.hpp>
#include <khronos/def.hpp>
#include <array>
#include <cassert> 
#include <cmath>

namespace khronos {
	namespace civil {
		day_t days_in_month(month_t month, bool isLeapYear) {
			static std::array<std::array<day_t, 13>, 2> daysInMonth = {
				0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31,
				0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31,
			};
			return daysInMonth[isLeapYear][month];
		}

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

		char const * islamic_month_names(month_t month) {
			static std::array<char const *, 13> const names = { "", "Muharram", "Safar", "Rabi'al-Awwal",
				"Rabi'ath-Thani", "Jumada I-Ula", "Jumada t-Tania", "Rajab", "Sha'ban", "Ramadan", "Shawwal",
				"Dhu I-Qa'da", "Dhu I-Hijja" };

			assert(month > 0);
			assert(month < 13);
			return names[month];
		}

		/** Get the full name of the civil day of week.
		@return pointer to the day name as a c-string.
		@param day [in] day number [0..6], where 0 = Monday
		*/
		char const* day_name(day_t day) {
			static std::array<char const*, 7> const names = {
				"Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"
			};
			assert(day >= 0);
			assert(day < 7);
			return names[day];
		}
	};
};
