/*
Author: Nguyễn Đức Minh Trí
Function: Chứa các enum, các struct, define cần thiết
Date: 19/12/2019
*/

#pragma once
#include <iostream>
#include <string>
#include <fstream>

#define MAX_BOOK_ISSUE_FOR_A_USER 5
#define MAX_LENDING_DAY 10

enum class BookFormat
{
	CULTURAL,
	SELF_HELF,
	FOREIGN_LANGUAGE_LEARNING,
	LITERATURE,
};

enum class BookStatus
{
	AVAILABLE,
	LOANED //đã cho mượn
};

enum class AccountStatus
{
	ACTIVE,
	BLOCK,
};

class Address
{
private:
	std::string _city;
	std::string _streetAddress;

public:
	Address();
	Address(std::string city, std::string streetAdd);
	Address(const Address& other);
	friend std::istream& operator>>(std::istream& in, Address& address);
	friend std::ifstream& operator>>(std::ifstream& in, Address& address);
	friend std::ostream& operator<<(std::ostream& out, const Address address);
};

class Person
{
private:
	std::string _name;
	Address _address;
	std::string _email;
	std::string _phone;

public:
	Person();
	Person(std::string name, Address address, std::string email, std::string phone);
	Person(const Person& person);

	std::string getName();
	Address getAddress();
	std::string getEmail();
	std::string getPhone();

	friend std::istream& operator>>(std::istream& in, Person& person);
	friend std::ifstream& operator>>(std::ifstream& in, Person& person);
	friend std::ostream& operator<<(std::ostream& out, const Person person);
	friend std::ofstream& operator<<(std::ofstream& out, const Person person);
};

void ShowError(const char* str);