#include "Library.h"

Library::Library() : _numberOfAccount(0), _numberOfBook(0), _totalFine(0) {}

Library::Library(size_t numberAccount, size_t numberBooks, size_t totalFine)
	: _numberOfAccount(numberAccount), _numberOfBook(numberBooks), _totalFine(totalFine) {}

Library::Library(const Library& lib)
{
	_numberOfAccount = lib._numberOfAccount;
	_numberOfBook = lib._numberOfBook;
	_totalFine = lib._totalFine;
}

void Library::updateNumberOfBook()
{
	_numberOfBook++;
}

void Library::updateNumberOfAccount()
{
	_numberOfAccount++;
}

void Library::updateTotalFine(size_t fine)
{
	_totalFine += fine;
}