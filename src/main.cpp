#ifdef HAVE_CONFIG_H
  #include <config.h>
#endif

#include <string>
#include <ncurses.h>

using namespace std;

int main()
{

  string mesg = "Game Of Life";
  initscr();
  mvprintw(LINES / 2, (COLS - mesg.length()) / 2, "%s" , mesg.c_str());
  mvprintw(LINES - 1.0, 0, "Kevin Bacas & Maxence Adnot");
  refresh();
  getch();
  endwin(); 
  return 0;
}
