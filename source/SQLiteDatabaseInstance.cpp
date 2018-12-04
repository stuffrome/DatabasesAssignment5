#include "SQLiteDatabaseInstance.h" 

SQLiteDatabaseInstance::SQLiteDatabaseInstance(std::string dbloc)
{
	sqlite3_open(dbloc.c_str(), &db);
}

SQLiteDatabaseInstance::~SQLiteDatabaseInstance()
{

}

void SQLiteDatabaseInstance::run(std::string statement)
{
	const char* c_stmt = statement.c_str();

	sqlite3_exec(db, c_stmt, callback, 0, &errorMessage);
}

int SQLiteDatabaseInstance::callback(void * empty, int argc, char **argv, char **colName)
{
	for(int i=0; i < argc; ++i)
	{
		std::cout << colName[i] << "   " << (argv[i] ? argv[i] : "NULL") << "\n";
	}

	std::cout << "\n";

	return 0;
}