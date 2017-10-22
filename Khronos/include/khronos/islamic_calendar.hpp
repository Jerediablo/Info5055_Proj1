#pragma once

/*
File:		khronos/Islamic_calendar.hpp
Author:		Jeremy Peterson-Katz
Date:		October 21, 2017

Islamic calendar class and functions.
*/

#include <khronos/def.hpp>
#include <khronos/calendar.hpp>
#include <khronos/julian_day.hpp>

#include <type_traits>
#include <string>

namespace khronos {

	bool is_islamic_leapyear(year_t year);

	inline char const * islamic_month_name(month_t month) {
		return civil::islamic_month_names(month);
	}

	inline day_t islamic_days_in_month(month_t month, bool isLeapYear) {
		return civil::islamic_days_in_month(month, isLeapYear);
	}

	jd_t islamic_to_jd(year_t year, month_t month, day_t day);
	jd_t islamic_to_jd(year_t year, month_t month, day_t day, hour_t hour, minute_t minute, second_t second);
	void jd_to_islamic(jd_t jd, year_t& year, month_t& month, day_t& day);
	void jd_to_islamic(jd_t jd, year_t& year, month_t& month, day_t& day, hour_t& hour, minute_t& minute, second_t& second);

	class Islamic {
		year_t		year_ = 1;
		month_t		month_ = 1;
		day_t		day_ = 1;
		hour_t		hour_ = 0;
		minute_t	minute_ = 0;
		second_t	second_ = 0;

		void from_jd(jd_t jd) { jd_to_islamic(jd, year_, month_, day_, hour_, minute_, second_); }
		jd_t to_jd() const { return islamic_to_jd(year_, month_, day_, hour_, minute_, second_); }

	public:
		Islamic();

		Islamic(has_time_of_day status);

		year_t  year() const { return year_; }

		month_t month() const { return month_; }

		day_t   day() const { return day_; }

		hour_t  hour() const { return hour_; }

		minute_t	minute() const { return minute_; }

		second_t	 second() const { return second_; }


		Islamic(year_t year, month_t month, day_t day) : year_(year), month_(month), day_(day) {}

		Islamic(year_t year, month_t month, day_t day, hour_t hour, minute_t minute, second_t second) :
			year_(year), month_(month), day_(day), hour_(hour), minute_(minute), second_(second) {}

		/** Construct a Islamic date from Islamic Day Number object.
		@param jd [in] Jd object.
		*/
		Islamic(Jd const& jd) { from_jd(jd.jd()); }


		std::string to_string() const;


		/**	Implicit cast to Jd class. */
		operator Jd () const { return Jd(to_jd()); }


		/**	Assign and convert from Jd type to Islamic type. */
		Islamic& operator = (Jd const& jd) {
			from_jd(jd.jd());
			return *this;
		}


		// block some operators
	private:
		Islamic operator + (detail::packaged_year_real const&);
		Islamic operator - (detail::packaged_year_real const&);
		Islamic operator + (detail::packaged_month_real const&);
		Islamic operator - (detail::packaged_month_real const&);
	};

	/** Islamic + (integer month) */
	Islamic operator + (Islamic const& dt, detail::packaged_month_integer const& month);

	/** Islamic - (integer month) */
	inline Islamic operator - (Islamic const& dt, detail::packaged_month_integer const& month) { return dt + detail::packaged_month_integer(-month.nMonths_); }

	/**	Islamic + (integer year) */
	Islamic operator + (Islamic const& dt, detail::packaged_year_integer const& year);

	/**	Islamic - (integer year) */
	inline Islamic operator - (Islamic const& dt, detail::packaged_year_integer const& year) { return dt + detail::packaged_year_integer(-year.nYears_); }

	/** Stream insertion operator. */
	inline std::ostream& operator << (std::ostream& os, Islamic const& i) { return os << i.to_string(); }

	year_t year(Islamic i);
	month_t month(Islamic i);
	day_t day(Islamic i);
	hour_t hour(Islamic i);
	minute_t minute(Islamic i);
	second_t second(Islamic i);

} // end-of-namespace khronos


