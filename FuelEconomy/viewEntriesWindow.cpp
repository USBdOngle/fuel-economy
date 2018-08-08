//Most of this code is just modified from "table-simple.cxx" included in the example folder of ftlk 1.3.4 download
//credit to the original author Greg Ercolano

#include "viewEntriesWindow.h"



viewEntriesWindow::viewEntriesWindow(std::list<dataEntry*> entryList, int x, int y, int w, int h, const char *l = 0) : Fl_Table(x,y,w,h,l) {
}


viewEntriesWindow::~viewEntriesWindow()
{
}

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

void
viewEntriesWindow::drawCell(TableContext context, int row = 0, int col = 0, int x = 0, int y = 0, int w = 0, int h = 0) {
	static char s[40];
	switch (context) {
	case CONTEXT_STARTPAGE:                   // before page is drawn..
		fl_font(FL_HELVETICA, 16);              // set the font for our drawing operations
		return;
	case CONTEXT_COL_HEADER:                  // Draw column headers
		sprintf(s, "%c", 'A' + COL);                // change so it puts in the labels for the data
		drawHeader(s, x, y, w, h);
		return;
	
	case CONTEXT_CELL:                        // Draw data in cells
		sprintf(s, "%d", data[ROW][COL]);		//change so it gets data from vector<vector<double>>
		drawData(s, x, y, w, h);
		return;
	default:
		return;
	}
}
}