#pragma once
#include <string>
#include <fstream>
#include "BookItem.h"
#include "Member.h"
#include "BookItem.h"

#define FINE_VIETNAMESE_BOOK 20000
#define FINE_FOREIGN_BOOK 10000

class Fine
{
private:
	std::string _memberId;
	std::string _barcode;

public:
	static double collectFine(std::string barcode, uint32_t days);
};

