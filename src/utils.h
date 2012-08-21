#ifndef DEF_UTILS
#define DEF_UTILS 

  #define DEAD 0
  #define LIVING 1


  #define WHITE 0  
  #define BLUE  1 
  #define RED   2


  void init_colors(); 
  void print_color(WINDOW *win, int y, int x, int color, const char* str);
  int modulo(int x, int k); 
#endif
