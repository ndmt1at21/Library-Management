#include "BookItem.h"
#include <iomanip>

BookItem::BookItem() :_numberAvailableBook(0) {}

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

	for (size_t i = 0; i < _authorsName.size(); i++)
		out << _authorsName[i] << "\n";
}

void BookItem::updateBookStatus()
{
	if (_numberAvailableBook == 0)
		_bookStatus = BookStatus::LOANED;
}

void BookItem::decreaseNumberAvailableBook()
{
	_numberAvailableBook--;
}

std::istream& operator>>(std::istream& in, BookItem& book)
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
	out << book._barCode << '\n';
	out << book._placeAt << '\n';
	out << int(book._bookStatus) << '\n';
	out << book._numberAvailableBook << '\n';
	operator<<(out, static_cast<const Book&>(book));

	return out;
}

bool BookItem::checkout()
{
	if (_numberAvailableBook == 0)
	{
		_bookStatus = BookStatus::LOANED;
		return false;
	}

	if (_bookStatus == BookStatus::LOANED)
	{
		ShowError("Sach da duoc muon");
		return false;
	}

	decreaseNumberAvailableBook();
	updateBookStatus();

	return true;
}