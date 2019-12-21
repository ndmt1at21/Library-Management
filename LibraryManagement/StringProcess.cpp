#include "StringProcess.h"
#include <algorithm>

void erase_space(std::string& str)
{
	str.erase(std::remove(str.begin(), str.end(), ' '), str.end());
}