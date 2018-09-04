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
	dateInput = new Fl_Input(55, 35, 160, 35, "Date");
	dateInput->labelfont(FL_BOLD);
	dateInput->labelsize(18);

	//odo input box
	odoInput = new Fl_Input(55, 90, 160, 35, "ODO");
	odoInput->labelfont(FL_BOLD);
	odoInput->labelsize(18);

	//total price input box
	priceTotalInput = new Fl_Input(55, 145, 160, 35, "Total $");
	priceTotalInput->labelfont(FL_BOLD);

	//total litres input box
	litresTotalInput = new Fl_Input(55, 200, 160, 35, "Litres");
	litresTotalInput->labelfont(FL_BOLD);
	litresTotalInput->labelsize(18);

	setDefaultValuesW();

	//save current entry button
	saveButton = new Fl_Button(25, 260, 190, 70, "SAVE");
	saveButton->labelsize(24);
	saveButton->callback(CBsaveAndUpdate, this);

	//displays helpful information
	helpButton = new Fl_Button(15, 8, 40, 20, "HELP");
	helpButton->callback(CBdisplayHelp);

	end();
	show();
}


newEntryWindow::~newEntryWindow()
{
}

//converts user input to doubles so they can be stored in dataEntry object
//returns True if inputs are correctly formatted, false if not
bool newEntryWindow::convertInputs(double convertedInputs[4], const char* date, const char* odo, const char* priceTotal, const char* litresTotal) {

	double dateD;
	double odoD;
	double priceTotalD;
	double litresTotalD;

	//convert from const char* to string
	std::string dateS = std::string(date);
	dateS.erase(std::remove(dateS.begin(), dateS.end(), '/'), dateS.end());
	
	std::string odoS = std::string(odo);
	std::string priceTotalS = std::string(priceTotal);
	std::string litresTotalS = std::string(litresTotal);

	//check if inputs can convert to double/int
	try {
		
		dateD = stoi(dateS);
		odoD = stoi(odoS);
		priceTotalD = stod(priceTotalS);
		litresTotalD = stod(litresTotalS);
	}
	catch (...) {
		return false;
	}
	
	//add to array
	convertedInputs[0] = (double)dateD;
	convertedInputs[1] = (double)odoD;
	convertedInputs[2] = priceTotalD;
	convertedInputs[3] = litresTotalD;
	
	//check if inputs are well formed
	return checkInput(convertedInputs);
}

//returns true if inputs are well formed, current distance is greater than previous
//return false otherwise
bool
newEntryWindow::checkInput(double convertedInputs[4]) {

	//date isn't 8-digit length
	double test = convertedInputs[0] / 100000000;
	if (1 <= test || test <= 0.1) {
		return false;
	}

	//curent odo input is less than previous
	else if (entryList.size() > 0 && convertedInputs[1] <= entryList.back()->returnOdo()) {
		return false;
	}

	//add more checks as I think of them...
	else { return true; }
}

void
newEntryWindow::CBdisplayHelp(Fl_Widget*, void* v) {
	((newEntryWindow*)v)->CBdisplayHelpI();
}

void
newEntryWindow::CBdisplayHelpI() {
	
	const char* helpMessage = "IMPORTANT:\n-You must fill gas tank completely for proper\nefficiency tracking.\n-Do not forget to record every fill-up.\n-In either case you must reset and start over\n"
							  "or update saveData.txt manually (advanced).\n\nIf this is your first entry:\n -Your efficiency will be displayed after you\n input your second entry.\n\n"
							  "Legend:\n-Date = The date you fueled up on.\n-ODO = Odometer reading when you fueled up.\n-Total $ = Total cost of fuel-up.\n-Litres = Total number of litres purchased.";
		
	
	Fl_Double_Window* win = new Fl_Double_Window(300, 300, "Help");
	Fl_Multiline_Output* output = new Fl_Multiline_Output(5, 5, 290, 290, "");
	output->box(FL_NO_BOX);
	output->value(helpMessage);
	win->show();
}

void
newEntryWindow::CBsaveAndUpdate(Fl_Widget* , void* v) {
	((newEntryWindow*)v)->CBsaveAndUpdateI();
}

//takes user inputs, creates new dataEntry object, pushes to back of datEntry list, and updates statistics for user
void newEntryWindow::CBsaveAndUpdateI() {
	
	double inputs[4]; //date, odo , priceTotal, litresTotal

	if (!convertInputs(inputs, dateInput->value(), odoInput->value(), priceTotalInput->value(), litresTotalInput->value())) {
		//warns user about incorrect input;
		fl_choice("Incorrect input, please try again.", "OK", 0, 0); //OK default
		setDefaultValuesW();
		return;
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

