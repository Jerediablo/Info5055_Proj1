/**	@file Jdn.cpp
	@author Garth Santor
	@date 2012-09-16

	Date and time library to_string method implementations.
	*/


#include <khronos/julian_day.hpp>
#include <khronos/gregorian_calendar.hpp>

#include <string>
#include <sstream>
#include <ctime>
#include <khronos/def.hpp>
using namespace std;

namespace khronos {

	/**	Jd default constructor.  Initialize to the current local time. */
	Jd::Jd()
		: jd_(0)
	{
		time_t nowTime = time(NULL);
		struct tm tmNow;
		localtime_s(&tmNow, &nowTime);
		jd_ = gregorian_to_jd(
			tmNow.tm_year + 1900,
			month_t(tmNow.tm_mon + 1),
			day_t(tmNow.tm_mday),
			hour_t(tmNow.tm_hour),
			minute_t(tmNow.tm_min),
			second_t(tmNow.tm_sec)
		);
	}
	



	/** Print the Julian Day as a string. */
	std::string Jd::to_string() const {
		ostringstream oss;
		oss << "JD " << jd_;
		return oss.str();
	}


	/** Jd + (integer year) operator. */
	Jd operator + (Jd const& dt, detail::packaged_year_real const& year) {
		return Jd(dt.jd() + year.nYears_ * EARTH_ORBITAL_PERIOD_DAYS);
	}
};