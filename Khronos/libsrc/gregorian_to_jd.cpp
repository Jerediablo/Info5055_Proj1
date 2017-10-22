/*
File:		khronos/gregorian_to_jdn.cpp
Author:		Jeremy Peterson-Katz
Date:		October 21, 2017

Khronos library 'gregorian::to_jdn' implementation.
*/

#include <khronos/gregorian_calendar.hpp>
#include <khronos/timeofday.hpp>
#include <cassert>
#include <cmath>

namespace khronos {

	namespace detail {
		/**	Real-number implementation. */
		jd_t greg2jd_real(year_t year, month_t month, day_t dayOfMonth) {
			long long y = year - 1;
			return
				GREGORIAN_EPOCH - 1
				+ 365 * y
				+ floor(y / 4.0)
				- floor(y / 100.0)
				+ floor(y / 400.0)
				+ floor((((367 * month) - 362) / 12.0)
					+ ((month <= 2)
						? 0
						: (is_gregorian_leapyear(year) ? -1 : -2)))
				+ dayOfMonth;
		} 


		/**	Integer implementation (wikipedia). */
		inline jd_t greg2jd_integer(year_t year, month_t month, day_t day) {
			long long a = (14 - month) / 12;
			long long y = year + 4800 - a;
			long long m = month + 12 * a - 3;
			return day + (153 * m + 2) / 5 + 365 * y + y / 4 - y / 100 + y / 400 - 32045 - 0.5;
		}
	};  // end-of-namespace detail

	jd_t gregorian_to_jd(year_t year, month_t month, day_t day) {
		assert(year > -4800 && "Minimum year is 4800 BCE");
		assert(month >= 1 && "Minimum month is January = 1");
		assert(month <= 12 && "Maximum month is December = 12");
		assert(day >= 1 && "Minimum day of the month is 1");
		assert(day <= 31 && "Maximum day of the month is 31");
		assert(detail::greg2jd_integer(year, month, day) == detail::greg2jd_real(year, month, day));
		return detail::greg2jd_integer(year, month, day);
	}

	jd_t gregorian_to_jd(year_t year, month_t month, day_t day, hour_t hour, minute_t minute, second_t second) {
		jd_t jdn = gregorian_to_jd(year, month, day);
		double tod = khronos::tod(hour, minute, second);
		return jdn + tod;
	}
}  // end-of-namespace khronos