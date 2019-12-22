#pragma once
#include "Account.h"
#include <string>
#include <iostream>
#include <fstream>
#include "Member.h"
#include "Librarian.h"

using namespace std;

class Menu
{
private:
	Account* _acc;

public:
	~Menu();

	void mainMenu();
	void libMenu();
	void memMenu();
	void login();
	void about();
	void registerMember();
};

