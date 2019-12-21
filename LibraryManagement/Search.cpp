#include "Search.h"

Catalog::Catalog(string linkDatabase) : _linkDataBook(linkDatabase) {}

bool Catalog::searchByTitle(string title, BookItem& bookReturn)
{
	std::ifstream infile_book(_linkDataBook);
	if (infile_book.fail())
		return false;

	BookItem tmp;
	while (true)
	{
		infile_book >> tmp;
		if (tmp.getBarCode().empty())
			break;

		if (title == tmp.getTitle())
			return true;
	}

	return false;
}

bool Catalog::searchByAuthor(string author, BookItem& book)
{
	return true;
}

BookItem searchByFormat(string type)
{
	BookItem book;
	return book;
}

BookItem searchByBarCode(string barCode)
{
	BookItem book;
	return book;
}