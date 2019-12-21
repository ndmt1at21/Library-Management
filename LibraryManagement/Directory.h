#pragma once/***********************************************************
* Author: Nguyễn Đức Minh Trí							   *
* Function: Xử lý các thao tác liên quan đến folder/file   *
* Date: 10/12/2019										   *
***********************************************************/

#pragma once
#include <cstring>
#include <io.h>
#include <iostream>
#include <vector>
#include <direct.h>
#include <string>
#include <fstream>
#include <direct.h>

class Directory
{
public:
	static std::string getDir(std::string linkFiles);
};

