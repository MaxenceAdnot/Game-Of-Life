#include <string>
#include <ncurses.h>
#include "utils.h"
#include "Gameoflife.h"

Gameoflife::Gameoflife(){
  game = subwin(stdscr, (int)((LINES*9)/10) , (int)((COLS*9)/10) , (int)(LINES/40) , (int)(COLS/20));
  box(game,0,0);
  wrefresh(game);
  seed = 0;
  running = 0;
}

void Gameoflife::update(){

}

void Gameoflife::render(){
  while (getch() != '\n'){
    wrefresh(game);
  }

}

void Gameoflife::start(){
  update();
  render();
}

int Gameoflife::numberAliveCellsAround(){
  return 0;
}
