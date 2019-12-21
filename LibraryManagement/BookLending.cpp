#include "BookLending.h"

BookLending::BookLending() {}

BookLending::BookLending(Date createDate, Date dueDate, string barcode, string memberId)
{
	_createDate = createDate;
	_dueDate = dueDate;
	_bookItemBarcode = barcode;
	_memberId = memberId;
}


BookLending::BookLending(const BookLending& bookLending)
{
	_createDate = bookLending._createDate;
	_dueDate = bookLending._dueDate;
	_bookItemBarcode = bookLending._bookItemBarcode;
	_memberId = bookLending._memberId;
}

BookLending::~BookLending() {}

Date BookLending::getDueDate()
{
	return _dueDate;
}

string BookLending::getBookItemBarCode()
{
	return _bookItemBarcode;
}

string BookLending::getMemberId()
{
	return _memberId;
}

void BookLending::lendBook(string barcode, string memberId)
{
	std::ifstream
}

std::vector<BookLending> BookLending::fetchLendingDetails(string memberId)
{

}


std::istream& operator>>(std::istream& in, BookLending& bookLending)
{
	in >> bookLending._createDate;
	in >> bookLending._dueDate;
	std::getline(in, bookLending._bookItemBarcode, '\n');
	std::getline(in, bookLending._memberId, '\n');
}

std::ostream& operator<<(std::ostream& out, const BookLending& bookLending)
{
	out << bookLending._createDate << '\n';
	out << bookLending._dueDate << '\n';
	out << bookLending._bookItemBarcode << '\n';
	out << bookLending._memberId << '\n';
}