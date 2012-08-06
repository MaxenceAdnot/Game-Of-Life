#ifdef HAVE_CONFIG_H
  #include <config.h>
#endif

#include <string.h>
#include <ncurses.h>
#include "utils.h"
#include "Gameoflife.h"


int main()
{

  /* Initialisation - Menu */
  char str_title[] = "Game Of Life";
  char str_press[] = "Press a touch to continue";

  initscr();
  raw();
  noecho();
  init_colors();

  print_color(stdscr, LINES / 2, (COLS - strlen(str_title)) / 2, WHITE, str_title);
  print_color(stdscr, LINES - 1.0, 0, BLUE, str_press);
  refresh();
  getch();

  /* GameOfLife */
  erase();
  start();

  endwin(); 
  return 0;

}
