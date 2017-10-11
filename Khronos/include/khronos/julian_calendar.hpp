#pragma once

/**	@file khronos/julian_calendar.hpp
	@author Garth Santor
	@date 2013-09-19

	Julian calendar functions and class declaration.
	*/

#include <khronos/def.hpp>
#include <khronos/calendar.hpp>
#include <khronos/julian_day.hpp>

#include <type_traits>
#include <string>

namespace khronos {

	constexpr year_t operator ""_BC(unsigned long long julianYearBC) { return -static_cast<long long>(julianYearBC) + 1; }
	constexpr year_t operator ""_bc(unsigned long long julianYearBC) { return -static_cast<long long>(julianYearBC) + 1; }

	jd_t julian_to_jd(year_t year, month_t month, day_t day);
	jd_t julian_to_jd(year_t year, month_t month, day_t day, hour_t hour, minute_t minute, second_t seconds);
	void jd_to_julian(jd_t jd, year_t& year, month_t& month, day_t& day);
	void jd_to_julian(jd_t jd, year_t& year, month_t& month, day_t& day, hour_t& hour, minute_t& minute, second_t& second);

	bool is_julian_leapyear(year_t year);

	inline day_t julian_days_in_month(month_t month, bool isLeapYear) {
		return civil::days_in_month(month, isLeapYear);
	}

	inline char const * julian_month_name(month_t month) {
		return civil::month_name_long(month);
	}

	inline char const * julian_short_month_name(month_t month) {
		return civil::month_name_short(month);
	}


	class Julian {
		year_t		year_ = 1;
		month_t		month_ = 1;
		day_t		day_ = 1;
		hour_t		hour_ = 0;
		minute_t	minute_ = 0;
		second_t	second_ = 0;

		void from_jd(jd_t jd) { jd_to_julian(jd, year_, month_, day_, hour_, minute_, second_); }
		jd_t to_jd() const { return julian_to_jd(year_, month_, day_, hour_, minute_, second_); }
	public:
		Julian();

		Julian(has_time_of_day status);

		/** Get the year.
		@return Astronomical year. */
		year_t  year() const { return year_; }


		/** Get the month.
		@return Month number [1..12] */
		month_t month() const { return month_; }


		/** Get the day of the month.
		@return Day of month number [1..31]. */
		day_t   day() const { return day_; }

		hour_t  hour() const { return hour_; }

		minute_t	minute() const { return minute_; }

		second_t	 second() const { return second_; }
	

		Julian(year_t year, month_t month, day_t day) : year_(year), month_(month), day_(day) {}

		Julian(year_t year, month_t month, day_t day, hour_t hour, minute_t minute, second_t second) :
			year_(year), month_(month), day_(day), hour_(hour), minute_(minute), second_(second) {}

		/** Construct a Julian date from Julian Day Number object.
		@param jd [in] Jd object.
		*/
		Julian(Jd const& jd) { from_jd(jd.jd()); }


		std::string to_string() const;


		/**	Implicit cast to Jd class. */
		operator Jd () const { return Jd(to_jd()); }


		/**	Assign and convert from Jd type to Julian type. */
		Julian& operator = (Jd const& jd) {
			from_jd(jd.jd());
			return *this;
		}


		// block some operators
		private:
		Julian operator + (detail::packaged_year_real const&);
		Julian operator - (detail::packaged_year_real const&);
		Julian operator + (detail::packaged_month_real const&);
		Julian operator - (detail::packaged_month_real const&);
	};



	// OPERATORS
	// ====================

	/** Julian + (integer month) */
	Julian operator + (Julian const& dt, detail::packaged_month_integer const& month);

	/** Julian - (integer month) */
	inline Julian operator - (Julian const& dt, detail::packaged_month_integer const& month) { return dt + detail::packaged_month_integer(-month.nMonths_); }

	/**	Julian + (integer year) */
	Julian operator + (Julian const& dt, detail::packaged_year_integer const& year);

	/**	Julian - (integer year) */
	inline Julian operator - (Julian const& dt, detail::packaged_year_integer const& year) { return dt + detail::packaged_year_integer(-year.nYears_); }

	/** Stream insertion operator. */
	inline std::ostream& operator << (std::ostream& os, Julian const& j) { return os << j.to_string(); }

	year_t year(Julian j);
	month_t month(Julian j);
	day_t day(Julian j);
	hour_t hour(Julian j);
	minute_t minute(Julian j);
	second_t second(Julian j);

}