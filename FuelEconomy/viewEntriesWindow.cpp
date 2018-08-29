//I used "table-simple.cxx" included in the example folder of ftlk 1.3.4 download as a template for this code
//credit to the original author Greg Ercolano
#pragma once
#include "viewEntriesWindow.h"

viewEntriesWindow::viewEntriesWindow(std::list<dataEntry*> &entryList, int x, int y, int w, int h, const char *l) : Fl_Table(x, y, w, h, l) {
	//fill 2d data vector
	fillData(entryList);
	// Rows
	
	rows(entryList.size());             // how many rows
	row_header(0);              // disable row headers (along left)
							// Cols
	cols(5);             // how many columns
	col_header(1);              // enable column headers (along top)
	col_width_all(160);          // default width of columns
	col_resize(1);              // enable column resizing
	end();
	show();
}

viewEntriesWindow::~viewEntriesWindow() {}

void
viewEntriesWindow::drawHeader(const char *s, int x, int y, int w, int h) {
	fl_push_clip(x, y, w, h);
	fl_draw_box(FL_THIN_UP_BOX, x, y, w, h, row_header_color());
	fl_color(FL_BLACK);
	fl_draw(s, x, y, w, h, FL_ALIGN_CENTER);
	fl_pop_clip();
}

void
viewEntriesWindow::drawData(const char *s, int x, int y, int w, int h) {
	fl_push_clip(x, y, w, h);
	// Draw cell bg
	fl_color(FL_WHITE); fl_rectf(x, y, w, h);
	// Draw cell data
	fl_color(FL_GRAY0); fl_draw(s, x, y, w, h, FL_ALIGN_CENTER);
	// Draw box border
	fl_color(color()); fl_rect(x, y, w, h);
	fl_pop_clip();
}

//this function is called by fl_table, we do not call it
void
viewEntriesWindow::draw_cell(TableContext context, int row, int col, int x, int y, int w, int h) {
	static char s[40];
	std::string colHeaders[5] = { "Date (YYYY/MM/DD)", "Odometer", "Total Cost", "Litres", "$/Litre" };
	
	switch (context) {
	case CONTEXT_STARTPAGE:                   // before page is drawn..
		fl_font(FL_HELVETICA, 16);              // set the font for our drawing operations
		return;
	case CONTEXT_COL_HEADER:                  // Draw column headers
		memset(s, 0, sizeof(s));
		colHeaders[col].copy(s, colHeaders[col].size(), 0); //copy col header from string array into s[]
		drawHeader(s, x, y, w, h);
		return;
	case CONTEXT_CELL:                        // Draw data in cells
		dataToChar(s, row, col);
		drawData(s, x, y, w, h);
		return;
	
	default:
		return;
	}
}

//populate 2d vector data with data from all entries to be displayed in the table
void
viewEntriesWindow::fillData(std::list<dataEntry*> &entryList) {
	for (std::list<dataEntry*>::iterator entry = entryList.begin(); entry != entryList.end(); ++entry) {
		data.push_back((*entry)->returnAllData());
	}
}

void
viewEntriesWindow::dataToChar(char* s, int row, int col) {
	std::string str;
	
	switch (col) {
	case 0: //date
		str = std::to_string((int)data[row][col]);
		str.insert(4, "/");
		str.insert(7, "/");
		break;

	case 1: //ODO
		str = std::to_string((int)data[row][col]);
		break;
	
	default: 
		str = std::to_string(data[row][col]);
		break;
	}
	
	int pos = str.find("."); //where to start trim
	if (!(pos == std::string::npos)) { //does not contain "."
		str.erase(str.begin() + pos + 3, str.end()); //delete trailing zeros after two digts of significance
	}

	strcpy_s(s, str.length() + 1, str.c_str()); //copy string to c-string
}