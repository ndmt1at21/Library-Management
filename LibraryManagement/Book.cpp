#include "Book.h"

Book::Book()
{
	_numberOfPages = 0;
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


std::istream& operator>>(std::istream& in, Book& book)
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
std::ostream& operator<<(std::ostream& out, const Book& book)
{
	out << book._ISBN << '\n';
	out << book._title << '\n';
	out << book._publisher << '\n';
	out << book._language << '\n';
	out << book._numberOfPages << '\n';
	out << int(book._bookFormat) << '\n';
	out << book._authorsName.size() << '\n';

	for (size_t i = 0; i < book._authorsName.size() - 1; i++)
		out << book._authorsName[i] << "\n\t\t\t\t";
	out << book._authorsName.back();

	return out;
}