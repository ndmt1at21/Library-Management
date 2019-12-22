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
	//kiểm tra điều kiện member
	Date dateNow;
	dateNow.getDateNow();
	
	std::ifstream infile_member(link_member_information);
	if (infile_member.fail())
		throw std::exception("file not found");

	Member mem;
	while (!infile_member.eof())
	{

		infile_member >> mem;

		if (memberId == mem.getId() && dateNow > mem.getDateOfMembership())
		{
			ShowError("Tai khoan het han");
			return false;
		}
	}
	infile_member.seekg(0, std::ios::beg);
	mem.increaseTotalBooksCheckedout();

	if (mem.getTotalCheckedoutBooks() >= MAX_BOOK_ISSUE_FOR_A_USER)
	{
		ShowError("Ban khong the muon them sach");
		return false;
	}

	//kiểm tra tình trạng sách
	std::ifstream infile_book(link_book_information);
	if (infile_book.fail())
		throw std::exception("file not found");

	BookItem book;
	while (!infile_book.eof())
	{
		infile_book >> book;
		if (book.getBarCode() == barcode)
		{
			if (!book.checkout())
				return false;
			break;
		}
	}
	infile_book.seekg(0, std::ios::beg);
	book.decreaseNumberAvailableBook();

	//update thông tin
	string linkTmpMember = Directory::getDir(link_member_information) + "tmpMember.txt";
	string linkTmpBook = Directory::getDir(link_member_information) + "tmpBook.txt";

	std::ofstream tmp_member(linkTmpMember);
	std::ofstream tmp_book(linkTmpBook);
	std::ofstream outfile_lending(link_lending_book, std::ios::app);

	while (!tmp_member.eof())
	{
		Member memTmp;
		infile_member >> memTmp;

		if (memTmp.getId() == memberId)
			tmp_member << mem;
		tmp_member << memTmp;
	}

	while (!tmp_book.eof())
	{
		BookItem bookTmp;
		infile_book >> bookTmp;

		if (bookTmp.getBarCode() == barcode)
			tmp_book << book;
		tmp_member << bookTmp;
	}

	this->_bookItemBarcode = barcode;
	this->_memberId = memberId;
	this->_createDate.getDateNow();
	this->_dueDate = _createDate + MAX_LENDING_DAY;

	bool isEmptyFile = File::is_empty_file(outfile_lending);
	if (isEmptyFile)
		outfile_lending << *this;
	else outfile_lending << '\n' << *this;

	infile_book.close();
	infile_member.close();
	tmp_book.close();
	tmp_member.close();
	outfile_lending.close();

	remove(link_book_information);
	remove(link_member_information);
	rename(link_book_information, linkTmpBook.c_str());
	rename(link_member_information, linkTmpMember.c_str());

	return true;
}

bool BookLending::deleteLendingBook(string barcode, string memberId)
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

		if (bookLending.getMemberId() != memberId || bookLending.getBookItemBarCode() != barcode)
			temp << bookLending;
		else isAvailbale = true;
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