#pragma once
#include <time.h>
#include <ctime>
#include <iostream>
#include <string>


class Date
{
private:
	uint32_t _day;
	uint32_t _mon;
	uint32_t _year;

public:
	Date();
	Date(uint32_t day, uint32_t month, uint32_t year);
	Date(std::string dateStr);
	Date(const Date& other);
	~Date();

	Date operator+(uint32_t day);
	bool operator>(const Date& date);
	uint32_t operator-(const Date& other);

	bool isLeafYear();
	bool validDate();
	std::string to_string() const;

	void getDateNow();

	friend std::istream& operator>>(std::istream& in, Date& date);
	friend std::ostream& operator<<(std::ostream& out, const Date date);
};

