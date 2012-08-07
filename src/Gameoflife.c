#include <string.h>
#include <ncurses.h>
#include "utils.h"
#include "Gameoflife.h"


static WINDOW *game      = NULL;
static char   *cells     = NULL;
static char   *nextcells = NULL;

static int     GLINES = 0;
static int     GCOLS  = 0;
static int     CMAX   = 0;
static int     LMAX   = 0;

int input_mode(char ch){
  int y,x;
  
  getyx(game, y, x);
  switch(ch){
    case 'd': /* Right */
      if((x=(x+1)%CMAX)==0)
        x = 1; 
      break;
    case 'q': /* Left */
       if((x=(x-1)%CMAX)==0)
         x=CMAX - 1;
       break;
    case 's': /* Down */
       if((y=(y+1)%LMAX)==0)
         y = 1;
       break;
    case 'z': /* Up */
       if((y=(y-1)%LMAX)==0)
         y=LMAX - 1;
       break;
     case ' ': /* Activate a cell */
       if (cells[y*GCOLS+x] == 1){ /* Row-major order storage method */ 
         cells[y*GCOLS+x] = 0;
	 mvwaddch(game, y, x, ' ');
       }
       else {
         cells[y*GCOLS+x] = 1; 
         mvwaddch(game, y, x, 'O');
       }
       break;
     case '\n':
       play_mode();
       break;
     case 'k':
       return 0;
  }
  wmove(game, y, x); 
  wrefresh(game);
  return 1;
}


void play_mode(){
  
  int x , y , n; 
  
  memcpy(nextcells, cells, GLINES*GCOLS*sizeof(char));  

  for (x = 0; x < GCOLS; x++){
    for(y=0 ; y < GLINES; y++){
      n = nbAliveCells(y,x);
      if (n == 3){
        nextcells[y*GCOLS+x] = 1; 
        mvwaddch(game, y, x, 'O');
      }   
      else if( n < 2 || n > 3){
	nextcells[y*GCOLS+x] = 0;
	mvwaddch(game, y, x, ' ');
      }
    }
  }
  memcpy(cells, nextcells, GLINES*GCOLS*sizeof(char));
  wrefresh(game);

}


int nbAliveCells(int y, int x){
  
  int n  = 0;
  
  if(y < LMAX)
  {
    n += cells[(y+1)*GCOLS+x] ? 1 : 0; /* Bottom */
  }
  if(y > 0)
  {
    n +=  cells[(y-1)*GCOLS+x] ? 1 : 0; /* Top */
  }

  if(x < CMAX)
  {
    n +=  cells[y*GCOLS+(x+1)] ? 1 : 0; /* Right */
    if(y > 0)
    {
      n += cells[(y-1)*GCOLS+(x+1)] ? 1 : 0; /* Top right */
     }
    if(y < LMAX)
     {
       n +=  cells[(y+1)*GCOLS+(x+1)] ? 1 : 0;/* Bottom right */
     }
  }
  if(x >  0)
  {
    n += cells[y*GCOLS+(x-1)] ? 1 : 0; /* Left */
    if(y > 0)
    {
      n += cells[(y-1)*GCOLS+(x-1)] ? 1 : 0; /* Top left */
    }
    if(y < LMAX)
    {
      n += cells[(y+1)*GCOLS+(x-1)] ? 1 : 0; /* Bottom left */
    }
  } 


  return n;
}


void run_splash(){

  char str_title[] = "Game Of Life";
  char str_press[] = "Press a touch to continue";
  
  print_color(stdscr, LINES / 2, (COLS - strlen(str_title)) / 2, WHITE, str_title);
  print_color(stdscr, LINES - 1.0, 0, BLUE, str_press);
  refresh();
  getch();
  erase();
}


void run_game(){ 
  
  char cmds[] = "k : Quit            z,q,s,d : Move            Enter : Run";
  char in;

  GLINES = (int)((LINES*9)/10);
  GCOLS = (int)((COLS*9)/10);
  LMAX = GLINES - 1;
  CMAX = GCOLS  - 1;
  
  cells = malloc(GLINES*GCOLS*sizeof(char));
  memset(cells, 0, GLINES*GCOLS*sizeof(char));

  nextcells = malloc(GLINES*GCOLS*sizeof(char));
  memset(nextcells, 0, GLINES*GCOLS*sizeof(char));

  mvprintw(LINES - 5, (int)(COLS/20), "%s", cmds);
  game = subwin(stdscr, GLINES , GCOLS , (int)(LINES/40) , (int)(COLS/20));
  box(game,0,0);
  wmove(game, GLINES / 2, GCOLS / 2);
  refresh();
  wrefresh(game);

  do {
    in = getch();
  }
  while(input_mode(in));
}

void destroy(){

  delwin(game);
  
  free(cells);
  free(nextcells);  

}

