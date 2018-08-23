//I used "table-simple.cxx" included in the example folder of ftlk 1.3.4 download as a template for this code
//credit to the original author Greg Ercolano

#include "viewEntriesWindow.h"

viewEntriesWindow::viewEntriesWindow(std::list<dataEntry*> &entryList, int x, int y, int w, int h, const char *l) : Fl_Table(x, y, w, h, l) {
	//fill 2d data vector
	fillData();
	// Rows
	
	rows(entryList.size());             // how many rows
	row_header(0);              // disable row headers (along left)
	row_height_all(20);         // default height of rows
	row_resize(0);              // disable row resizing
								// Cols
	cols(6);             // how many columns
	col_header(1);              // enable column headers (along top)
	col_width_all(80);          // default width of columns
	col_resize(1);              // enable column resizing
	end();
	
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
viewEntriesWindow::drawCell(TableContext context, int row, int col, int x, int y, int w, int h) {
	static char s[40];
	std::string colHeaders[6] = { "Date (YYYY/MM/DD)", "Odometer", "Total Cost", "Litres", "$/Litre", "L/100km" };
	
	switch (context) {
	case CONTEXT_STARTPAGE:                   // before page is drawn..
		fl_font(FL_HELVETICA, 16);              // set the font for our drawing operations
		return;
	case CONTEXT_COL_HEADER:                  // Draw column headers
		colHeaders[col].copy(s, colHeaders[col].size(), 0); //copy col headers from string array into s[]
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
viewEntriesWindow::fillData() {
	int i = 0;
	for (std::list<dataEntry*>::iterator entry = entryList.begin(); entry != entryList.end(); ++entry) {
		data[i] = (*entry)->returnAllData();
		i++;
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

	case 1:
		str = std::to_string((int)data[row][col]);
		break;
	
	default:
		str = std::to_string(data[row][col]);
		break;
	}

	strcpy_s(s, str.length() + 1, str.c_str()); //copy string to c-string
}