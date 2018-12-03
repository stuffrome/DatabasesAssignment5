#include <iostream>
#include <stdio.h>
#include <sqlite3.h>
#include <string>

using namespace std;

static int callback(void *NotUsed, int argc, char **argv, char **azColName)
{
	int i;
	for(i=0; i<argc; i++)
	{
		cout<<azColName[i]<<"   " << (argv[i] ? argv[i] : "NULL")<<"\n";
	}
	cout<<"\n";
	return 0;
}

int main()
{
	const int STATEMENTS = 1;
	sqlite3 * db;
	char * errMsg = 0;
	const char *SQL[STATEMENTS];

	sqlite3_open("flowers.db", &db);


    SQL[0] = "SELECT * FROM FLOWERS";

    sqlite3_exec(db, SQL[0], callback, 0, &errMsg);
 
    sqlite3_close(db);

	return 0;
}