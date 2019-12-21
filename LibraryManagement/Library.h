#pragma once
#include <iostream>
#include "Account.h"
#include "BookItem.h"
#include "MyDefine.h"


class Library
{
private:
	size_t _numberOfBook;
	size_t _numberOfAccount;
	size_t _totalFine;

public:
	Library();
	Library(size_t, size_t, size_t);
	Library(const Library& lib);
	void updateNumberOfBook();
	void updateNumberOfAccount();
	void updateTotalFine(size_t fine);
};

