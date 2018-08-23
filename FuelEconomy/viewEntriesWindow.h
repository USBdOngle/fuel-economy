#include<Windows.h>
#include<FL/Fl.h>
#include<FL/Fl_Double_Window.H>
#include<FL/Fl_Table.H>
#include<FL/fl_draw.H>
#include<vector>
#include<list>
#include<string>
#include"dataEntry.h"

class viewEntriesWindow : public Fl_Table {

public:
	
	viewEntriesWindow(std::list<dataEntry*> &entryList, int x, int y, int w, int h, const char *L=0);
	~viewEntriesWindow();

private:
	
	std::vector<std::vector<double>> data;
	std::list<dataEntry*> entryList;

	void drawHeader(const char *s, int x, int y, int w, int h);
	void drawData(const char *s, int x, int y, int w, int h);
	void drawCell(TableContext context, int row = 0, int col = 0, int x = 0, int y = 0, int w = 0, int h = 0);

	void fillData();
	void dataToChar(char* s, int row, int col);
};

