#include "SQLITE_DATABASE_INSTANCE.h" 

SQLITE_DATABASE_INSTANCE::SQLITE_DATABASE_INSTANCE(string dbloc) : db(sqlite3())
{
	sqlite3_open(dbloc.c_str(), db);
}

SQLITE_DATABASE_INSTANCE::~SQLITE_DATABASE_INSTANCE()
{

}

void SQLITE_DATABASE_INSTANCE::run(string statement)
{
	c_stmt = statement.c_str();

	sqlite3_exec(db, c_stmt, callback, 0, errorMessage);
}

int SQLITE_DATABASE_INSTANCE::callback(void * empty, int argc, char **argv, char **colName)
{
	for(int i=0; i < argc; ++i)
	{
		cout << colName[i] << "   " << (argv[i] ? argv[i] : "NULL") << "\n";
	}

	cout << "\n";
	
	return 0;
}