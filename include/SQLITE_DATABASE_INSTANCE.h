#ifdef SQLITE_DATABASE_INSTANCE
#define SQLITE_DATABASE_INSTANCE

#include <iostream>
#include <stdio.h>
#include <sqlite3.h>
#include <string>


// Creates an instance of an SQLite3 database and allows single statement actions

class SQLITE_DATABASE_INSTANCE {
public:

	SQLITE_DATABASE_INSTANCE(string dbloc); // Takes in the local directory of the database file
	~SQLITE_DATABASE_INSTANCE();

	void run(string statement); // Will run a single SQLite statement
	void close(); // Closes the database instance

private:

	sqlite3* db;
	char* errorMessage;

	int callback(void * empty, int argc, char **argv, char **colName)

};