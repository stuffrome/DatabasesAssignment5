#ifndef USERINTERFACE_H
#define USERINTERFACE_H

#include <iostream>
#include <string>
#include "SQLiteDatabaseInstance.h"


class UserInterface {
public:

	UserInterface();
	~UserInterface();


private:

	SQLiteDatabaseInstance flowersDB;
	SQLiteDatabaseInstance usersDB;

	void alterFlowersDatabase();
	bool runLogin();					// Returns TRUE if there was a valid login
	void runMenu();
	void clear();

};

#endif // USERINTERFACE_H