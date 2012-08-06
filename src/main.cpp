#ifdef HAVE_CONFIG_H
  #include <config.h>
#endif

#include <ncurses.h>
#include <string>
#include "utils.h"
#include "Gameoflife.h"

using namespace std;

int main()
{

  /* Initialisation - Menu */
  string str_title = "Game Of Life";
  string str_press = "Press a touch to continue";

  initscr();
  raw();
  noecho();
  init_colors();

  print_color(stdscr, LINES / 2, (COLS - str_title.length()) / 2, WHITE, str_title);
  print_color(stdscr, LINES - 1.0, 0, BLUE, str_press);
  refresh();
  getch();

  /* GameOfLife */
  erase();
  Gameoflife gol;
  gol.start();
  endwin(); 
  return 0;

}
