//Fuel Economy Tracker
//Christopher Rennie

#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup") //prevent console from opening

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
	return Fl::run();
}





