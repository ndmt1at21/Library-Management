#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "MyDefine.h"

using std::string;

class Book
{
protected:
	string _ISBN;
	string _title;
	string _publisher;
	string _language;
	uint32_t _numberOfPages;
	BookFormat _bookFormat;
	std::vector<string> _authorsName;

public:
	Book();
	Book(string, string, string, string, uint32_t, BookFormat, std::vector<string> _authorsName);
	Book(const Book& book);
	virtual ~Book();

	string getISBN();
	string getTitle();
	string getPublisher();

	friend std::istream& operator>>(std::istream& in, Book& book);
	friend std::ostream& operator<<(std::ostream& out, const Book& book);
};

