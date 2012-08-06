#include <ncurses.h>
#include "utils.h"
#include "Gameoflife.h"

void update(){

}

void render(){
  while (getch() != '\n'){

  }
}

void start(){
  
  WINDOW *game;
  int seed = 0; 
  int running = 0;  

  game = subwin(stdscr, (int)((LINES*9)/10) , (int)((COLS*9)/10) , (int)(LINES/40) , (int)(COLS/20));
  box(game,0,0);
  wrefresh(game);

  update();
  render();
}

