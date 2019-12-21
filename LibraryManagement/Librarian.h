#pragma once
#include <iostream>
#include <fstream>
#include "Account.h"
#include "BookItem.h"
#include "Member.h"

#define link_data_account "information_account.txt" 

class Librarian :public Account
{
public:
	void addBookItem(BookItem bookItem);
	bool modifyBook(BookItem bookItemMod);
	bool removeBook(string barCode);
	bool blockMember(string id);
	bool unblockMember(Member member);

	size_t getNumberOfMember();
	bool searchMember(string id);
	void showAllMember();
};

