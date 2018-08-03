#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Button.h>
#include <FL/fl_ask.H>
#include <list>
#include "entryStats.h"
#include "mainWindow.h"
#include "newEntryWindow.h"

mainWindow::mainWindow(entryStats* userStats, std::list<dataEntry*> &entries, int width, int height, const char* title) : Fl_Window(width, height, title) {
	entryList = entries;
	stats = userStats;

	begin();
	
	//efficiency stat box
	effAvgStat = new Fl_Box(160, 60, 160, 90); //stats->returnEffAvgS()); 
	effAvgStat->box(FL_NO_BOX);
	effAvgStat->labelfont(FL_BOLD);
	effAvgStat->labelsize(64);
	effAvgStat->labeltype(FL_ENGRAVED_LABEL);
	
	//effciency label box
	effAvgLabel = new Fl_Box(195, 110, 90, 90, "L/100km (Avg)");
	effAvgLabel->box(FL_NO_BOX);
	effAvgLabel->labelsize(24);

	//total distance stat box
	distStat = new Fl_Box(45, 160, 120, 90);
	distStat->labelfont(FL_BOLD);
	distStat->labelsize(36);
	distStat->labeltype(FL_ENGRAVED_LABEL);

	//total distance label box
	distLabel = new Fl_Box(60, 190, 90, 90, "Distance (km)");
	distLabel->box(FL_NO_BOX);
	distLabel->labelsize(14);
	
	//total fills stat box
	fillsStat = new Fl_Box(195, 160, 90, 90);
	fillsStat->box(FL_NO_BOX);
	fillsStat->labelfont(FL_BOLD);
	fillsStat->labelsize(36);
	fillsStat->labeltype(FL_ENGRAVED_LABEL);

	//total fills label box
	fillsLabel = new Fl_Box(195, 190, 90, 90, "Fills");
	fillsLabel->box(FL_NO_BOX);
	fillsLabel->labelsize(14);

	//avg price per litre stat box
	avgLitreStat = new Fl_Box(335, 160, 90, 90);
	avgLitreStat->box(FL_NO_BOX);
	avgLitreStat->labelfont(FL_BOLD);
	avgLitreStat->labelsize(36);
	avgLitreStat->labeltype(FL_ENGRAVED_LABEL);

	//avg price per litre label box
	avgLitreLabel = new Fl_Box(335, 190, 90, 90, "Avg $/Litre");
	avgLitreLabel->box(FL_NO_BOX);
	avgLitreLabel->labelsize(14);

	//add new entry button
	addNewEntry = new Fl_Button(20, 270, 210, 60, "New Entry");
	addNewEntry->type(FL_NORMAL_BUTTON);
	addNewEntry->box(FL_UP_BOX);
	addNewEntry->labelsize(24);
	addNewEntry->callback(CBopenEntryWindow, this);

	//view past entries button
	viewEntries = new Fl_Button(250, 270, 210, 60, "View Entries");
	viewEntries->type(FL_NORMAL_BUTTON);
	viewEntries->box(FL_UP_BOX);
	viewEntries->labelsize(24);

	//reset statistics and delete entries button
	reset = new Fl_Button(20, 20, 65, 25, "Reset");
	reset->type(FL_NORMAL_BUTTON);
	reset->box(FL_UP_BOX);
	reset->labelsize(18);
	reset->callback(CBresetData, this);

	setStatWidgetLabels();

	end();
	show();
}


mainWindow::~mainWindow()
{
}

void
mainWindow::CBopenEntryWindow(Fl_Widget*, void* v) {
	((mainWindow*)v)->CBopenEntryWindowI(); //overcomes function being static so we can pass std::list<dataEntry*> and entryStats* into called functions
}

void
mainWindow::CBopenEntryWindowI() {
	newEntryWindow* window = new newEntryWindow(entryList, stats, effAvgStat, distStat, fillsStat, avgLitreStat, 240, 360, "New Entry");
}

void
mainWindow::CBresetData(Fl_Widget*, void* v) {
	((mainWindow*)v)->CBresetDataI();
}

//asks user if they want to continue with reset
//resets statistics, deletes entries in list, and clears saveData file
void
mainWindow::CBresetDataI() {
	
	switch (fl_choice("Are you sure you want to reset?", "Yes", "No", 0)) {
		case 0: //yes
			
			stats->resetStats(); //set all stats to 0
			resetEntryList(); //reset to null list
			saveEntries(entryList); //clears save file

			//set widgets on main window to reset stat values
			setStatWidgetLabels();
			break;
		
		case 1: //no
			break;
	}

}

void
mainWindow::resetEntryList() {
	
	//delete each dataEntry object pointed to in list
	for (std::list<dataEntry*>::iterator entry = entryList.begin(); entry != entryList.end(); ++entry) {
		delete *entry;
	}

	entryList.clear(); //deletes pointers within list and resets size to 0
}

//sets the label of the stat widgets to the current stat values
void
mainWindow::setStatWidgetLabels() {
	
	effAvgStat->label(stats->returnStatS(0));
	distStat->label(stats->returnStatS(1));
	fillsStat->label(stats->returnStatS(2));
	avgLitreStat->label(stats->returnStatS(3));
}
