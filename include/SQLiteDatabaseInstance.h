#ifndef SQLITEDATABASEINSTANCE_H
#define SQLITEDATABASEINSTANCE_H

#include <iostream>
#include <iomanip>
#include <stdio.h>
#include <sqlite3.h>
#include <string>

// Creates an instance of an SQLite3 database and allows single statement actions

class SQLiteDatabaseInstance {
public:

	SQLiteDatabaseInstance(std::string dbloc); // Takes in the local directory of the database file
	~SQLiteDatabaseInstance(); // Closes the database instance

	void run(std::string statement, bool withOutput = true); // Will run a single SQLite statement
	bool errorThrown();
	bool emptyResult();

private:

	sqlite3* db;
	char* errorMessage;
	bool errorFlag;
	bool emptyFlag;

	void outputResult(sqlite3_stmt* stmt, int& returnCode);

};

#endif // SQLITEDATABASEINSTANCE_H