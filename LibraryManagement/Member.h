#pragma once
#include <iostream>
#include "Account.h"
#include "Date.h"
#include "BookLending.h"
#include <fstream>
#include "Fine.h"

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
	static void increaseTotalBooksCheckedout(string memberId);
	static void decreaseTotalBooksCheckedout(string memberId);

	bool resetPassword(string newPassWord);
	void registerNew();
	
	friend std::istream& operator>>(std::istream& in, Member& member);
	friend std::ifstream& operator>>(std::ifstream& in, Member& member);
	friend std::ostream& operator<<(std::ostream& out, const Member& member);
	friend std::ofstream& operator<<(std::ofstream& out, const Member& member);

	void checkForFine();
	bool checkoutBookItem(string barcode);
	bool returnBookItem(string barcode);
	bool renewBookItem(string barcode);
};

