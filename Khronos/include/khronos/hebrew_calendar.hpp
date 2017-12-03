#pragma once

/*
File:		khronos/hebrew_calendar.hpp
Author:		Jeremy Peterson-Katz
Date:		October 21, 2017

Khronos library 'Hebrew calendar' declarations.
*/

#include <khronos/def.hpp>
#include <khronos/calendar.hpp>
#include <khronos/julian_day.hpp>

#include <type_traits>
#include <string>

namespace khronos {

	// FUNCTIONS
	// --------------------------------------------------------------------------------------

	// Function declarations for hebrew-to-jd and jd-to-hebrew conversions (with and without times).
	jd_t hebrew_to_jd(year_t year, month_t month, day_t day);
	jd_t hebrew_to_jd(year_t year, month_t month, day_t day, hour_t hour, minute_t minute, second_t second);
	void jd_to_hebrew(jd_t jd, year_t& year, month_t& month, day_t& day);
	void jd_to_hebrew(jd_t jd, year_t& year, month_t& month, day_t& day, hour_t& hour, minute_t& minute, second_t& second);

	// Function declaraction to check if a year is a leapyear.
	bool is_hebrew_leapyear(year_t year);

	// Provide the name of the given month in the Hebrew calendar. 
	inline char const * hebrew_month_name(month_t month) {
		return civil::hebrew_month_names(month);
	}

	day_t delayOfWeek(year_t year);
	day_t delayAdjacentYear(year_t year);
	long hebrew_days_in_year(year_t year);
	day_t hebrew_days_in_month(year_t year, month_t month);
	month_t hebrew_months_in_year(year_t year);

	// CLASSES
	// --------------------------------------------------------------------------------------

	class Hebrew {
		year_t		year_ = 1;
		month_t		month_ = 1;
		day_t		day_ = 1;
		hour_t		hour_ = 0;
		minute_t	minute_ = 0;
		second_t	second_ = 0;

		void from_jd(jd_t jd) { jd_to_hebrew(jd, year_, month_, day_, hour_, minute_, second_); }
		jd_t to_jd() const { return hebrew_to_jd(year_, month_, day_, hour_, minute_, second_); }

	public:
		Hebrew();

		Hebrew(has_time_of_day status);

		year_t  year() const { return year_; }

		month_t month() const { return month_; }

		day_t   day() const { return day_; }

		hour_t  hour() const { return hour_; }

		minute_t	minute() const { return minute_; }

		second_t	 second() const { return second_; }


		Hebrew(year_t year, month_t month, day_t day) : year_(year), month_(month), day_(day) {}

		Hebrew(year_t year, month_t month, day_t day, hour_t hour, minute_t minute, second_t second) :
			year_(year), month_(month), day_(day), hour_(hour), minute_(minute), second_(second) {}

		/** Construct a Hebrew date from Hebrew Day Number object.
		@param jd [in] Jd object.
		*/
		Hebrew(Jd const& jd) { from_jd(jd.jd()); }


		std::string to_string() const;


		/**	Implicit cast to Jd class. */
		operator Jd () const { return Jd(to_jd()); }


		/**	Assign and convert from Jd type to Hebrew type. */
		Hebrew& operator = (Jd const& jd) {
			from_jd(jd.jd());
			return *this;
		}


		// block some operators
	private:
		Hebrew operator + (detail::packaged_year_real const&);
		Hebrew operator - (detail::packaged_year_real const&);
		Hebrew operator + (detail::packaged_month_real const&);
		Hebrew operator - (detail::packaged_month_real const&);
	};

	// OPERATORS
	// --------------------------------------------------------------------------------------

	/** Hebrew + (integer month) */
	Hebrew operator + (Hebrew const& dt, detail::packaged_month_integer const& month);

	/** Hebrew - (integer month) */
	inline Hebrew operator - (Hebrew const& dt, detail::packaged_month_integer const& month) { return dt + detail::packaged_month_integer(-month.nMonths_); }

	/**	Hebrew + (integer year) */
	Hebrew operator + (Hebrew const& dt, detail::packaged_year_integer const& year);

	/**	Hebrew - (integer year) */
	inline Hebrew operator - (Hebrew const& dt, detail::packaged_year_integer const& year) { return dt + detail::packaged_year_integer(-year.nYears_); }

	/** Stream insertion operator. */
	inline std::ostream& operator << (std::ostream& os, Hebrew const& i) { return os << i.to_string(); }

	year_t year(Hebrew i);
	month_t month(Hebrew i);
	day_t day(Hebrew i);
	hour_t hour(Hebrew i);
	minute_t minute(Hebrew i);
	second_t second(Hebrew i);

} // end-of-namespace khronos