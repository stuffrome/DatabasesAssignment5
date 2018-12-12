#include "UserInterface.h"

UserInterface::UserInterface() : usersDB(SQLiteDatabaseInstance("databases/users.db")), flowersDB(SQLiteDatabaseInstance("databases/flowers.db"))
{
	if (runLogin())
	{
		alterFlowersDatabase();

		runMenu();
	}
}

UserInterface::~UserInterface()
{

}

void UserInterface::alterFlowersDatabase()
{
	/* 
	 * Added ON UPDATE CASCADE ON DELETE SET NULL to the foreign key
	 * constraints on SIGHTINGS to have it be automatically updated 
	 * when the changes a flower's information.
	 *
	 */
	flowersDB.run("PRAGMA foreign_keys=off;"
			"ALTER TABLE SIGHTINGS RENAME TO _SIGHTINGS_OLD;"
			"CREATE TABLE SIGHTINGS ("
			"	NAME	VARCHAR ( 30 ),"
			"	PERSON	VARCHAR ( 30 ),"
			"	LOCATION	VARCHAR ( 30 ),"
			"	SIGHTED	DATE,"
			"	CONSTRAINT sightings_pk PRIMARY KEY(`NAME`,`PERSON`,`LOCATION`,`SIGHTED`),"
			"	CONSTRAINT fk1_sightings FOREIGN KEY(`NAME`) REFERENCES `FLOWERS`(`COMNAME`) ON UPDATE CASCADE ON DELETE SET NULL,"
			"	CONSTRAINT fk2_sightings FOREIGN KEY(`LOCATION`) REFERENCES `FEATURES`(`LOCATION`) ON UPDATE CASCADE ON DELETE SET NULL);"
			"INSERT INTO SIGHTINGS SELECT * FROM _SIGHTINGS_OLD;"
			"DROP TABLE _SIGHTINGS_OLD;"
			"PRAGMA foreign_keys=on;", false);
}

bool UserInterface::runLogin()
{
	int userInt;
    std::string username;
    std::string password;

    do {
	    std::cout << "\nFUNCTIONS:\n1. Login\n2. Sign Up\n3. Quit" << std::endl;
	    std::cout << "Choose an option: ";

	    std::cin >> userInt;

	    // Login

	    if (userInt == 1)
	    {
	        std::cout << "Username: ";

	        std::cin >> username;

	        std::cout << "Password: ";

	        std::cin >> password;

	        usersDB.run("SELECT * FROM ACCOUNTS WHERE USERNAME = '" + username + "' AND PASSWORD = '" + password + "';", false);

	        if (!usersDB.emptyResult())
	        {
	        	std::cout << "\nSuccessful login attempt.\n";
	        	usersDB.run("UPDATE ACCOUNTS SET LAST_LOGIN = date('now') WHERE USERNAME = '" + username + "' AND PASSWORD = '" + password + "';", false);
	        	return true;
	        }
	        else
	        {
	        	std::cout << "\nUnsuccessful login attempt. Please try again.\n";
	        }
	    }

	    // Sign Up

	    if (userInt == 2)
	    {
	       

	    }

	} while (userInt != 3);

	return false;
}

void UserInterface::runMenu()
{
	int userInt;
    std::string userFlower;
    std::string newName;
    std::string spotter;
    std::string location;
    std::string date;

    do {
	    std::cout << "\nFUNCTIONS:\n1. Query\tDisplay the 10 most recent sightings of a flower\n2. Update\tUpdate the information of a flower\n3. Insert\tAdd a new sighting of a flower\n4. Quit" << std::endl;
	    std::cout << "Input an Integer (1, 2, 3, or 4): ";

	    std::cin >> userInt;

	    // Query

	    if (userInt == 1)
	    {
	        flowersDB.run("SELECT COMNAME FROM FLOWERS;");

	        std::cout << "Please enter the name of a flower: ";

	        std::cin.ignore();
	        getline(std::cin, userFlower);

	        clear();

	        flowersDB.run("SELECT PERSON, LOCATION, SIGHTED FROM SIGHTINGS WHERE NAME = '" + userFlower + "' ORDER BY SIGHTED DESC LIMIT 10;");
	    }

	    // Update

	    if (userInt == 2)
	    {
	        flowersDB.run("SELECT COMNAME FROM FLOWERS;");

	        std::cout << "Please enter the name of a flower to update: ";

	        std::cin.ignore();
	        getline(std::cin, userFlower);

	        std::cout << "Please enter the new genus of the flower: ";

	        getline(std::cin, newName);

	        flowersDB.run("UPDATE FLOWERS SET GENUS = '" + newName + "' WHERE COMNAME = '" + userFlower + "';", false);

	        std::cout << "Please enter the new species of the flower: ";

	        getline(std::cin, newName);

	        flowersDB.run("UPDATE FLOWERS SET SPECIES = '" + newName + "' WHERE COMNAME = '" + userFlower + "';", false);

	        std::cout << "Please enter the new common name for the flower: ";

	        getline(std::cin, newName);

	        flowersDB.run("UPDATE FLOWERS SET COMNAME = '" + newName + "' WHERE COMNAME = '" + userFlower + "';", false);

	    }

	    // Insert

	    if (userInt == 3)
	    {
	    	std::cout << "Please enter the name of the flower being inserted: ";

	    	std::cin.ignore();
	        getline(std::cin, userFlower);

	        std::cout << "Please enter the name of the person who spotted the flower: ";

	        getline(std::cin, spotter);

	        std::cout << "Please enter the location where the flower was spotted: ";

	        getline(std::cin, location);

	        std::cout << "Please enter the date the flower was spotted (yyyy-mm-dd): ";

	        getline(std::cin, date);

	        flowersDB.run("INSERT INTO SIGHTINGS VALUES('" + userFlower + "', '" + spotter + "', '" + location + "', '" + date + "');", false);
	    }
	} while (userInt != 4);
}

void UserInterface::clear()
{
	std::cout  <<  "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
}