#include "MyDefine.h"

Address::Address() {}

Address::Address(std::string city, std::string streetAdd)
{
	_city = city;
	_streetAddress = streetAdd;
}

Address::Address(const Address& other)
{
	_city = other._city;
	_streetAddress = other._streetAddress;
}

std::istream& operator>>(std::istream& in, Address& address)
{
	std::cout << "Thanh pho hien tai: ";
	std::getline(in, address._city, '\n');

	std::cout << "Dia chi cu the: ";
	std::getline(in, address._streetAddress, '\n');

	return in;
}

std::ostream& operator<<(std::ostream& out, const Address address)
{
	out << address._city << '\n';
	out << address._streetAddress;

	return out;
}

Person::Person() {}

Person::Person(std::string name, Address address, std::string email, std::string phone)
	:_name(name), _address(address), _email(email), _phone(phone) {}

Person::Person(const Person& person)
{
	_name = person._name;
	_address = person._address;
	_email = person._email;
	_phone = person._phone;
}

std::istream& operator>>(std::istream& in, Person& person)
{
	std::cout << "Ho va ten: ";
	std::getline(in, person._name, '\n');

	in >> person._address;

	std::cout << "Email: ";
	std::getline(in, person._email, '\n');

	std::cout << "SDT: ";
	std::getline(in, person._phone, '\n');

	return in;
}

std::ostream& operator<<(std::ostream& out, const Person person)
{
	out << person._name << '\n';
	out << person._address << '\n';
	out << person._email << '\n';
	out << person._phone;

	return out;
}

void ShowError(const char* str)
{
	std::cout << str;
}