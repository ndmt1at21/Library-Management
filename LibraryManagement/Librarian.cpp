﻿#include "Librarian.h"
#include "Directory.h"
#include "File.h"

void Librarian::addBookItem(BookItem bookItem)
{
	std::ofstream file_book(link_book_information, std::ios::app);
	if (file_book.fail())
		throw std::exception("data not found");

	if (File::is_empty_file(file_book))
		file_book << bookItem;
	else
	{
		file_book << '\n';
		file_book << bookItem;
	}
}

bool Librarian::modifyBook(string barcode)
{
	std::ifstream infile_book(link_book_information);
	if (infile_book.fail())
		throw std::exception("data not found");

	std::string linkTemp = Directory::getDir(link_book_information) + "tmp.txt";
	std::ofstream temp(linkTemp);

	BookItem search;
	bool isFound = false;
	while (!infile_book.eof())
	{
		infile_book >> search;
		if (search.getBarCode() == barcode)
		{
			std::cout << "Nhap thong tin sua doi sach\n";
			std::cin >> search;

			if (File::is_empty_file(infile_book))
				temp << search;
			else
				temp << search << '\n';

			isFound = true;
		}
		else temp << search;
	}
	infile_book.close();
	temp.close();

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

	int i = 0;
	while (!infile_member.eof())
	{
		infile_member >> mem;
		
		if (mem.getId() == id)
		{
			mem.setAccountStatus(AccountStatus::BLOCK);
			isFound = true;
		}
		
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

bool Librarian::unblockMember(string id)
{
	std::ifstream infile_member(link_member_information);
	if (infile_member.fail())
		return false;

	if (File::is_empty_file(infile_member))
		return false;

	std::string linkTemp = Directory::getDir(link_member_information) + "tmp.txt";
	std::ofstream temp(linkTemp);
	
	Member mem;
	bool isAvailable = false;
	int i = 0;
	while (!infile_member.fail())
	{
		infile_member >> mem;

		if (mem.getId() == id)
		{
			isAvailable = true;
			mem.setAccountStatus(AccountStatus::ACTIVE);
		}

		if (i == 0)
		{
			temp << mem;
			i++;
		}
		else temp << '\n' << mem;
	}
	infile_member.close();
	temp.close();

	if (!isAvailable)
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

void Librarian::listMember()
{
	std::ifstream infile_member(link_member_information);

	if (File::is_empty_file(infile_member))
	{
		std::cout << "Chua co thanh vien\n";
		return;
	}

	Member mem;
	while (!infile_member.eof())
	{
		infile_member >> mem;
		std::cout << mem;
	}
}

void Librarian::xuatPhieuMuon(string barcode, string memberId)
{
	BookLending bookLending;
	std::vector<BookLending> books = bookLending.fetchLendingDetails(memberId); //Nhiều cuốn

	std::ifstream infile_member(link_member_information);
	Member mem;
	while (!infile_member.eof())
	{
		infile_member >> mem;

		if (mem.getId() == memberId)
			break;
	}

	for (size_t i = 0; i < books.size(); i++)
	{
		if (books[i].getBookItemBarCode() == barcode)
		{
			string link = barcode + "_" + memberId + ".txt";
			std::ofstream outfile_phieuMuon(link);

			outfile_phieuMuon << "\t\t\tPHIEU MUON SACH\n\n";
			outfile_phieuMuon << std::left << "Ho va ten: " << std::setw(30) << mem.getPersonInfo().getName() << '\n';
			outfile_phieuMuon << "ID: " << std::setw(30) << mem.getId() << '\n';
			outfile_phieuMuon << "Barcode sach: " << std::setw(30) << books[i].getBookItemBarCode() << '\n';
			outfile_phieuMuon << "Ngay muon: " << std::setw(30) << books[i].getCreateDate() << '\n';
			outfile_phieuMuon << "Ngay tra: " << std::setw(30) << books[i].getDueDate() << '\n';
			outfile_phieuMuon << "\t\t\t\t\t Ky va ghi ro ho ten";
		}
	}
}
