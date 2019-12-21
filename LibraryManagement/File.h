#pragma once
#include <iostream>
#include <fstream>
#include <string>

class File
{
public:
	static bool is_empty_file(std::ifstream& in);
	static bool is_empty_file(std::ofstream& out);
};