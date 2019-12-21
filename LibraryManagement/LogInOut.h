#pragma once
#include "Account.h"
#include "Librarian.h"
#include "Member.h"
#include <fstream>
#include <iostream>

using std::cout;
using std::cin;

void login();
void logout(Account* account);
void registerAccount();