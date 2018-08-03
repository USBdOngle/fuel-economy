#include "newEntryWindow.h"



newEntryWindow::newEntryWindow(std::list<dataEntry*> &entries, entryStats* userStats, Fl_Widget* effWidget, Fl_Widget* distWidget, Fl_Widget* fillsWidget, Fl_Widget* litreWidget, int width, int height, const char* title) : Fl_Window(width, height, title){
	
	entryList = entries; 
	stats = userStats;

	effW = effWidget;
	distW = distWidget;
	fillsW = fillsWidget;
	litreW = litreWidget;

	begin();
	
	//date input box
	dateInput = new Fl_Input(55, 25, 160, 35, "Date");
	dateInput->labelfont(FL_BOLD);
	dateInput->labelsize(18);

	//odo input box
	odoInput = new Fl_Input(55, 80, 160, 35, "ODO");
	odoInput->labelfont(FL_BOLD);
	odoInput->labelsize(18);

	//total price input box
	priceTotalInput = new Fl_Input(55, 135, 160, 35, "Total $");
	priceTotalInput->labelfont(FL_BOLD);

	//total litres input box
	litresTotalInput = new Fl_Input(55, 190, 160, 35, "Litres");
	litresTotalInput->labelfont(FL_BOLD);
	litresTotalInput->labelsize(18);

	setDefaultValuesW();

	//save current entry button
	saveButton = new Fl_Button(25, 260, 190, 70, "SAVE");
	saveButton->labelsize(24);
	saveButton->callback(CBsaveAndUpdate, this);

	end();
	show();
}


newEntryWindow::~newEntryWindow()
{
}

//converts user input to doubles so they can be stored in dataEntry object
//returns True if inputs are correctly formatted, false if not
bool newEntryWindow::convertInputs(double convertedInputs[4], const char* date, const char* odo, const char* priceTotal, const char* litresTotal) {

	//convert date
	std::string dateS = std::string(date);
	dateS.erase(std::remove(dateS.begin(), dateS.end(), '/'), dateS.end());
	double dateD = stod(dateS);
	
	//convert odo
	std::string odoS = std::string(odo);
	double odoD = stod(odoS);

	//convert priceTotal
	std::string priceTotalS = std::string(priceTotal);
	double priceTotalD = stod(priceTotalS);

	//convert litresTotal
	std::string litresTotalS = std::string(litresTotal);
	double litresTotalD = stod(litresTotalS);

	//add array
	convertedInputs[0] = dateD;
	convertedInputs[1] = odoD;
	convertedInputs[2] = priceTotalD;
	convertedInputs[3] = litresTotalD;
	
	return true;
}

void
newEntryWindow::CBsaveAndUpdate(Fl_Widget* , void* v) {
	((newEntryWindow*)v)->CBsaveAndUpdateI();
}

//takes user inputs, creates new dataEntry object, pushes to back of datEntry list, and updates statistics for user
void newEntryWindow::CBsaveAndUpdateI() {
	
	double inputs[4]; //date, odo , priceTotal, litresTotal
	
	while (!convertInputs(inputs, dateInput->value(), odoInput->value(), priceTotalInput->value(), litresTotalInput->value())) {
		//add code to prompt user of bad input and try again
	}
	
	//save entry
	dataEntry* newEntry = new dataEntry(inputs[0], inputs[1], inputs[2], inputs[3], 0, 0);
	
	if (entryList.size() != 0) { //cannot update stats if it is the first entry
		entryList.back()->updateEfficiency(newEntry);
	}
	
	stats->updateStats(newEntry, entryList);
	entryList.push_back(newEntry);
	saveEntries(entryList); //save to file

	setDefaultValuesW(); //reset input boxes to user format guide text on new entry window
	updateStatMainW(); //update stats on main window
}

//updates stat widgets on main window with latest info
void newEntryWindow::updateStatMainW() {
	
	effW->label(stats->returnStatS(0));
	distW->label(stats->returnStatS(1));
	fillsW->label(stats->returnStatS(2));
	litreW->label(stats->returnStatS(3));
}

//sets the default value of the input widgets to guide user input
void newEntryWindow::setDefaultValuesW() {
	
	dateInput->value("YYYY/MM/DD");
	odoInput->value("X...X");
	priceTotalInput->value("XX.xx");
	litresTotalInput->value("XX.xx");
}