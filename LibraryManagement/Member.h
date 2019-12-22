#pragma once
#include <iostream>
#include "Account.h"
#include "Date.h"
#include "BookLending.h"
#include <fstream>

class Member :public Account
{
private:
	Date _dateOfMembership;
	uint32_t _totalBooksCheckedout;

public:
	Member();
	Member(string, AccountStatus, string, Person, Date, uint32_t);

	Date getDateOfMembership();
	uint32_t getTotalCheckedoutBooks();

	void setDateOfMembership(Date date);
	void setTotalBooksCheckedout(uint32_t total);
	void increaseTotalBooksCheckedout();
	void decreaseTotalBooksCheckedout();

	bool resetPassword(string newPassWord);
	void registerNew();
	
	

	friend std::istream& operator>>(std::istream& in, Member& member);
	friend std::ifstream& operator>>(std::ifstream& in, Member& member);
	friend std::ostream& operator<<(std::ostream& out, const Member& member);

	bool checkoutBookItem(string barCode);
	bool returnItem(string barCode);
	bool renewItem(string barCode);
};

