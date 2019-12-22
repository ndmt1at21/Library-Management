#include "Fine.h"
#include "StringProcess.h"

double Fine::collectFine(std::string barcode, uint32_t days)
{
	std::ifstream infile_book(link_book_information);
	if (infile_book.fail())
		throw std::exception("file not found");

	BookItem book;
	while (!infile_book.eof())
	{
		infile_book >> book;

		if (book.getBarCode() == barcode)
			break;
	}

	double fine = 0;
	std::string lang = book.getLanguage();
	lang = tolower(lang);
	erase_space(lang);

	if (lang == "vietnam")
		fine = FINE_VIETNAMESE_BOOK * days;
	else
		fine = FINE_FOREIGN_BOOK * days;

	return fine;
}