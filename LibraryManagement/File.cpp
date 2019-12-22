#include "File.h"

bool File::is_empty_file(std::ifstream& in)
{
	std::streamoff cur = in.tellg();

	in.seekg(0, std::ios::end);
	std::streampos tmp = in.tellg();
	in.seekg(cur);

	if (tmp == 0)
		return true;
	return false;
}

bool File::is_empty_file(std::ofstream& out)
{
	std::streamoff cur = out.tellp();

	out.seekp(0, std::ios::end);
	std::streampos tmp = out.tellp();
	out.seekp(cur);

	if (tmp == 0)
		return true;
	return false;
}