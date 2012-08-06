#include <string>
#include <ncurses.h>
#include "utils.h"

using namespace std;

void init_colors(){
  start_color();
  init_pair(BLUE, COLOR_BLUE, COLOR_BLACK);
}


void print_color(WINDOW *win, int y, int x, int color, string str) {

  attron(COLOR_PAIR(color));
  mvwprintw(win, y, x, "%s", str.c_str());
  attroff(COLOR_PAIR(color));
  wrefresh(win);

}
