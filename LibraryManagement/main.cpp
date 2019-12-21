#include "Date.h"
#include "BookItem.h"
#include <iostream>
#include "MyDefine.h"
#include <string>
#include <fstream>
#include "Account.h"
#include "Member.h"
#include "Librarian.h"

using namespace std;

int main()
{
	/*Member mem;
	mem.registerNew();*/

	Librarian lib;
	lib.blockMember("1");
}