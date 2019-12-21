#include "Directory.h"

std::string Directory::getDir(std::string linkFile)
{
	size_t last_slash = linkFile.find_last_of("\\/");

	if (last_slash == std::string::npos)
		return "";

	std::string dir(linkFile, 0, last_slash);
	return dir;
}