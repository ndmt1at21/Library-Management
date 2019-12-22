#include "StringProcess.h"
#include <algorithm>

void erase_space(std::string& str)
{
	str.erase(std::remove(str.begin(), str.end(), ' '), str.end());
}

std::string tolower(std::string str)
{
	for (size_t i = 0; i < str.size(); i++)
		str[i] = tolower(str[i]);
	return str;
}

bool isAllDigit(std::string str)
{
	for (size_t i = 0; i < str.size(); i++)
		if (str[i] > '9' || str[i] < '0')
			return false;
	return true;
}