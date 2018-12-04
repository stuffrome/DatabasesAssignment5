#ifndef SQLITEDATABASEINSTANCE_H
#define SQLITEDATABASEINSTANCE_H

#include <iostream>
#include <stdio.h>
#include <sqlite3.h>
#include <string>

// Creates an instance of an SQLite3 database and allows single statement actions

class SQLiteDatabaseInstance {
public:

	SQLiteDatabaseInstance(std::string dbloc); // Takes in the local directory of the database file
	~SQLiteDatabaseInstance(); // Closes the database instance

	void run(std::string statement); // Will run a single SQLite statement

private:

	sqlite3* db;
	char* errorMessage;

	static int callback(void * empty, int argc, char **argv, char **colName);

};

#endif // SQLITEDATABASEINSTANCE_H