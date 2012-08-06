#include "utils.h"

class Gameoflife {
 
 private:
  WINDOW *game;
  int seed, running;
  int numberAliveCellsAround();
 public:
  Gameoflife();
  void update();
  void render();
}
