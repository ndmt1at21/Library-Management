#pragma once
#include <string>
#include <iostream>
#include "MyDefine.h"
#include "BookItem.h"
#include "Library.h"
#include "Search.h"

#define link_member_information "member_information.txt"

using std::string;

class Account
{
protected:
	string _id;
	AccountStatus _status;
	string _password;
	Person _person;

public:
	Account();
	Account(string, AccountStatus, string, Person);
	Account(const Account& other);
	virtual ~Account();

	string getId();
	AccountStatus getAccountStatus();
	string getPassword(); //????
	Person getPersonInfo();

	void setId(string id);
	void setAccountStatus(AccountStatus status);

	friend std::istream& operator>>(std::istream& in, Account& account);
	friend std::ifstream& operator>>(std::ifstream& in, Account& account);
	friend std::ostream& operator<<(std::ostream& out, const Account& account);
	friend std::ofstream& operator<<(std::ofstream& out, const Account& account);

	void listBook();
};

