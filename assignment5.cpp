#include <iostream>
#include <string>
#include "include/SQLiteDatabaseInstance.h"

using namespace std;

int main()
{
	SQLiteDatabaseInstance sql = SQLiteDatabaseInstance("flowers.db");

	// START DATABASE SCHEMA ALTERATIONS
	
	 /* 
	 * Added ON UPDATE CASCADE ON DELETE SET NULL to the foreign key
	 * constraints on SIGHTINGS to have it be automatically updated 
	 * when the changes a flower's information.
	 */
	sql.run("	PRAGMA foreign_keys=off;

				ALTER TABLE SIGHTINGS RENAME TO _SIGHTINGS_OLD;

				CREATE TABLE SIGHTINGS (
					NAME	VARCHAR ( 30 ),
					PERSON	VARCHAR ( 30 ),
					LOCATION	VARCHAR ( 30 ),
					SIGHTED	DATE,
					CONSTRAINT sightings_pk PRIMARY KEY(`NAME`,`PERSON`,`LOCATION`,`SIGHTED`),
					CONSTRAINT fk1_sightings FOREIGN KEY(`NAME`) REFERENCES `FLOWERS`(`COMNAME`) ON UPDATE CASCADE ON DELETE SET NULL,
					CONSTRAINT fk2_sightings FOREIGN KEY(`LOCATION`) REFERENCES `FEATURES`(`LOCATION`) ON UPDATE CASCADE ON DELETE SET NULL
				);

				INSERT INTO SIGHTINGS SELECT * FROM _SIGHTINGS_OLD;

				DROP TABLE _SIGHTINGS_OLD;

				PRAGMA foreign_keys=on;");

	// END DATABASE SCHEMA ALTERATIONS

	int userInt;
    string userFlower;
    string newName;
    string spotter;
    string location;
    string date;

    do {
	    cout<<"1. Query\n2. Update\n3. Insert\n4. Quit"<<endl;
	    cout<<"Input an Integer (1, 2, 3, or 4): ";

	    cin >> userInt;

	    //query
	    if (userInt == 1)
	    {
	        sql.run("SELECT COMNAME FROM FLOWERS;");

	        cout<<"Please enter the name of a flower: ";

	        cin.ignore();
	        getline(cin, userFlower);

	        sql.run("SELECT PERSON, LOCATION, SIGHTED FROM SIGHTINGS WHERE NAME = '" + userFlower + "' ORDER BY SIGHTED DESC;");
	        //TODO cut off after 10 sightings

	    }
	    //update
	    if (userInt == 2)
	    {
	        sql.run("SELECT COMNAME FROM FLOWERS;");

	        cout<<"Please enter the name of a flower to update: ";

	        cin.ignore();
	        getline(cin, userFlower);

	        cout<<"Please enter the new genus of the flower: ";

	        cin.ignore();
	        getline(cin, newName);

	        sql.run("UPDATE FLOWERS SET GENUS = '" + newName + "' WHERE COMNAME = '" + userFlower + "';");

	        cout<<"Please enter the new species of the flower: ";

	        cin.ignore();
	        getline(cin, newName);

	        sql.run("UPDATE FLOWERS SET SPECIES = '" + newName + "' WHERE COMNAME = '" + userFlower + "';");

	        cout<<"Please enter the new common name for the flower: ";

	        cin.ignore();
	        getline(cin, newName);

	        sql.run("UPDATE FLOWERS SET COMNAME = '" + newName + "' WHERE COMNAME = '" + userFlower + "';");
	        //sql.run("UPDATE SIGHTINGS SET NAME = '" + newName + "' WHERE NAME = '" + userFlower + "';");
	        sql.run("SELECT * FROM FLOWERS");

	    }
	    //insert
	    if (userInt == 3)
	    {
	    	cout<<"Please enter the name of the flower being inserted: ";

	        cin.ignore();
	        getline(cin, userFlower);

	        cout<<"Please enter the name of the person who spotted the flower: ";

	        cin.ignore();
	        getline(cin, spotter);

	        cout<<"Please enter the location where the flower was spotted: ";

	        cin.ignore();
	        getline(cin, location);

	        cout<<"Please enter the date the flower was spotted (yyyy-mm-dd): ";

	        cin.ignore();
	        getline(cin, date);

	        sql.run("INSERT INTO SIGHTINGS VALUES('" + userFlower + "', '" + spotter + "', '" + location + "', '" + date + "');");

	    }
	} while (userInt != 4);
	return 0;
}