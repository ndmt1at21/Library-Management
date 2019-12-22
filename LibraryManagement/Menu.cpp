#include "Menu.h"
#include <conio.h>
#include <Windows.h>

Menu::~Menu()
{
	delete _acc;
}
void Menu::mainMenu()
{
	while (true)
	{
		cout << "1. Dang nhap\n";
		cout << "2. Thong tin\n";
		cout << "3. Dang ky tai khoan\n";
		cout << "4. Thoat\n";
		cout << "Nhap lua chon: ";

		int choice;
		cin >> choice;
		cin.get();

		switch (choice)
		{
		case 1:
			login();
			break;
			
		case 2:
			about();
			break;

		case 3:
			registerMember();
			break;

		default:
			return;
		}
	}
	
}

void Menu::login()
{
	Member* mem = new Member;
	bool isAvailable = false;

	while (!isAvailable)
	{
		system("cls");
		cout << "Ten dang nhap: ";

		string id;
		getline(cin, id, '\n');

		if (id == "admin")
			break;

		ifstream infile_member(link_member_information);
		if (infile_member.fail())
			throw exception("file not found");

		while (!infile_member.eof())
		{
			infile_member >> *mem;

			if (mem->getId() == id)
			{
				isAvailable = true;
				break;
			}
			else
			{
				cout << "Sai ten dang nhap\n";
				Sleep(1000);
			}
		}
	}

	while (true)
	{
		cout << "Mat khau: ";
		string pass;
		getline(cin, pass, '\n');

		if (pass == "admin")
		{
			_acc = new Librarian;
			break;
		}

		if (pass == mem->getPassword())
		{
			_acc = mem;
			break;
		}
		else
			cout << "Sai mat khau\n";
	}

	if (dynamic_cast<Librarian*>(_acc) != NULL)
		libMenu();
	else if (dynamic_cast<Member*>(_acc) != NULL)
		memMenu();
}

void Menu::libMenu()
{
	while (true)
	{
		system("cls");
		cout << "1. Them sach\n";
		cout << "2. Chinh sua sach\n";
		cout << "3. Xoa sach\n";
		cout << "4. Khoa thanh vien\n";
		cout << "5. Mo khoa thanh vien\n";
		cout << "6. Danh sach thanh vien\n";
		cout << "7. Danh sach cac sach trong thu vien\n";
		cout << "8. Doc gia muon sach qua han\n";
		cout << "9. In phieu muon sach\n";
		cout << "9. Thoat\n";
		cout << "Nhap lua chon: ";
		int choice;
		cin >> choice;
		cin.get();

		Librarian* lib = dynamic_cast<Librarian*>(_acc);
		system("cls");

		switch (choice)
		{
		case 1:
		{
			cout << "Nhap thong tin sach\n";
			BookItem book;
			cin >> book;
			
			lib->addBookItem(book);
			break;
		}

		case 2:
		{
			cout << "Nhap barcode: ";
			string barcode;
			getline(cin, barcode, '\n');
			
			if (lib->modifyBook(barcode))
				cout << "Sua doi thanh cong\n";
			else
				cout << "Sua doi khong thanh cong\n";
			break;
		}

		case 3:
		{
			cout << "Nhap barcode: ";
			string barcode;
			getline(cin, barcode, '\n');
			if (!lib->removeBook(barcode))
				cout << "Khong the xoa sach\n";
			else
				cout << "Xoa sach thanh cong\n";
			break;
		}

		case 4:
		{
			cout << "Nhap ten tai khoan: ";
			string id;
			getline(cin, id, '\n');
			if (!lib->blockMember(id))
				cout << "Khoa khong thanh cong\n";
			else
				cout << "Khoa thanh cong\n";
			break;
		}

		case 5:
		{
			cout << "Nhap ten tai khoan: ";
			string id;
			getline(cin, id, '\n');
			if (!lib->unblockMember(id))
				cout << "Mo khoa khong thanh cong\n";
			else
				cout << "Mo khoa thanh cong\n";
			break;
		}

		case 6:
		{
			cout << "DANH SACH THANH VIEN\n";
			cout << left << std::setw(20) << "TEN TAI KHOAN" << setw(10) << "STATUS" << setw(30) << "HO TEN";
			cout << setw(20) << "EMAIL" << setw(20) << "SO DIEN THOAI" << setw(20);
			cout << "THOI HAN TK" << setw(10) << "SO SACH MUON\n";
			lib->listMember();
			break;
		}

		case 7:
		{
			std::cout << "TEN SACH" << std::setw(40) << "BARCODE" << std::setw(20) << "THE LOAI";
			std::cout << std::setw(23) << "STATUS" << std::setw(10) << "VI TRI" << std::setw(11) << "TAC GIA" << std::endl;
			lib->listBook();
			break;
		}

		case 8:
		{

		}

		case 9: 
		{
			cout << "Nhap ID: ";
			string id;
			getline(cin, id, '\n');

			cout << "Nhap barcode sach: ";
			string barcode;
			getline(cin, barcode, '\n');

			lib->xuatPhieuMuon(barcode, id);
			break;
		}
		default:
			return;
		}

		cout << "(Bam phim bat ky de tro ve)\n";
		_getch();
	}
}

void Menu::memMenu()
{
	while (true)
	{
		system("cls");
		cout << "1. Muon sach\n";
		cout << "2. Tra sach\n";
		cout << "3. Gia han\n";
		cout << "4. Tim sach\n";
		cout << "5. Danh sach cac sach trong thu vien\n";
		cout << "6. Reset password\n";
		cout << "7. Thoat\n";
		cout << "Nhap lua chon: ";
		int choice;
		cin >> choice;
		cin.get();

		Member* mem = dynamic_cast<Member*>(_acc);
		system("cls");

		switch (choice)
		{
		case 1:
		{
			cout << "Nhap barcode: ";
			string barcode;
			getline(cin, barcode, '\n');
			if (mem->checkoutBookItem(barcode))
			{
				cout << "Muon sach thanh cong\n";
				cout << "Ra quay de in phieu muon\n";
			}
			else
				cout << "Khong the muon sach";
			break;
		}

		case 2:
		{
			cout << "Nhap barcode: ";
			string barcode;
			getline(cin, barcode, '\n');

			if (mem->returnBookItem(barcode))
				cout <<"Tra sach thanh cong\n";
			break;
		}

		case 3:
		{
			cout << "Nhap barcode: ";
			string barcode;
			getline(cin, barcode, '\n');
			
			if (mem->renewBookItem(barcode))
				cout << "Gia han thanh cong\n";
			else
				cout << "khong the gia han\n";
			break;
		}

		case 4:
		{
			//tim sach
		}

		case 5:
		{
			std::cout << "TEN SACH" << std::setw(40) << "BARCODE" << std::setw(20) << "THE LOAI";
			std::cout << std::setw(23) << "STATUS" << std::setw(10) << "VI TRI" << std::setw(11) << "TAC GIA" << std::endl;
			mem->listBook();
			break;
		}

		case 6:
		{
			while (true)
			{
				cout << "Nhap password moi: ";
				string newPass;
				getline(cin, newPass, '\n');

				if (newPass.size() <= 5)
					continue;
				else
				{
					mem->resetPassword(newPass);
					break;
				}
			}
			
		}

		default:
			return;
		}

		cout << "(Bam phim bat ky de tro ve)\n";
		_getch();
	}
}
void Menu::about()
{
	system("cls");
	cout << "Do an Lap trinh Huong doi tuong - 18CTT5\n";
	cout << "GV: Pham Tuan Minh\n";
	cout << "Tac gia: Nguyen Duc Minh Tri - 18120612\n";
	cout << "Ngay hoan thanh: 22/12/2019\n\n";

	cout << "(Nhap phim bat ky de thoat)";
	
	if (_getch())
		return;
}

void Menu::registerMember()
{
	Member* mem = new Member;
	mem->registerNew();
	memMenu();
}