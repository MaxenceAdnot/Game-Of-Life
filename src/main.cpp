#ifdef HAVE_CONFIG_H
  #include <config.h>
#endif

#include <string>
#include <ncurses.h>

using namespace std;

int main()
{

  string mesg = "Hello World !";
  initscr();
  mvprintw(LINES / 2, (COLS - mesg.length()) / 2, "%s" , mesg.c_str());
  refresh();
  getch();
  endwin(); 
  return 0;
}
