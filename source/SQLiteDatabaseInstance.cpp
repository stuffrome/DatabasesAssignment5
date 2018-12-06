#include "SQLiteDatabaseInstance.h" 

SQLiteDatabaseInstance::SQLiteDatabaseInstance(std::string dbloc)
{
	sqlite3_open(dbloc.c_str(), &db);
	errorMessage = nullptr;
}

SQLiteDatabaseInstance::~SQLiteDatabaseInstance()
{
	sqlite3_close(db);
}

void SQLiteDatabaseInstance::run(std::string statement, bool withOutput)
{
	sqlite3_stmt* stmt;
	const char* c_stmt = statement.c_str();

	int returnCode = sqlite3_prepare_v2(db, c_stmt, -1, &stmt, NULL);

	if (returnCode != SQLITE_OK) {
	    std::cout << "Error: " << sqlite3_errmsg(db) << '\n';
	    return;
	}

	if (withOutput)
	{
		outputResult(stmt,returnCode);
	}
	else
	{
		while ((returnCode = sqlite3_step(stmt)) == SQLITE_ROW) {}
	}

	if (returnCode != SQLITE_DONE) {
	    std::cout << "Error: " << sqlite3_errmsg(db);
	}

	sqlite3_finalize(stmt);
}

void SQLiteDatabaseInstance::outputResult(sqlite3_stmt* stmt, int& returnCode)
{
	int colOutputWidth = 20;
	std::string colOutputSpacer = "\t";

	std::cout << "===== OUTPUT START =====" << std::endl;

	int colCount = sqlite3_column_count(stmt);

	for (int i = 0; i < colCount; ++i)
	{
		std::cout << std::setw(colOutputWidth) << std::left << sqlite3_column_name(stmt, i) << colOutputSpacer;
	}

	std::cout << '\n';

	for (int i = 0; i < colCount; ++i)
	{
		for (int j = 0; j < colOutputWidth; ++j)
		{
			std::cout << "-";
		}
		std::cout << colOutputSpacer;
	}

	std::cout << '\n';

	while ((returnCode = sqlite3_step(stmt)) == SQLITE_ROW) {
		for (int i = 0; i < colCount; ++i)
		{
			std::cout << std::setw(20) << std::left << sqlite3_column_text(stmt, i) << colOutputSpacer;
		}
		std::cout << '\n';
	}

	std::cout << "===== OUTPUT END =====" << std::endl;
}