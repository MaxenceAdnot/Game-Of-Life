#ifdef HAVE_CONFIG_H
  #include <config.h>
#endif

#include <ncurses.h>
#include "utils.h"
#include "Gameoflife.h"


int main()
{
  initscr();
  raw();
  noecho();
  init_colors();

  run_splash();
  run_game();
  
  destroy();
  endwin(); 
  return 0;
}
