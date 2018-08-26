#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Button.h>
#include <list>
#include "entryStats.h"

class mainWindow : public Fl_Window{

public:
	
	mainWindow(entryStats* stats, std::list<dataEntry*> &entries, int width, int height, const char* title);
	~mainWindow();

	Fl_Box* effAvgStat; //textbox for efficiency value
	Fl_Box* effAvgLabel; //title for efficiency box
	Fl_Box* distStat; //box for distance value
	Fl_Box* distLabel; //title
	Fl_Box* fillsStat; //number of fills
	Fl_Box* fillsLabel; //title
	Fl_Box* avgLitreStat; //avg price per litre
	Fl_Box* avgLitreLabel; //title

	Fl_Button* addNewEntry; //button to click to go to new entry window
	Fl_Button* viewEntries; //button to click to view entries
	Fl_Button* reset; //button to delete all entries and reset statistics

private:
	
	static void CBopenEntryWindow(Fl_Widget*, void* v);
	inline void CBopenEntryWindowI();

	static void CBresetData(Fl_Widget*, void* v);
	inline void CBresetDataI();

	static void CBviewEntriesWindow(Fl_Widget*, void* v);
	inline void CBviewEntriesWindowI();
	static void CBquitViewEntriesWindow(Fl_Widget* widget, void* v);
	inline void CBquitViewEntriesWindowI(Fl_Widget* widget);

	void resetEntryList();
	void setStatWidgetLabels();
	
	std::list<dataEntry*> entryList;
	entryStats* stats;

};

