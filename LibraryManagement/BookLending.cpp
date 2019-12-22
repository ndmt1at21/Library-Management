#include "BookLending.h"
#include "File.h"
#include "Directory.h"
#include "Account.h"
#include "Member.h"

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

Date BookLending::getCreateDate()
{
	return _createDate;
}

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

bool BookLending::lendBook(string barcode, string memberId)
{
	if (!BookItem::checkout(barcode))
		return false;

	Member::increaseTotalBooksCheckedout(memberId);
	
	Date dateNow;
	dateNow.getDateNow();

	std::ofstream outfile_lending(link_lending_book, std::ios::app);
	if (outfile_lending.fail())
		return false;

	this->_bookItemBarcode = barcode;
	this->_memberId = memberId;
	this->_createDate.getDateNow();
	this->_dueDate = _createDate + MAX_LENDING_DAY;

	bool isEmptyFile = File::is_empty_file(outfile_lending);
	if (isEmptyFile)
		outfile_lending << *this;
	else outfile_lending << '\n' << *this;

	return true;
}

bool BookLending::deleteLendingBook(string barcode, string memberId)
{
	if (!BookItem::returnBook(barcode))
		return false;

	std::ifstream infile_lending(link_lending_book);
	if (infile_lending.fail())
		throw std::exception("file not found");

	std::string linkTmp((Directory::getDir(link_lending_book) + "tmp.txt"));
	std::ofstream temp(linkTmp);

	bool isAvailbale = false;
	while (!infile_lending.eof())
	{
		BookLending bookLending;
		infile_lending >> bookLending;

		if (bookLending.getMemberId() != memberId || bookLending.getBookItemBarCode() != barcode)
			temp << bookLending;
		else isAvailbale = true;
	}

	if (!isAvailbale)
		return false;

	infile_lending.close();
	temp.close();

	remove(link_lending_book);
	if (!rename(linkTmp.c_str(), link_lending_book))
		return false;

	return true;
}

bool BookLending::updateDueDate(string barcode, string memberId)
{
	std::ifstream infile_lending(link_lending_book);
	if (infile_lending.fail())
		throw std::exception("file not found");

	std::string linkTmp((Directory::getDir(link_lending_book) + "tmp.txt"));
	std::ofstream temp(linkTmp);

	bool isAvailbale = false;
	while (!infile_lending.eof())
	{
		BookLending bookLending;
		infile_lending >> bookLending;

		if (bookLending.getMemberId() == memberId && bookLending.getBookItemBarCode() == barcode)
		{
			bookLending._createDate.getDateNow();
			bookLending._dueDate = bookLending._createDate + MAX_LENDING_DAY;
			isAvailbale = true;
		}	
		temp << bookLending;
	}

	if (!isAvailbale)
		return false;

	infile_lending.close();
	temp.close();

	remove(link_lending_book);
	if (!rename(link_lending_book, linkTmp.c_str()))
		return false;

	return true;
}

std::vector<BookLending> BookLending::fetchLendingDetails(string memberId)
{
	std::ifstream infile_lending(link_lending_book);

	std::vector<BookLending> listLending;
	while (!infile_lending.eof())
	{
		BookLending bookLending;
		infile_lending >> bookLending;

		if (bookLending.getMemberId() == memberId)
			listLending.push_back(bookLending);
	}
	
	return listLending;
}


std::istream& operator>>(std::istream& in, BookLending& bookLending)
{
	in >> bookLending._createDate;
	in >> bookLending._dueDate;
	std::getline(in, bookLending._bookItemBarcode, '\n');
	std::getline(in, bookLending._memberId, '\n');

	return in;
}

std::ostream& operator<<(std::ostream& out, const BookLending& bookLending)
{
	out << bookLending._createDate << '\n';
	out << bookLending._dueDate << '\n';
	out << bookLending._bookItemBarcode << '\n';
	out << bookLending._memberId;

	return out;
}