#include <string.h>
#include <ncurses.h>
#include "utils.h"
#include "Gameoflife.h"

static WINDOW * gameWin = NULL;  /* Window for game grid */
static WINDOW * borderWin = NULL; /* Window for border */

static unsigned char * cur_tab = NULL;
static unsigned char * tmp_tab = NULL;

static unsigned char * t1 = NULL; /* Tab 1 */
static unsigned char * t2 = NULL; /* Tab 2 */

static int t_LINES = 0; /* Number of lines used for game grid */
static int t_COLS  = 0; /* Number of cols  used for game grid */ 

static int x,y,seed = 0; /* (x,y) and number of cycles */



void 
run_splash(){
  char str_title[] = "Game Of Life";
  char str_press[] = "Press a key to continue";

  print_color(stdscr, LINES / 2, (COLS - strlen(str_title)) / 2, WHITE , str_title);
  print_color(stdscr, LINES - 1.0, 0, BLUE, str_press);
  refresh();
  getch();
  erase();

}


void
run_game(){
  char in;

  t_LINES = (int) (LINES * 95 / 100);
  t_COLS  = (int) (COLS  * 95 / 100);

  /* Create tabs */
  t1 = malloc(t_LINES*t_COLS*sizeof(unsigned char *));
  t2 = malloc(t_LINES*t_COLS*sizeof(unsigned char *));
  memset(t1, 0, t_LINES*t_COLS*sizeof(unsigned char *));
  memset(t2, 0, t_LINES*t_COLS*sizeof(unsigned char *));

  cur_tab = t1;
  tmp_tab = t2;

  /* Set the command line */
  print_color(stdscr,LINES - 1.0, COLS - t_COLS, BLUE, "ZQSD : Move    SPACE : (De)Activate    ENTER : Run    I : Restart     K : Quit");
  mvprintw(LINES - 1.0, COLS + 80 - t_COLS, " Seed : %d          ", seed);

  /* Create windows */
  borderWin = newwin( t_LINES + 2, t_COLS + 2, 0 , (COLS - t_COLS) / 2);
  gameWin = newwin( t_LINES, t_COLS, 1, ((COLS - t_COLS) /2) + 1);
  box(borderWin, 0, 0);

  /* Move the cursor in the game window */
  wmove(gameWin, 0, 0);

  /* Refresh windows*/
  refresh();
  wrefresh(borderWin);
  wrefresh(gameWin);
  
  /* Handle input */
  do {
    in = getch();
  }
  while(input_mode(in));




}


int 
input_mode(char ch){
  getyx(gameWin, y, x);
  switch(ch){

    case 'd': /* Right */
      x= modulo(x+1,t_COLS); 
      break;
    case 'q': /* Left */
      x= modulo(x-1 , t_COLS);
      break;
    case 's': /* Down */    
      y = modulo(y+1, t_LINES);
      break;
    case 'z': /* Up */
      y= modulo(y-1, t_LINES);
      break;

    case ' ': /* Activate a cell */
      if (cur_tab[(y)*t_COLS+(x)] == 1){ /* Row-major order storage method */ 
        cur_tab[(y)*t_COLS+(x)] = 0;
        mvwaddch(gameWin, y, x, ' ');
      }
      else {
        cur_tab[(y)*t_COLS+(x)] = 1; 
        mvwaddch(gameWin, y, x, 'O');
      }
      break;

    case '\n': /* Run */
      play_mode();
      break;

    case 'i': /* Restart */
      memset(t1, 0, t_LINES*t_COLS*sizeof(unsigned char *));
      memset(t2, 0, t_LINES*t_COLS*sizeof(unsigned char *));
      werase(gameWin);
      seed = 0;
      mvprintw(LINES - 1.0, COLS + 80 - t_COLS, " Seed : %d          ", seed);
      break;

    case 'k':
      return 0;
  }

  mvprintw(0,0, "%d   ", x);
  mvprintw(1,0, "%d   ", y);
  mvprintw(2,0, "%d   ", t_COLS);
  mvprintw(3,0, "%d   ", t_LINES);

  wmove(gameWin, y, x);
  
  /* Seems to be useless but because it's warm */
  refresh(); 
  wrefresh(gameWin);

  return 1;

}

void
play_mode()
{
	unsigned int life;

	/* Checking the 8 cases around */
	for (x = 0; x < t_COLS; x++)
	{
		for (y = 0; y < t_LINES; y++)
		{
		  life = 0;
		  if ((y + 1) < t_LINES)
		  {
			  if (x && cur_tab[(y+1)*t_COLS+(x-1)] == 1)
				life++;
			  if (cur_tab[(y+1)*t_COLS+x] == 1)
				life++;
			  if ((x + 1) < t_COLS && cur_tab[(y+1)*t_COLS+(x+1)] == 1)
				life++;
	          }
		  if (x)
	          {
			  if (cur_tab[y*t_COLS+(x-1)] == 1)
				life++;
			  if (y && cur_tab[(y-1)*t_COLS+(x-1)] == 1)
				life++;
	   	  }
		  if (y && cur_tab[(y-1)*t_COLS+x] == 1)
			life++;
		  if (y && (x + 1) < t_COLS  && cur_tab[(y-1)*t_COLS+(x+1)] == 1)
			life++;
		  if ((x + 1) < t_COLS && cur_tab[y*t_COLS+(x+1)] == 1)
			life++;
		  if (cur_tab[y*t_COLS+x] == 1)
			tmp_tab[y*t_COLS+x] = (life != 2 && life != 3) ? 0 : 1;
		  else
			tmp_tab[y*t_COLS+x] = (life == 3) ? 1 : 0;
		  mvwaddch(gameWin, y, x, tmp_tab[y*t_COLS+x] ? '0' : ' ');
		}
	}
        

        /* Switch tabs */
	if (cur_tab == t1)
	{
	  cur_tab = t2;
	  tmp_tab = t1;
	}
        else
	{
	  cur_tab = t1;
	  tmp_tab = t2;
	}

        /* Increase the number of cycles and move the cursor to (0,0) */
        mvprintw(LINES - 1.0, COLS + 80 - t_COLS, " Seed : %d          ", ++seed);
        wmove(gameWin, 0, 0);

        /* Seems to be useless but for the beauty of it */
	refresh();
        wrefresh(gameWin);
}

void 
destroy(){
  delwin(gameWin);
  delwin(borderWin);
  free(t1);
  free(t2);
}
