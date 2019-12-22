#include "Search.h"

BookItem SearchCatalog::searchByTitle(string title)
{
	BookItem book;
	std::ifstream infile_book(link_book_information);
	if (infile_book.fail())
		return book;

	BookItem tmp;
	while (!infile_book.eof())
	{
		infile_book >> tmp;

		if (tolower(title) == tolower(tmp.getTitle()))
		{
			book = tmp;
			break;
		}
	}

	return book;
}

std::vector<BookItem> SearchCatalog::searchByAuthor(string author)
{
	std::vector<BookItem> books;
	std::ifstream infile_book(link_book_information);
	if (infile_book.fail())
		return books;

	BookItem tmp;
	while (!infile_book.eof())
	{
		infile_book >> tmp;

		std::vector<string> authors = tmp.getAuthorsName();
		for (size_t i = 0; i < authors.size(); i++)
		{
			if (tolower(author) == tolower(authors[i]))
			{
				books.push_back(tmp);
				break;
			}
		}
	}

	return books;
}

std::vector<BookItem> SearchCatalog::searchByFormat(uint32_t type)
{
	std::vector<BookItem> books;
	std::ifstream infile_book(link_book_information);
	if (infile_book.fail())
		return books;

	BookItem tmp;
	while (!infile_book.eof())
	{
		infile_book >> tmp;

		if (type == unsigned int(tmp.getBookFormat()))
			books.push_back(tmp);
	}

	return books;
}

BookItem SearchCatalog::searchByBarCode(string barCode)
{
	BookItem book;
	std::ifstream infile_book(link_book_information);
	if (infile_book.fail())
		return book;

	BookItem tmp;
	while (!infile_book.eof())
	{
		infile_book >> tmp;

		if (barCode == tmp.getBarCode())
		{
			book = tmp;
			break;
		}
	}

	return book;
}