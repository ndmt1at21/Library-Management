#include "Date.h"
#include <sstream>

Date::Date()
{
	_day = 0;
	_mon = 0;
	_year = 0;
}

Date::Date(uint32_t day, uint32_t mon, uint32_t year)
{
	_day = day;
	_mon = mon;
	_year = year;
}

Date::Date(std::string dateStr)
{
	std::stringstream ss(dateStr);
	std::string tmp;

	//day
	std::getline(ss, tmp, '/');
	_day = uint32_t(std::stoi(tmp));

	//month
	std::getline(ss, tmp, '/');
	_mon = uint32_t(std::stoi(tmp));

	//year
	std::getline(ss, tmp, '/');
	_year = uint32_t(std::stoi(tmp));

	validDate();
}

Date::Date(const Date& other)
{
	_day = other._day;
	_mon = other._mon;
	_year = other._year;

	if (!validDate())
		throw std::logic_error("thoi gian khong dung dinh dang");
}

Date::~Date() {}

Date Date::operator+(uint32_t day)
{
	tm date;
	date.tm_mday = _day;
	date.tm_mon = _mon;
	date.tm_year = _year;

	date.tm_mday += day;
	
	Date newDate(date.tm_mday, date.tm_mon, date.tm_year);
	return newDate;
}

uint32_t Date::operator-(const Date& other)
{
	tm newDate{ 0 };
	newDate.tm_mday = other._day;
	newDate.tm_mon = other._mon;
	newDate.tm_year = other._year - 1900;

	tm curDate{ 0 };
	curDate.tm_mday = _day;
	curDate.tm_mon = _mon;
	curDate.tm_year = _year - 1900;

	uint64_t seconds = uint64_t(difftime(mktime(&curDate), mktime(&newDate)));
	uint32_t days = uint32_t(seconds / (60 * 60 * 24));
	
	return days;
}

bool Date::isLeafYear()
{
	if (_year % 4 == 0 && _year % 100 != 0 || _year % 400 == 0)
		return true;
	return false;
}

bool Date::validDate()
{
	if (_mon == 0 || _mon > 12)
		return false;

	switch (_mon)
	{
	case 1:
	case 3:
	case 5:
	case 7:
	case 8:
	case 10:
	case 12:
		if (_day > 31)
			return false;
		break;
	case 2:
		if (isLeafYear())
		{
			if (_day > 29)
				return false;
		}
		else if (_day > 28)
			return false;
		break;

	default:
		if (_day > 30)
			return false;
	}

	return true;
}

std::string Date::to_string() const
{
	std::stringstream ss;
	ss << _day << "/" << _mon << "/" << _year;

	return (ss.str());
}

void Date::getDateNow()
{
	time_t now = time(0);
	tm date;
	localtime_s(&date, &now);
	_day = date.tm_mday;
	_mon = date.tm_mon + 1;
	_year = date.tm_year + 1900;
}

std::istream& operator>>(std::istream& in, Date& date)
{
	std::string dateStr;
	std::getline(in, dateStr, '\n');
	date = Date(dateStr);

	return in;
}

std::ostream& operator<<(std::ostream& out, const Date date)
{
	out << date.to_string();
	return out;
}