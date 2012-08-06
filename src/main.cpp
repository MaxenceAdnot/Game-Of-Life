#ifdef HAVE_CONFIG_H
  #include <config.h>
#endif

#include <ncurses.h>
#include <string>
#include "utils.h"

using namespace std;

int main()
{
  
  string mesg = "Game Of Life";
  string credits = "Kevin Bacas & Maxence Adnot";

  initscr();
  init_colors();
  mvprintw(LINES / 2, (COLS - mesg.length()) / 2, "%s" , mesg.c_str());
  print_color(stdscr, LINES - 1.0, 0, BLUE, credits);
  refresh();
  getch();
  endwin(); 
  return 0;
}
