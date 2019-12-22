#pragma once
#include "BookItem.h"
#include "Account.h"
#include "StringProcess.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using std::string;

class SearchCatalog
{
public:
	static BookItem searchByTitle(string title);
	static std::vector<BookItem> searchByAuthor(string author);
	static std::vector<BookItem> searchByFormat(uint32_t type);
	static BookItem searchByBarCode(string barCode);
};

