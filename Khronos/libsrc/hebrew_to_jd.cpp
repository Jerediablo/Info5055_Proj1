/**	@file Hebrew_to_jd.cpp
	@author Garth Santor
	@date 2012-09-14

	Hebrew calendar conversion implementations.
	*/

#include <khronos/hebrew_calendar.hpp>
#include <khronos/timeofday.hpp>

#include <algorithm>

namespace khronos {

	jd_t hebrew_to_jd(year_t year, month_t month, day_t day) {
		jd_t jdn = HEBREW_EPOCH + delayOfWeek(year) + delayAdjacentYear(year) + day + 1;
		if (month < 7) {
			for (int m = 7; m <= hebrew_months_in_year(year); ++m) {
				jdn += hebrew_days_in_month(year, m);
			}
			for (int m = 1; m <= (month - 1); ++m) {
				jdn += hebrew_days_in_month(year, m);
			}
		}
		else {
			for (int m = 7; m <= (month-1); ++m) {
				jdn += hebrew_days_in_month(year, m);
			}	
		}
		return jdn;
	}
	jd_t hebrew_to_jd(year_t year, month_t month, day_t day, hour_t hour, minute_t minute, second_t second) {
	
		jd_t jdn = hebrew_to_jd(year, month, day);
		double tod = khronos::tod(hour, minute, second);
		if (tod >= 0.5) {
			tod--;
		}
		jd_t jd = jdn + tod;
		return jd;
	}

	void jd_to_hebrew(jd_t jd, year_t& year, month_t& month, day_t& day) {
	    jd = floor(jd) + 0.5;
		int count = floor((( jd-HEBREW_EPOCH ) * 98'496) / 35'975'351);
		year = count - 1;
		int i = count;
		while (jd >= hebrew_to_jd(i, 7, 1)) {
			year++;
			i++;
		}
		int first = 1;
		if (jd < hebrew_to_jd(year, 1, 1)) {
			first = 7;
		}
		month = first;
		i = first;
		while (jd > hebrew_to_jd(year, i, hebrew_days_in_month(year, i))) {
			month++;
			i++;
		}
		day = floor(jd - hebrew_to_jd(year, month, 1) + 1);
	}

	void jd_to_hebrew(jd_t jd, year_t& year, month_t& month, day_t& day, hour_t& hour, minute_t& minute, second_t& second) {
		jd_to_hebrew(jd, year, month, day);
		double tod = (jd + 0.5) - floor(jd + 0.5);
		hms(tod, hour, minute, second);
	}
}