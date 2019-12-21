#pragma once
#include <iostream>
#include "Account.h"
#include "Date.h"
#include <fstream>

class Member :public Account
{
private:
	Date _dateOfMembership;
	uint32_t _totalBooksCheckedout;

protected:
	void updatePassword(string newPassword);

public:
	Member();
	Member(string, AccountStatus, string, Person, Date, uint32_t);

	bool resetPassword(string id, string newPassWord);
	void registerNew();
	uint32_t getTotalCheckedoutBooks();

	friend std::istream& operator>>(std::istream& in, Member& member);
	friend std::ostream& operator<<(std::ostream& out, const Member& member);

	bool checkoutBookItem(BookItem book);
};

