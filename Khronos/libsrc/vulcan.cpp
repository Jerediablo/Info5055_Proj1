/**	@file vulcan.cpp
	@author Garth Santor
	@date 2014-09-29

	Vulcan calendar class implementation.
	*/

#include <khronos/vulcan_calendar.hpp>

#include <sstream>
#include <iomanip>

namespace khronos {

	jd_t vulcan_to_jd(year_t year, month_t month, day_t day) {
		double y = 266.4;
		double m = y / 12;
		double d = m / 21;
		return (year * y) + (month * m) + (day * d) + VULCAN_EPOCH - (y + m + d);		
	}

	jd_t vulcan_to_jd(year_t year, month_t month, day_t day, hour_t hour, minute_t minute, second_t second) {
		jd_t jdn = vulcan_to_jd(year, month, day);
		double h = ((266.4 / 12) / 21) / 18;
		double min = h / 54;
		double s = min / 54;
		return jdn + (hour * h) + (minute * min) + (second * s);
	}

	void jd_to_vulcan(jd_t jd, year_t& year, month_t& month, day_t& day) {
		double y = 266.4;
		double m = y / 12;
		double d = m / 21;

		jd_t jdVal = jd - VULCAN_EPOCH + y + m + d;
		year = static_cast<year_t>(jdVal / y);
		if (year < 0)
			year--;
		jdVal = utility::mod(jdVal, y);
		month = static_cast<month_t>(jdVal / m);
		jdVal = utility::mod(jdVal, m);
		day = static_cast<day_t>(jdVal / d);
	}

	void jd_to_vulcan(jd_t jd, year_t& year, month_t& month, day_t& day, hour_t& hour, minute_t& minute, second_t& second) {
		double y = 266.4;
		double m = y / 12;
		double d = m / 21;
		double h = ((266.4 / 12) / 21) / 18;
		double min = h / 54;
		double s = min / 54;

		jd_t jdVal = jd - VULCAN_EPOCH + y + m + d;
		jdVal = utility::mod(jdVal, y);
		jdVal = utility::mod(jdVal, m);
		jdVal = utility::mod(jdVal, d);

		jd_to_vulcan(jd, year, month, day);

		hour = static_cast<hour_t>(jdVal / h);
		jdVal = utility::mod(jdVal, h);
		minute = static_cast<minute_t>(jdVal/ min);
		jdVal = utility::mod(jdVal, min);
		second = static_cast<second_t>(floor(jdVal / s));
	}

	Vulcan::Vulcan() {
		from_jd(Jd().jd());
	}

	Vulcan::Vulcan(has_time_of_day status)
	{
		if (status == 0) {
			from_jd(Jd().jd());
			hour_ = 0;
			minute_ = 0;
			second_ = 0;
		}
		else if (status == 1) {
			from_jd(Jd().jd());
		}
	}

	std::string Vulcan::to_string() const {
		std::ostringstream oss;

		oss << vulcan_month_name(month_) << ' ' << (unsigned)day_ << ", ";

		oss << year_ << ' ';

		oss << hour_;
		oss << ":" << std::setfill('0') << std::setw(2) << minute_;
		oss << ":" << std::setfill('0') << std::setw(2) << second_;
		
		return oss.str();
	}

	year_t year(Vulcan v) {
		return v.year();
	}

	month_t month(Vulcan v) {
		return v.month();
	}

	day_t day(Vulcan v) {
		return v.day();
	}

	hour_t hour(Vulcan v) {
		return v.hour();
	}

	minute_t minute(Vulcan v) {
		return v.minute();
	}

	second_t second(Vulcan v) {
		return v.second();
	}

	// Add days ( + operator )
	Vulcan operator + (Vulcan const& dt, detail::packaged_day const& n) {

		year_t y = static_cast<year_t>(dt.year() + n.nDays_ / 266.4);
		month_t m = dt.month() + static_cast<month_t>(floor(utility::mod(n.nDays_, 266.4) / 21));
		day_t d = dt.day() + n.nDays_;

		hour_t hour = dt.hour();
		minute_t minute = dt.minute();
		second_t second = dt.second();

		return Vulcan(y, m, d, hour, minute, second);
	}
	 
	// Add months ( + operator )
	Vulcan operator + (Vulcan const& dt, detail::packaged_month_integer const& n) {

		year_t y = dt.year() + n.nMonths_ / 12;
		month_t m = dt.month() + n.nMonths_ % 12;

		day_t d = dt.day();
		hour_t hour = dt.hour();
		minute_t minute = dt.minute();
		second_t second = dt.second();

		return Vulcan(y, m, d, hour, minute, second);
	}

	// Add years ( + operator )
	Vulcan operator + (Vulcan const& dt, detail::packaged_year_integer const& n) {

		year_t y = dt.year() + n.nYears_;

		month_t m = dt.month();
		day_t d = dt.day();
		hour_t hour = dt.hour();
		minute_t minute = dt.minute();
		second_t second = dt.second();

		return Vulcan(y, m, d, hour, minute, second);
	}
}