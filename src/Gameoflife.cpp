#include <string>
#include <ncurses.h>
#include "utils.h"
#include "Gameoflife.h"

class Gameoflife {
 private:
  WINDOW *game;
  int seed, running;
  int numberAliveCellsAround();
  
  Gameoflife::Gameoflife(){
    this.game = newwin(20,20,0,0);
    bow(game,0,0);
    wrefresh(game);
    this.seed = 0;
    this.running = 0;
  }

  int Gameoflife::numberAliveCellsAround(){
    
  }

  void Gameoflife::update(){

  }

  void Gameoflife::render(){

  }
}
