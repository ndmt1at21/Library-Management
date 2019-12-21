#pragma once
#include "BookItem.h"
#include <iostream>
#include <fstream>
#include <string>
#include "Account.h"

using std::string;

class Search
{
public:
	virtual BookItem searchByTitle(string title) = 0;
	virtual BookItem searchByAuthor(string author) = 0;
	virtual BookItem searchByFormat(string type) = 0;
	virtual BookItem searchByBarCode(string barCode) = 0;
};

class Catalog :public Search
{
private:
	string _linkDataBook;

public:
	Catalog(string linkDatabase);
	bool searchByTitle(string title, BookItem& bookReturn);
	bool searchByAuthor(string author, BookItem& bookReturn);
	bool searchByFormat(string type, BookItem& bookReturn);
	bool searchByBarCode(string barCode, BookItem& bookReturn);
};

