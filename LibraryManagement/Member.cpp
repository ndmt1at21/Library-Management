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

bool Member::resetPassword(string newPassword)
{
	std::ifstream infile_member(link_member_information);

	std::string linkTmp = Directory::getDir(link_member_information) + "tmp.txt";
	std::ofstream temp(linkTmp);

	if (infile_member.fail())
		throw std::exception("file not found");

	bool isEmptyFileMember = File::is_empty_file(infile_member);
	if (isEmptyFileMember)
		return false;

	int i = 0; //ghi đầu file ko cần xuống dòng
	while (!infile_member.eof())
	{
		Member mem;
		infile_member >> mem;

		if (mem.getId() == this->_id)
			mem._password = newPassword;
		
		if (i == 0)
		{
			temp << mem;
			i++;
		}
		else
			temp << '\n' << mem;
	}
	infile_member.close();
	temp.close();

	remove(link_member_information);
	if (!rename(linkTmp.c_str(), link_member_information))
		return false;

	return true;
}

uint32_t Member::getTotalCheckedoutBooks()
{
	return _totalBooksCheckedout;
}

Date Member::getDateOfMembership()
{
	return _dateOfMembership;
}

void Member::setDateOfMembership(Date date)
{
	_dateOfMembership = date;
}

void Member::setTotalBooksCheckedout(uint32_t total)
{
	_totalBooksCheckedout = total;
}

void Member::increaseTotalBooksCheckedout(string memberId)
{
	std::ifstream infile_member(link_member_information);
	if (infile_member.fail())
		throw std::exception("file not found");

	string linkTmp = Directory::getDir(link_member_information) + "tmp.txt";
	std::ofstream file_temp(linkTmp);

	int i = 0;
	while (!infile_member.eof())
	{
		Member mem;
		infile_member >> mem;

		if (mem.getId() == memberId)
			mem._totalBooksCheckedout++;

		if (i == 0)
		{
			file_temp << mem;
			i++;
		}
		else
		{
			file_temp << '\n';
			file_temp << mem;
		}
	}
	infile_member.close();
	file_temp.close();

	remove(link_member_information);
	rename(linkTmp.c_str(), link_member_information);
}

void Member::decreaseTotalBooksCheckedout(string memberId)
{
	std::ifstream infile_member(link_member_information);
	if (infile_member.fail())
		throw std::exception("file not found");

	string linkTmp = Directory::getDir(link_member_information) + "tmp.txt";
	std::ofstream file_temp(linkTmp);

	int i = 0;
	while (!infile_member.eof())
	{
		Member mem;
		infile_member >> mem;

		if (mem.getId() == memberId)
			mem._totalBooksCheckedout++;

		if (i == 0)
		{
			file_temp << mem;
			i++;
		}
		else
		{
			file_temp << '\n';
			file_temp << mem;
		}
	}

	remove(link_member_information);
	rename(linkTmp.c_str(), link_member_information);
}

void Member::registerNew()
{
	std::ifstream infile_member(link_member_information);
	if (infile_member.fail())
		throw std::exception("file not found");

	bool isEmptyFile = File::is_empty_file(infile_member);
	while (true)
	{
		while (true)
		{
			std::cout << "Ten dang nhap: ";
			std::getline(std::cin, _id, '\n');
			if (_id.empty())
				ShowError("Ten dang nhap khong duoc trong\n");
			else break;
		};


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
				infile_member.seekg(0);
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

		if (_password.size() < 5)
			ShowError("Mat khau it nhat 5 ky tu");
		else break;
	}

	std::cin >> _person;

	_status = AccountStatus::ACTIVE;
	_dateOfMembership.getDateNow();
	_dateOfMembership = _dateOfMembership + 10;
	_totalBooksCheckedout = 0;

	infile_member.close();

	std::ofstream outfile(link_member_information, std::ios::app);
	if (isEmptyFile)
		outfile << *this;
	else
	{
		outfile << '\n';
		outfile << *this;
	}
}

std::istream& operator>>(std::istream& in, Member& member)
{
	operator>>(in, static_cast<Account&>(member));
	in >> member._dateOfMembership;

	in >> member._totalBooksCheckedout;
	in.get();

	return in;
}

std::ifstream& operator>>(std::ifstream& in, Member& member)
{
	operator>>(in, static_cast<Account&>(member));
	in >> member._dateOfMembership;
	in >> member._totalBooksCheckedout;
	in.get();

	return in;
}

std::ostream& operator<<(std::ostream& out, const Member& member)
{
	operator<<(out, static_cast<const Account&>(member));
	out << std::setw(10) << member._dateOfMembership;
	out << std::right << std::setw(20) << member._totalBooksCheckedout << '\n';

	return out;
}

std::ofstream& operator<<(std::ofstream& out, const Member& member)
{
	operator<<(out, static_cast<const Account&>(member)) << '\n';
	out << member._dateOfMembership << '\n';
	out << member._totalBooksCheckedout;

	return out;
}

bool Member::checkoutBookItem(string barcode)
{
	Date dateNow;
	dateNow.getDateNow();

	if (_totalBooksCheckedout > MAX_BOOK_ISSUE_FOR_A_USER)
	{
		ShowError("Ban da muon sach vuot gioi han\n");
		return false;
	}

	if (_dateOfMembership > dateNow)
	{
		ShowError("Tai khoan het han su dung");
		return false;
	}

	BookLending bookLending;
	if (!bookLending.lendBook(barcode, this->_id))
		return false;
	_totalBooksCheckedout++;

	return true;
}

void Member::checkForFine()
{
	std::vector<BookLending> books = BookLending::fetchLendingDetails(this->_id);
	
	Date dateNow;
	dateNow.getDateNow();
	
	double fines = 0;
	for (size_t i = 0; i < books.size(); i++)
	{
		if (books[i].getCreateDate() > dateNow)
		{
			uint32_t days = dateNow - books[i].getCreateDate();
			fines += Fine::collectFine(books[i].getBookItemBarCode(), days);
		}
	}

	std::cout << "So tien phat: " << fines;
}


bool Member::returnBookItem(string barcode)
{
	checkForFine();

	BookLending bookLending;
	if (!bookLending.deleteLendingBook(barcode, this->_id))
		return false;

	return true;
}

bool Member::renewBookItem(string barcode)
{
	checkForFine();

	Date dateNow;
	dateNow.getDateNow();

	if (_dateOfMembership > dateNow)
	{
		ShowError("Tai khoan het han su dung");
		return false;
	}

	BookLending bookLending;
	if (!bookLending.updateDueDate(barcode, this->_id))
		return false;
	return true;
}