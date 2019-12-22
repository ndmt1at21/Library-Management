#pragma once
#include "Book.h"
#include "Date.h"
#include "Rack.h"
#include "BookLending.h"

#define link_book_information "book_information.txt"

class BookItem : public Book
{
private:
	string _barCode;
	Rack _placeAt;
	BookStatus _bookStatus;
	uint32_t _numberAvailableBook;

public:
	BookItem();
	BookItem(string barCode, Rack place, BookStatus bookStatus, uint32_t numAvailable,
		string isbn, string title, string publisher, string language,
		uint32_t numberPages, BookFormat bookFormat, std::vector<string> authors);
	BookItem(const BookItem& book);
	~BookItem();

	string getBarCode();
	Rack getPlaceAt();
	BookStatus getBookStatus();
	uint32_t getNumberAvailableBook();

	void setBookStatus();
	void decreaseNumberAvailableBook();

	friend std::istream& operator>>(std::istream& in, BookItem& book);
	friend std::ifstream& operator>>(std::ifstream& in, BookItem& book);
	friend std::ostream& operator<<(std::ostream& out, const BookItem& book);
	friend std::ofstream& operator<<(std::ofstream& out, const BookItem& book);
	
	void viewBookInformation(std::ostream& out);
	bool checkout();
};

