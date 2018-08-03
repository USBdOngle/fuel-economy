#include<fstream>
#include<iostream>
#include<string>
#include<list>
#include<cstdlib>
#include"dataEntry.h"


//loads previously recorded entries from file
//input: address to list which contains pointers to loaded entries, file object
//output 1 for success, 0 for fail

bool loadEntries(std::list<dataEntry*> &entriesPrev) {

	std::ifstream file;
	file.open("saveData.txt");

	if (file.is_open()) {

		std::string line; //line containing a single previous entry

		double values[6] = { 0 }; // data, odo, litres, priceTotal, pricePerLitre, efficiency


		std::string entry; //single entry value read from line

						   //iterate through each line in file for each data entry
		while (std::getline(file, line)) {
			//checks to see if on end of file
			if (line.length() < 2) {
				break;
			}

			int posStart = 0; //beginning of single value in line
			int len = 0;	  //length of single value in line
			int posVal = 0;

			for (int i = 0; i <= line.length(); i++) {
				if (line[i] == ' ' || i == line.length()) { //end of value

					entry = line.substr(posStart, len);
					values[posVal] = stod(entry, 0);
					entry.clear();
					posVal++;
					posStart += len + 1;
					len = 0;
					continue;
				}

				else {
					len++;;
				}

			}

			//store values in new dataEntry object and pushes to passed in list
			dataEntry* newEntry = new dataEntry((int)values[0], (int)values[1], values[2], values[3], values[4], values[5]);
			entriesPrev.push_back(newEntry);

		}

		file.close();
		return true;
	}

	return false;
}

//saves entries from list to file
//input: address to list which contains pointers to loaded entries, file object
//output 1 for success, 0 for fail

bool saveEntries(std::list<dataEntry*> &entries) {

	std::ofstream file;
	file.open("saveData.txt", std::fstream::out);

	if (file.is_open()) {
		for (std::list<dataEntry*>::iterator entry = entries.begin(); entry != entries.end(); ++entry) { //iterate through list and save each entry to file in order
			(*entry)->saveEntry(file);
		}

		file.close();
		return true;
	}

	return false;
}