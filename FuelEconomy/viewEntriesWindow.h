#pragma once
#include<FL/Fl.h>
#include<FL/Fl_Double_Window.H>
#include<FL/Fl_Table.H>
#include<FL/fl_draw.H>
#include<vector>
#include"dataEntry.h"

class viewEntriesWindow : public Fl_Table {

public:
	
	viewEntriesWindow(int x, int y, int w, int h, const char *L=0);
	~viewEntriesWindow();

private:
	
	std::vector<std::vector<int>> data;

	void drawHeader(const char *s, int x, int y, int w, int h);
	void drawData(const char *s, int x, int y, int w, int h);
	void drawCell(TableContext context, int row = 0, int col = 0, int x = 0, int y = 0, int w = 0, int h = 0);
};

