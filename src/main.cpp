#ifdef HAVoE_CONFIG_H
  #include <config.h>
#endif

#include <ncurses.h>
#include <string>
#include "utils.h"

using namespace std;

int main()
{
  
  string title = "Game Of Life";
  string credits = "Kevin Bacas & Maxence Adnot";

  initscr();
  init_colors();
  print_color(stdscr, LINES / 2, (COLS - title.length()) / 2, WHITE,  title);
  print_color(stdscr, LINES - 1.0, 0, BLUE, credits);
  refresh();
  getch();
  endwin(); 
  return 0;

}
