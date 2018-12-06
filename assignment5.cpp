#include <iostream>
#include <string>
#include "include/SQLiteDatabaseInstance.h"

using namespace std;

void clear()
{
	cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
}

int main()
{
	clear();

	SQLiteDatabaseInstance sql = SQLiteDatabaseInstance("flowers.db");

	// START DATABASE SCHEMA ALTERATIONS

	/* 
	 * Added ON UPDATE CASCADE ON DELETE SET NULL to the foreign key
	 * constraints on SIGHTINGS to have it be automatically updated 
	 * when the changes a flower's information.
	 *
	 */
	sql.run("PRAGMA foreign_keys=off;"
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

	// END DATABASE SCHEMA ALTERATIONS

	string userInt;
    string userFlower;
    string newName;
    string spotter;
    string location;
    string date;

    do {
	    cout<<"FUNCTIONS:\n1. Query\tDisplay the 10 most recent sightings of a flower\n2. Update\tUpdate the information of a flower\n3. Insert\tAdd a new sighting of a flower\n4. Quit"<<endl;
	    cout<<"Input an Integer (1, 2, 3, or 4): ";


	    cin >> userInt;

	    // Query

	    if (userInt == "1")
	    {
	        sql.run("SELECT COMNAME FROM FLOWERS;");

	        cout<<"Please enter the name of a flower: ";

	        cin.ignore();
	        getline(cin, userFlower);

	        clear();

	        sql.run("SELECT PERSON, LOCATION, SIGHTED FROM SIGHTINGS WHERE NAME = '" + userFlower + "' ORDER BY SIGHTED DESC LIMIT 10;");
	    }

	    // Update

	    if (userInt == "2")
	    {
	        sql.run("SELECT COMNAME FROM FLOWERS;");

	        cout<<"Please enter the name of a flower to update: ";

	        cin.ignore();
	        getline(cin, userFlower);

	        cout<<"Please enter the new genus of the flower: ";

	        getline(cin, newName);

	        sql.run("UPDATE FLOWERS SET GENUS = '" + newName + "' WHERE COMNAME = '" + userFlower + "';", false);

	        cout<<"Please enter the new species of the flower: ";

	        getline(cin, newName);

	        sql.run("UPDATE FLOWERS SET SPECIES = '" + newName + "' WHERE COMNAME = '" + userFlower + "';", false);

	        cout<<"Please enter the new common name for the flower: ";

	        getline(cin, newName);

	        sql.run("UPDATE FLOWERS SET COMNAME = '" + newName + "' WHERE COMNAME = '" + userFlower + "';", false);

	    }

	    // Insert

	    if (userInt == "3")
	    {
	    	cout<<"Please enter the name of the flower being inserted: ";

	    	cin.ignore();
	        getline(cin, userFlower);

	        cout<<"Please enter the name of the person who spotted the flower: ";

	        getline(cin, spotter);

	        cout<<"Please enter the location where the flower was spotted: ";

	        getline(cin, location);

	        cout<<"Please enter the date the flower was spotted (yyyy-mm-dd): ";

	        getline(cin, date);

	        sql.run("INSERT INTO SIGHTINGS VALUES('" + userFlower + "', '" + spotter + "', '" + location + "', '" + date + "');", false);
	    }
	} while (userInt != "4");

	return 0;
}