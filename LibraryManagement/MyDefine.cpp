#include "MyDefine.h"
#include "StringProcess.h"
#include <iomanip>

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
	while (true)
	{
		std::cout << "Thanh pho hien tai: ";
		std::getline(in, address._city, '\n');

		if (address._city.size() != 0)
			break;
		else 
			ShowError("Vui long nhap thanh pho");
	}
	

	while (true)
	{
		std::cout << "Dia chi cu the: ";
		std::getline(in, address._streetAddress, '\n');

		if (address._streetAddress.size() != 0)
			break;
		else
			ShowError("Vui long nhap thanh pho");
	}

	return in;
}

std::ifstream& operator>>(std::ifstream& in, Address& address)
{
	std::getline(in, address._city, '\n');
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

std::string Person::getName()
{
	return _name;
}

Address Person::getAddress()
{
	return _address;
}

std::string Person::getEmail()
{
	return _email;
}

std::string Person::getPhone()
{
	return _phone;
}

std::istream& operator>>(std::istream& in, Person& person)
{
	std::cout << "Ho va ten: ";
	
	while (true)
	{
		std::getline(in, person._name, '\n');

		if (person._name.size() != 0)
			break;
		else
			ShowError("Ten khong the bo trong\n");
	}
	
	in >> person._address;

	while (true)
	{
		std::cout << "Email: ";
		std::getline(in, person._email, '\n');

		if (person._email.size() <= 3 || person._email.find('@') == std::string::npos)
			ShowError("Email ban nhap khong hop le\n");
		else
			break;
	}


	while (true)
	{
		std::cout << "SDT: ";
		std::getline(in, person._phone, '\n');

		if (!isAllDigit(person._phone) || person._phone.size() > 12 || person._phone.size() < 9)
			ShowError("So ban nhap khong dung\n");
		else break;
	}
	

	return in;
}

std::ifstream& operator>>(std::ifstream& in, Person& person)
{
	std::getline(in, person._name, '\n');
	in >> person._address;
	std::getline(in, person._email, '\n');
	std::getline(in, person._phone, '\n');

	return in;
}

std::ostream& operator<<(std::ostream& out, const Person person)
{
	out << std::left << std::setw(30) << person._name;
	out << std::setw(20) << person._email;
	out << std::setw(20) << person._phone;

	return out;
}

std::ofstream& operator<<(std::ofstream& out, const Person person)
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