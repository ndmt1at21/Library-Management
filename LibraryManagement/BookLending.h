#pragma once
#include "Date.h"
#include <iostream>
#include <string>
#include <vector>

#define link_lending_book "lending_information"

using std::string;

class BookLending
{
private:
	Date _createDate;
	Date _dueDate;
	string _bookItemBarcode;
	string _memberId;

public:
	BookLending();
	BookLending(Date, Date, string, string);
	BookLending(const BookLending& bookLending);
	~BookLending();

	Date getDueDate();
	string getBookItemBarCode();
	string getMemberId();

	void lendBook(string barcode, string memberId);
	std::vector<BookLending> fetchLendingDetails(string memberId);

	friend std::istream& operator>>(std::istream& in, BookLending& bookLending);
	friend std::ostream& operator<<(std::ostream& out, const BookLending& bookLending);
};

