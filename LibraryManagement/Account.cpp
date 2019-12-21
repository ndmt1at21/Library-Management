#include "Account.h"
#include <fstream>

Account::Account()
{
	_status = AccountStatus::BLOCK;
}

Account::Account(string id, AccountStatus status, string pass, Person person)
{
	_id = id;
	_password = pass;
	_status = status;
	_person = person;
}

Account::Account(const Account& other)
{
	_id = other._id;
	_password = other._password;
	_status = other._status;
	_person = other._person;
}

Account::~Account() {}

string Account::getId()
{
	return _id;
}

AccountStatus Account::getAccountStatus()
{
	return _status;
}

void Account::setAccountStatus(AccountStatus status)
{
	_status = status;
}

std::istream& operator>>(std::istream& in, Account& account)
{
	std::getline(in, account._id, '\n');

	int status;
	in >> status;
	account._status = AccountStatus(status);
	in.get();

	std::getline(in, account._password, '\n');
	in >> account._person;

	return in;
}

std::ostream& operator<<(std::ostream& out, const Account& account)
{
	out << account._id << '\n';
	out << int(account._status) << '\n';
	out << account._password << '\n';
	out << account._person;

	return out;
}

void Account::listBook()
{
	std::ifstream infile_book(link_book_information);
	BookItem book;

	while(!infile_book.eof())
	{
		infile_book >> book;
		book.viewBookInformation(std::cout);
	}	
}