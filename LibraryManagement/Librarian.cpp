#include "Librarian.h"
#include "Directory.h"
#include "File.h"

void Librarian::addBookItem(BookItem bookItem)
{
	std::fstream file_book(link_book_information, std::fstream::in | std::fstream::out | std::fstream::app);
	if (file_book.fail())
		throw std::exception("data not found");

	size_t numBooks = 0;
	file_book >> numBooks;
	file_book.get();

	numBooks++;
	file_book << bookItem;
	file_book.seekp(0, std::fstream::beg);
	file_book << numBooks;
}

bool Librarian::modifyBook(BookItem bookItemMod)
{
	std::ifstream infile_book(link_book_information);
	if (infile_book.fail())
		throw std::exception("data not found");

	size_t numBooks = 0;
	infile_book >> numBooks;

	std::string linkTemp = Directory::getDir(link_book_information) + "tmp.txt";
	std::ofstream outfile_book(linkTemp);

	BookItem search;
	bool isFound = false;
	for (size_t i = 0; i < numBooks; i++)
	{
		infile_book >> search;
		if (search.getBarCode() == bookItemMod.getBarCode())
		{
			outfile_book << bookItemMod;
			isFound = true;
		}
		else
			outfile_book << search;
	}

	if (!isFound)
	{
		remove(linkTemp.c_str());
		return false;
	}

	remove(link_book_information);
	if (!rename(linkTemp.c_str(), link_book_information))
		return false;

	return true;
}

bool Librarian::removeBook(string barCode)
{
	std::ifstream infile_book(link_book_information);
	if (infile_book.fail())
		throw std::exception("data not found");

	size_t numBooks = 0;
	infile_book >> numBooks;

	std::string  linkTemp = Directory::getDir(link_book_information) + "tmp.txt";
	std::ofstream outfile_book(linkTemp);

	BookItem search;
	bool isFound = false;
	for (size_t i = 0; i < numBooks; i++)
	{
		infile_book >> search;
		if (search.getBarCode() != barCode)
			outfile_book << search;
		else
			isFound = true;
	}

	if (!isFound)
	{
		remove(linkTemp.c_str());
		return false;
	}

	remove(link_book_information);
	if (!rename(linkTemp.c_str(), link_book_information))
		return false;

	return true;
}

bool Librarian::blockMember(string id)
{
	std::ifstream infile_member(link_member_information);

	if (infile_member.fail())
		throw std::exception("file not found");

	if (File::is_empty_file(infile_member))
		return false;

	std::string linkTemp = Directory::getDir(link_member_information) + "tmp.txt";
	std::ofstream temp(linkTemp);
	
	Member mem;
	bool isFound = false;
	while (!infile_member.eof())
	{
		infile_member >> mem;
		
		if (mem.getId() == id)
		{
			mem.setAccountStatus(AccountStatus::BLOCK);
			isFound = true;
		}
		
		temp << mem;
	}
	infile_member.close();
	temp.close();

	if (!isFound)
	{
		remove(linkTemp.c_str());
		return false;
	}

	remove(link_member_information);
	if (!rename(linkTemp.c_str(), link_member_information))
		return false;

	return true;
}

bool Librarian::unblockMember(Member member)
{
	std::ifstream infile_member(link_member_information);
	size_t numMembers = 0;
	infile_member >> numMembers;

	std::string linkTemp = Directory::getDir(link_member_information) + "tmp.txt";
	std::ofstream temp(linkTemp);
	
	Member search;
	bool isFound = false;
	for (size_t i = 0; i < numMembers; i++)
	{
		infile_member >> search;

		if (search.getId() == member.getId())
		{
			isFound = true;
			member.setAccountStatus(AccountStatus::ACTIVE);
		}

		temp << search;
	}

	if (!isFound)
	{
		remove(linkTemp.c_str());
		return false;
	}

	remove(link_member_information);
	if (!rename(linkTemp.c_str(), link_member_information))
		return false;
	return true;
}

size_t Librarian::getNumberOfMember()
{
	std::ifstream infile_member(link_member_information);
	size_t numMembers = 0;
	infile_member >> numMembers;

	return numMembers;
}

bool Librarian::searchMember(string id)
{
	std::ifstream infile_member(link_member_information);
	size_t numMembers = 0;
	infile_member >> numMembers;
	return true;
}

void Librarian::showAllMember()
{
	std::ifstream infile_member(link_member_information);

	while (true)
	{
		infile_member >> *this;
		std::cout << _id << "\t" << _password << "\t";

		switch (_status)
		{
		case AccountStatus::ACTIVE:
			std::cout << "Active\n";
			break;
		
		case AccountStatus::BLOCK:
			std::cout << "Block\n";
			break;
		}
	}
}