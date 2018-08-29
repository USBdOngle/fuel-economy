#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Button.h>
#include <FL/Fl_Input.H>
#include <FL/fl_ask.H>
#include <list>
#include <algorithm>
#include <string>
#include <iterator>
#include "entryStats.h"
#include "dataEntry.h"
#include "fileOps.h"


class newEntryWindow : public Fl_Window {

public:
	
	newEntryWindow(std::list<dataEntry*> &entries, entryStats* userStats, Fl_Widget* effWidget, Fl_Widget* distWidget, Fl_Widget* fillsWidget, Fl_Widget* litreWidget, int width, int height, const char* title);
	~newEntryWindow();

	Fl_Input* dateInput; //receives user date input
	Fl_Input* odoInput; //receives user odo input
	Fl_Input* priceTotalInput; //receives user total price input
	Fl_Input* litresTotalInput; //receives user total litres input
	Fl_Button* saveButton; //button to save entry from input boxes

private:

	std::list<dataEntry*> entryList;
	entryStats* stats;

	//widgets from main window to update from new entry window
	Fl_Widget* effW;
	Fl_Widget* distW;
	Fl_Widget* fillsW;
	Fl_Widget* litreW;

	static void CBsaveAndUpdate(Fl_Widget*, void* v);
	inline void CBsaveAndUpdateI();

	bool checkInput(double convertedInputs[4]);
	bool convertInputs(double convertedInputs[4], const char* date, const char* odo, const char* priceTotal, const char* litresTotal);
	void updateStatMainW();
	void setDefaultValuesW();
};


