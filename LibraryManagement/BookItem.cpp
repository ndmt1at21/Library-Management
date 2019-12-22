#include "BookItem.h"
#include <iomanip>
#include "Directory.h"

BookItem::BookItem() 
	:_numberAvailableBook(0), _bookStatus(BookStatus::LOANED) {}

BookItem::BookItem(string barCode, Rack place, BookStatus bookStatus, uint32_t numAvailable,
	string isbn, string title, string publisher, string language, 
	uint32_t numberPages, BookFormat bookFormat, std::vector<string> authors)
	:Book(isbn, title, publisher, language, numberPages, bookFormat, authors)
{
	_barCode = barCode;
	_placeAt = place;
	_bookStatus = bookStatus;
	_numberAvailableBook = numAvailable;

}

BookItem::BookItem(const BookItem& bookItem) :Book(bookItem)
{
	_barCode = bookItem._barCode;
	_placeAt = bookItem._placeAt;
	_bookStatus = bookItem._bookStatus;
	_numberAvailableBook = bookItem._numberAvailableBook;
}

BookItem::~BookItem() {}

string BookItem::getBarCode()
{
	return _barCode;
}

Rack BookItem::getPlaceAt()
{
	return _placeAt;
}

BookStatus BookItem::getBookStatus()
{
	return _bookStatus;
}

uint32_t BookItem::getNumberAvailableBook()
{
	return _numberAvailableBook;
}

void BookItem::setBookStatus()
{
	if (_numberAvailableBook == 0)
		_bookStatus = BookStatus::LOANED;
}

void BookItem::decreaseNumberAvailableBook()
{
	_numberAvailableBook--;
}

void BookItem::viewBookInformation(std::ostream& out)
{
	out << std::left << std::setw(40) << _title;
	out << std::setw(20) << _barCode;
	switch (_bookFormat)
	{
	case BookFormat::CULTURAL:
		out << std::setw(25) << "Van hoa";
		break;

	case BookFormat::SELF_HELF:
		out << std::setw(25) << "Self-help";
		break;

	case BookFormat::FOREIGN_LANGUAGE_LEARNING:
		out << std::setw(25) << "Sach hoc ngoai ngu";
		break;

	case BookFormat::LITERATURE:
		out << std::setw(25) << "Van hoc";
		break;

	default:
		out << std::setw(25) << "Khong ro";
		break;
	}

	switch (_bookStatus)
	{
	case BookStatus::AVAILABLE:
		out << std::setw(10) << "Co san";
		break;

	case BookStatus::LOANED:
		out << std::setw(10) << "Da muon";
		break;

	default :
		out << std::setw(10) << "None";
	}

	out << std::setw(10) << _placeAt;
	for (size_t i = 0; i < _authorsName.size(); i++)
		out << _authorsName[i] << "\n";
}

std::istream& operator>>(std::istream& in, BookItem& book)
{
	operator>>(in, static_cast<Book&>(book));

	std::cout << "Barcode: ";
	std::getline(in, book._barCode, '\n');

	std::cout << "Vi tri ke (day-ke-thu tu): ";
	in >> book._placeAt;

	std::cout << "So sach hien co: ";
	in >> book._numberAvailableBook;
	in.get();

	if (book._numberAvailableBook == 0)
		book._bookStatus = BookStatus::LOANED;
	else book._bookStatus = BookStatus::AVAILABLE;

	return in;
}

std::ifstream& operator>>(std::ifstream& in, BookItem& book)
{
	std::getline(in, book._barCode, '\n');
	in >> book._placeAt;

	int bookStatus;
	in >> bookStatus;
	book._bookStatus = BookStatus(bookStatus);

	in >> book._numberAvailableBook;
	in.get();

	operator>>(in, static_cast<Book&>(book));

	return in;
}

std::ostream& operator<<(std::ostream& out, const BookItem& book)
{
	operator<<(out, static_cast<const Book&>(book));
	out << std::left << std::setw(30) << "Barcode: " << book._barCode << '\n';
	out << std::setw(30) << "Vi tri ke: " << book._placeAt << '\n';
	out << std::setw(30) << "Status: " << int(book._bookStatus) << '\n';
	out << std::setw(30) << "So sach co san: " << book._numberAvailableBook << '\n';

	return out;
}

std::ofstream& operator<<(std::ofstream& out, const BookItem& book)
{
	out << book._barCode << '\n';
	out << book._placeAt << '\n';
	out << int(book._bookStatus) << '\n';
	out << book._numberAvailableBook << '\n';
	operator<<(out, static_cast<const Book&>(book));

	return out;
}

bool BookItem::checkout(string barcode)
{
	std::ifstream infile_book(link_book_information);
	if (infile_book.fail())
		throw std::exception("file not found");

	std::string linkTmp = Directory::getDir(link_book_information) + "tmp.txt";
	std::ofstream file_temp(linkTmp);

	int i = 0;
	while (!infile_book.eof())
	{
		BookItem book;
		infile_book >> book;

		if (book.getBarCode() == barcode)
		{
			if (book._numberAvailableBook == 0)
			{
				book._bookStatus = BookStatus::LOANED;
				return false;
			}

			if (book._bookStatus == BookStatus::LOANED)
			{
				ShowError("Sach da duoc muon");
				return false;
			}
			book._numberAvailableBook--;
		}

		if (i == 0)
		{
			file_temp << book;
			i++;
		}
		else
		{
			file_temp << '\n';
			file_temp << book;
		}
	}
	infile_book.close();
	file_temp.close();

	remove(link_book_information);
	rename(linkTmp.c_str(), link_book_information);

	return true;
}

bool BookItem::returnBook(string barcode)
{
	std::ifstream infile_book(link_book_information);
	if (infile_book.fail())
		throw std::exception("file not found");

	std::string linkTmp = Directory::getDir(link_book_information) + "tmp.txt";
	std::ofstream file_temp(linkTmp);

	int i = 0;
	while (!infile_book.eof())
	{
		BookItem book;
		infile_book >> book;

		if (book.getBarCode() == barcode)
		{
			book._numberAvailableBook++;
			book._bookStatus = BookStatus::AVAILABLE;
		}

		if (i == 0)
		{
			file_temp << book;
			i++;
		}
		else
		{
			file_temp << '\n';
			file_temp << book;
		}
	}
	infile_book.close();
	file_temp.close();

	remove(link_book_information);
	rename(linkTmp.c_str(), link_book_information);

	return true;
}