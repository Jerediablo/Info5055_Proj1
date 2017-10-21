#pragma once

/**	@file vulcan.hpp
	@author Garth Santor
	@date 2014-09-29

	Vulcan calendar class and functions.
	*/

#include <khronos/calendar.hpp>
#include <khronos/def.hpp>
#include <khronos/julian_day.hpp>

#include <type_traits>
#include <string>


namespace khronos {

	inline day_t vulcan_days_in_month() {
		return 21;
	}

	inline char const * vulcan_month_name(month_t month) {
		return civil::vulcan_month_names(month);
	}

	jd_t vulcan_to_jd(year_t year, month_t month, day_t day);
	jd_t vulcan_to_jd(year_t year, month_t month, day_t day, hour_t hour, minute_t minute, second_t second);
	void jd_to_vulcan(jd_t jd, year_t& year, month_t& month, day_t& day);
	void jd_to_vulcan(jd_t jd, year_t& year, month_t& month, day_t& day, hour_t& hour, minute_t& minute, second_t& second);



	class Vulcan {
		year_t		year_ = 1;
		month_t		month_ = 1;
		day_t		day_ = 1;
		hour_t		hour_ = 0;
		minute_t	minute_ = 0;
		second_t	second_ = 0;

		void from_jd(jd_t jd) { jd_to_vulcan(jd, year_, month_, day_, hour_, minute_, second_); }
		jd_t to_jd() const { return vulcan_to_jd(year_, month_, day_, hour_, minute_, second_); }

	public:
		Vulcan();

		Vulcan(has_time_of_day status);

		year_t  year() const { return year_; }

		month_t month() const { return month_; }

		day_t   day() const { return day_; }

		hour_t  hour() const { return hour_; }

		minute_t	minute() const { return minute_; }

		second_t	 second() const { return second_; }


		Vulcan(year_t year, month_t month, day_t day) : year_(year), month_(month), day_(day) {}

		Vulcan(year_t year, month_t month, day_t day, hour_t hour, minute_t minute, second_t second) :
			year_(year), month_(month), day_(day), hour_(hour), minute_(minute), second_(second) {}

		/** Construct a Vulcan date from Vulcan Day Number object.
		@param jd [in] Jd object.
		*/
		Vulcan(Jd const& jd) { from_jd(jd.jd()); }


		std::string to_string() const;


		/**	Implicit cast to Jd class. */
		operator Jd () const { return Jd(to_jd()); }


		/**	Assign and convert from Jd type to Vulcan type. */
		Vulcan& operator = (Jd const& jd) {
			from_jd(jd.jd());
			return *this;
		}


		// block some operators
	private:
		Vulcan operator + (detail::packaged_year_real const&);
		Vulcan operator - (detail::packaged_year_real const&);
		Vulcan operator + (detail::packaged_month_real const&);
		Vulcan operator - (detail::packaged_month_real const&);
	};

	inline std::ostream& operator << (std::ostream& os, Vulcan const& i) { return os << i.to_string(); }

	Vulcan operator + (Vulcan const& dt, detail::packaged_day const& day);
	inline Vulcan operator - (Vulcan const& dt, detail::packaged_day const& month) { return dt + detail::packaged_day(-month.nDays_); }

	Vulcan operator + (Vulcan const& dt, detail::packaged_month_integer const& month);
	inline Vulcan operator - (Vulcan const& dt, detail::packaged_month_integer const& month) { return dt + detail::packaged_month_integer(-month.nMonths_); }

	Vulcan operator + (Vulcan const& dt, detail::packaged_year_integer const& year);
	inline Vulcan operator - (Vulcan const& dt, detail::packaged_year_integer const& year) { return dt + detail::packaged_year_integer(-year.nYears_); }


	year_t year(Vulcan v);
	month_t month(Vulcan v);
	day_t day(Vulcan v);
	hour_t hour(Vulcan i);
	minute_t minute(Vulcan v);
	second_t second(Vulcan v);
}