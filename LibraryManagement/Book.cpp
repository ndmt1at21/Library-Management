#include "Book.h"

Book::Book()
{
	_numberOfPages = 0;
	_bookFormat = BookFormat::CULTURAL;
}

Book::Book(string isbn, string title, string publisher, string lang, uint32_t numPage,
	BookFormat bookFormat, std::vector<string> authorsName)
{
	_ISBN = isbn;
	_title = title;
	_publisher = publisher;
	_language = lang;
	_numberOfPages = numPage;
	_bookFormat = bookFormat;
	_authorsName = authorsName;
}

Book::Book(const Book& book)
{
	_ISBN = book._ISBN;
	_title = book._title;
	_publisher = book._publisher;
	_language = book._language;
	_numberOfPages = book._numberOfPages;
	_bookFormat = book._bookFormat;
	_authorsName = book._authorsName;
}

Book::~Book() {}

string Book::getISBN()
{
	return _ISBN;
}

string Book::getTitle()
{
	return _title;
}

string Book::getPublisher()
{
	return _publisher;
}

string Book::getLanguage()
{
	return _language;
}

uint32_t Book::getNumberOfPages()
{
	return _numberOfPages;
}

BookFormat Book::getBookFormat()
{
	return _bookFormat;
}

std::vector<string> Book::getAuthorsName()
{
	return _authorsName;
}

std::ifstream& operator>>(std::ifstream& in, Book& book)
{
	std::getline(in, book._ISBN, '\n');
	std::getline(in, book._title, '\n');
	std::getline(in, book._publisher, '\n');
	std::getline(in, book._language, '\n');
	in >> book._numberOfPages;

	int bookFormat;
	in >> bookFormat;
	book._bookFormat = BookFormat(bookFormat);

	size_t numAuthor;
	in >> numAuthor;
	in.get(); //bỏ '\n'

	book._authorsName.clear();
	for (size_t i = 0; i < numAuthor; i++)
	{
		std::string tmp;
		std::getline(in, tmp, '\n');
		book._authorsName.push_back(tmp);
	}

	return in;
}

std::istream& operator>>(std::istream& in, Book& book)
{
	std::cout << "Tua sach: ";
	std::getline(in, book._title, '\n');

	std::cout << "Nha xuat ban: ";
	std::getline(in, book._publisher, '\n');

	std::cout << "Ngon ngu: ";
	std::getline(in, book._language, '\n');

	std::cout << "So trang: ";
	in >> book._numberOfPages;
	in.get();

	std::cout << "ISBN: ";
	std::getline(in, book._ISBN, '\n');

	std::cout << "The loai (0: Van hoa, 1: self-help, 2: sach hoc ngoai ngu, 3: van hoc): ";
	int bookFormat;
	in >> bookFormat;
	book._bookFormat = BookFormat(bookFormat);

	std::cout << "So tac gia: ";
	size_t numAuthor;
	in >> numAuthor;
	in.get(); //bỏ '\n'

	std::cout << "Ten tac gia: ";
	book._authorsName.clear();
	for (size_t i = 0; i < numAuthor; i++)
	{
		std::string tmp;
		std::getline(in, tmp, '\n');
		book._authorsName.push_back(tmp);
	}

	return in;
}

std::ostream& operator<<(std::ostream& out, const Book& book)
{
	out << std::left << std::setw(30) << "ISBN:" << book._ISBN << '\n';
	out << std::setw(30) << "Title:" << book._title << '\n';
	out << std::setw(30) << "Nha xuat ban:" << book._publisher << '\n';
	out << std::setw(30) << "Ngon ngu: " << book._language << '\n';
	out << std::setw(30) << "So trang: " << book._numberOfPages << '\n';
	out << std::setw(30) << "Loai:"<< int(book._bookFormat) << '\n';
	out << std::setw(30) << "Tac gia:";
	for (size_t i = 0; i < book._authorsName.size(); i++)
		out << book._authorsName[i] << "; ";
	out << '\n';
	return out;
}

std::ofstream& operator<<(std::ofstream& out, const Book& book)
{
	out << book._ISBN << '\n';
	out << book._title << '\n';
	out << book._publisher << '\n';
	out << book._language << '\n';
	out << book._numberOfPages << '\n';
	out << int(book._bookFormat) << '\n';
	out << book._authorsName.size() << '\n';

	for (size_t i = 0; i < book._authorsName.size() - 1; i++)
		out << book._authorsName[i] << "\n";
	out << book._authorsName.back();

	return out;
}