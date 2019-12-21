#include "File.h"

bool File::is_empty_file(std::ifstream& in)
{
	in.seekg(0, std::ios::end);
	std::streampos tmp = in.tellg();
	in.seekg(0, std::ios::beg);

	if (tmp == 0)
		return true;
	return false;
}

bool File::is_empty_file(std::ofstream& out)
{
	out.seekp(0, std::ios::end);
	std::streampos tmp = out.tellp();
	out.seekp(0, std::ios::beg);

	if (tmp == 0)
		return true;
	return false;
}