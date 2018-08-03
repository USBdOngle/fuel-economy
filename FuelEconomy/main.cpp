//Fuel Economy Tracker
//Christopher Rennie

#include<cstdlib>
#include<iostream>
#include<list>
#include<fstream>
#include<string>
#include<Windows.h>
#include<FL/Fl.H>
#include<FL/Fl_Window.H>
#include<FL/Fl_Box.H>
#include<FL/Fl_Output.H>
#include"dataEntry.h"
#include"fileOps.h"
#include"entryStats.h"
#include"mainWindow.h"


int main() {

	std::list<dataEntry*> testList;

	/*for (int i = 0; i < 5; i++) {
	dataEntry* test = new dataEntry(20180101, 67888, 56.11, 45.33, 1.27, 9.78);
	testList.push_back(test);
	}

	saveEntries(testList);*/


	loadEntries(testList);

	entryStats* testStats = new entryStats(testList);

	mainWindow win(testStats, testList, 480, 360, "Fuel Economy");

	/*dataEntry* testEntry = new dataEntry(20180109, 69920, 52.11, 58.33, 1.35, 0);

	testList.back()->updateEfficiency(testEntry);

	testStats->updateStats(testEntry, testList);

	testList.push_back(testEntry);

	saveEntries(testList);
	
	return 0;*/

	return Fl::run();
}
//fix bug not displaying correct updated efficiency




