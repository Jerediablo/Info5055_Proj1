#pragma once

/*
File:		khronos/julian_day.hpp
Author:		Jeremy Peterson-Katz
Date:		October 21, 2017
*/

#include "calendar.hpp"
#include <string>
#include <iostream>


namespace khronos {

	/** Convert a Julian date to a Julian day number. */
	inline jdn_t jd_to_jdn(jd_t jd) {
		return static_cast<jdn_t>(floor(jd + 0.5));
	}

	// CLASSES
	// --------------------------------------------------------------------------------------

	/**	Julian Date (JN) class. */
	class Jd {
		jd_t	jd_;
	public:
		Jd();

		Jd(has_time_of_day status);

		/**	Constructor from real number. */
		Jd(jd_t jd) : jd_(jd) { }

		/**	Get the number of days. */
		jd_t jd() const { return jd_; }

		std::string to_string() const;
	};


	/** stream insertion operator. */
	inline std::ostream& operator << (std::ostream& os, Jd const& jd) {
		return os << jd.to_string();
	}


	// OPERATORS
	// --------------------------------------------------------------------------------------

	/** Jd relational operators. */
	inline bool operator == (Jd const& lhs, Jd const& rhs) { return lhs.jd() == rhs.jd(); }
	inline bool operator != (Jd const& lhs, Jd const& rhs) { return lhs.jd() != rhs.jd(); }
	inline bool operator <= (Jd const& lhs, Jd const& rhs) { return lhs.jd() <= rhs.jd(); }
	inline bool operator >= (Jd const& lhs, Jd const& rhs) { return lhs.jd() >= rhs.jd(); }
	inline bool operator <  (Jd const& lhs, Jd const& rhs) { return lhs.jd() <  rhs.jd(); }
	inline bool operator >  (Jd const& lhs, Jd const& rhs) { return lhs.jd() >  rhs.jd(); }


	/**Jd difference operator. */
	inline jd_t operator - (Jd const& lhs, Jd const& rhs) { return lhs.jd() - rhs.jd(); }


	/**	Day of the week. */
	inline day_t day_of_week(Jd const& jd) { return civil::day_of_week(jd.jd()); }


	/** Day addition/subtraction. */
	namespace detail {
		struct packaged_day {
			day_t nDays_;
			packaged_day(day_t d) : nDays_(d) { };
		};
	};
	inline detail::packaged_day days(day_t d) { return detail::packaged_day(d); }
	inline Jd operator + (Jd const& jdn, detail::packaged_day days) { return Jd(jdn.jd() + days.nDays_); }
	inline Jd operator - (Jd const& jdn, detail::packaged_day days) { return jdn.jd() - days.nDays_; }


	/** Week addition/subtraction. */
	namespace detail {
		struct packaged_week {
			day_t nWeeks_;
			packaged_week(day_t w) : nWeeks_(w) { };
		};
	};
	inline detail::packaged_week weeks(day_t w) { return detail::packaged_week(w); }
	inline Jd operator + (Jd const& jdn, detail::packaged_week weeks) { return jdn.jd() + weeks.nWeeks_ * 7.0; }
	inline Jd operator - (Jd const& jdn, detail::packaged_week weeks) { return jdn.jd() - weeks.nWeeks_ * 7.0; }


	//** Month addition/subtraction. */
	namespace detail {
		struct packaged_month_integer {
			month_t nMonths_;
			packaged_month_integer(month_t m) : nMonths_(m) { }
		};
		struct packaged_month_real {
			double nMonths_;
			packaged_month_real(double m) : nMonths_(m) { }
		};
	};
	inline detail::packaged_month_real months(double m) { return detail::packaged_month_real(m); }
	inline detail::packaged_month_real months(float m) { return detail::packaged_month_real(m); }
	template <typename T> inline detail::packaged_month_integer months(T m) { return detail::packaged_month_integer(month_t(m)); }


	//** Year addition/subtraction. */
	namespace detail {
		/** Year as integer number wrapper. */
		struct packaged_year_integer {
			year_t nYears_;
			packaged_year_integer(year_t y) : nYears_(y) { }
		};
		/** Year as real number wrapper. */
		struct packaged_year_real {
			double nYears_;
			packaged_year_real(double y) : nYears_(y) { }
		};
	};
	/** Wrap a double literal into a real year package. */
	inline detail::packaged_year_real years(double y) { return detail::packaged_year_real(y); }

	/** Wrap a float literal into a real year package. */
	inline detail::packaged_year_real years(float y) { return detail::packaged_year_real(y); }

	/** Wrap all other literals into an integer year package (if possible). */
	template<typename T> inline detail::packaged_year_integer years(T y) { return detail::packaged_year_integer(static_cast<year_t>(y)); }

	/**	JD + (real years) */
	Jd operator + (Jd const& dt, detail::packaged_year_real const& year);

	/**	JD - (real years) */
	inline Jd operator - (Jd const& dt, detail::packaged_year_real const& year) { return dt + detail::packaged_year_real(-year.nYears_); }

	/**	JD + (integer year) */
	inline Jd operator + (Jd const& dt, detail::packaged_year_integer const& year) { return dt + detail::packaged_year_real((double)year.nYears_); }

	/**	JD - (integer year) */
	inline Jd operator - (Jd const& dt, detail::packaged_year_integer const& year) { return dt + detail::packaged_year_integer(-year.nYears_); }

};  // end-of-namespace khronos

