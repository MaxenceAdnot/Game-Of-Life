#include <string.h>
#include <ncurses.h>
#include "utils.h"
#include "Gameoflife.h"


static WINDOW *game      = NULL;
static char   *cells     = NULL;
static char   *nextcells = NULL;

static int     seeds  = 0;
static char cmds[] = "k : Quit            z,q,s,d : Move             Space : Activate            Enter : Run            Seeds: ";

static int     GLINES = 0;
static int     GCOLS  = 0;
static int     CMAX   = 0;
static int     LMAX   = 0;

int input_mode(char ch){
  int y,x;
  
  getyx(game, y, x);
  switch(ch){
    case 'd': /* Right */
      if((x=(x+1)%(GCOLS-1))==0)
        x = 1; 
      break;
    case 'q': /* Left */
      if((x=(x-1)%(GCOLS-1))==0)
         x=CMAX;
       break;
    case 's': /* Down */
      if((y=(y+1)%(GLINES-1))==0)
         y = 1;
       break;
    case 'z': /* Up */
      if((y=(y-1)%(GLINES-1))==0)
         y=LMAX;
       break;
    case ' ': /* Activate a cell */
      if (cells[(y-1)*CMAX+(x-1)] == 1){ /* Row-major order storage method */ 
        cells[(y-1)*CMAX+(x-1)] = 0;
         mvwaddch(game, y, x, ' ');
      }
      else {
        cells[(y-1)*CMAX+(x-1)] = 1; 
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
   
  memcpy(nextcells, cells, LMAX*CMAX*sizeof(char));  

  for (x = 1; x < GCOLS - 1; x++){
    for(y= 1 ; y < GLINES - 1 ; y++){
      n = nbAliveCells(y-1,x-1);
      if (n == 3){
        nextcells[(y-1)*CMAX+(x-1)] = 1; 
        mvwaddch(game, y, x, 'O');
      }   
      else if( n < 2 || n > 3){
	nextcells[(y-1)*CMAX+(x-1)] = 0;
	mvwaddch(game, y, x, ' ');
      }
    }
  }
  memcpy(cells, nextcells, LMAX*CMAX*sizeof(char));
  mvwprintw(stdscr,LINES - 5, (int)(COLS/20), "%s %d", cmds, ++seeds);
  box(game,0,0);
  wrefresh(game);

}


int nbAliveCells(int y, int x){
  
  int n  = 0;
  
  if(y < GLINES - 1 )
  {
    n += cells[(y+1)*CMAX+x] ? 1 : 0; /* Bottom */
  }
  if(y > 0)
  {
    n +=  cells[(y-1)*CMAX+x] ? 1 : 0; /* Top */
  }

  if(x < GCOLS - 1 )
  {
    n +=  cells[y*CMAX+(x+1)] ? 1 : 0; /* Right */
    if(y > 0)
    {
      n += cells[(y-1)*CMAX+(x+1)] ? 1 : 0; /* Top right */
     }
    if(y < GLINES - 1 )
     {
       n +=  cells[(y+1)*CMAX+(x+1)] ? 1 : 0;/* Bottom right */
     }
  }
  if(x >  0)
  {
    n += cells[y*CMAX+(x-1)] ? 1 : 0; /* Left */
    if(y > 0)
    {
      n += cells[(y-1)*CMAX+(x-1)] ? 1 : 0; /* Top left */
    }
    if(y < GLINES - 1)
    {
      n += cells[(y+1)*CMAX+(x-1)] ? 1 : 0; /* Bottom left */
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
  
  
  char in;

  GLINES = (int)((LINES*9)/10);
  GCOLS = (int)((COLS*9)/10);
  LMAX = GLINES - 2;
  CMAX = GCOLS  - 2;
  
  cells = malloc(LMAX*CMAX*sizeof(char));
  memset(cells, 0, LMAX*CMAX*sizeof(char));

  nextcells = malloc(LMAX*CMAX*sizeof(char));
  memset(nextcells, 0, LMAX*CMAX*sizeof(char));

  mvprintw(LINES - 5, (int)(COLS/20), "%s %d", cmds, seeds);
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

