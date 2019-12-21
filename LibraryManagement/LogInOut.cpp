#include "LogInOut.h"

void login()
{
	std::ifstream inforFile("account_data.txt");
	
	int times = 0;
	while (true)
	{
		cout << "Ten dang nhap: ";
		string id;
		std::getline(cin, id, '\n');
		
		string getId;
		if (std::getline(inforFile, getId, '\n'))
		{
			if (id.compare(getId) == 0);

		}
		

	}
	
}

void logout(Account* account)
{

}

void registerAccount()
{

}