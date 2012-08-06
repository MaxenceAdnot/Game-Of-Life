#ifndef DEF_GAMEOFLIFE
#define DEF_GAMEOFLIFE



class Gameoflife {
 
 private:
  WINDOW *game;
  int seed, running;
  int numberAliveCellsAround();

 public:
  Gameoflife();
  void update();
  void render();
  void start();
};

#endif

