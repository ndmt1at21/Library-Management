#include "Member.h"
#include "File.h"
#include "Directory.h"

Member::Member() 
{
	_totalBooksCheckedout = 0;
}

Member::Member(string id, AccountStatus status, string password, Person person, 
	Date dateMembership, uint32_t totalBookChekedout)
	:Account(id, status, password, person)
{
	_dateOfMembership = dateMembership;
	_totalBooksCheckedout = totalBookChekedout;
}

void Member::updatePassword(string newPassword)
{
	_password = newPassword;
}

bool Member::resetPassword(string id, string newPassword)
{
	std::ifstream infile_member(link_member_information);
	std::ofstream temp(Directory::getDir(link_member_information) + "tmp.txt");

	if (infile_member.fail())
		throw std::exception("file not found");

	if (File::is_empty_file(infile_member))
		return false;

	int i = 0;
	while (!infile_member.eof())
	{
		Member mem;
		infile_member >> mem;

		if (mem.getId() == id)
			mem.updatePassword(newPassword);
		
		if (i == 0)
			temp << mem;
		else temp << '\n' << mem;
	}

	return true;
}

void Member::registerNew()
{
	std::ifstream infile_member(link_member_information);
	if (infile_member.fail())
		throw std::exception("file not found");

	bool isEmptyFile = File::is_empty_file(infile_member);
	while (true)
	{
		std::cout << "Ten dang nhap: ";
		std::getline(std::cin, _id, '\n');

		if (isEmptyFile)
			break;

		Member search;
		bool isAvailable = false;
		while (!infile_member.eof())
		{
			infile_member >> search;

			if (search.getId() == _id)
			{
				isAvailable = true;
				std::cout << "Ten dang nhap da ton tai.\n";
				break;
			}
		}
		if (!isAvailable)	
			break;
	}

	while (true)
	{
		std::cout << "Mat khau: ";
		std::getline(std::cin, _password, '\n');

		if (!_password.empty())
			break;
	}

	std::cin >> _person;

	_status = AccountStatus::ACTIVE;
	_dateOfMembership.getDateNow();
	_dateOfMembership = _dateOfMembership + 10;
	_totalBooksCheckedout = 0;
	
	//kiểm tra file trống ko, nếu trống thì ko cần \n trước
	infile_member.close();
	std::ofstream outfile(link_member_information, std::ios::app);

	if (isEmptyFile)
		outfile << *this;
	else outfile << '\n' << *this;
}

uint32_t Member::getTotalCheckedoutBooks()
{
	return _totalBooksCheckedout;
}

std::istream& operator>>(std::istream& in, Member& member)
{
	operator>>(in, static_cast<Account&>(member));
	in >> member._dateOfMembership;

	in >> member._totalBooksCheckedout;
	in.get();

	return in;
}

std::ostream& operator<<(std::ostream& out, const Member& member)
{
	operator<<(out, static_cast<const Account&>(member)) << '\n';
	out << member._dateOfMembership << '\n';
	out << member._totalBooksCheckedout;

	return out;
}

bool Member::checkoutBookItem(BookItem book)
{
	return true;
}