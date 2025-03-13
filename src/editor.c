#include "../include/nook.h"
#include <ncurses.h>
#include <stdio.h>

int bootNook(const char* filePath) 
{
  // ---------------------------------- // 

  FILE* nookFile;
  char* nookBuff; 

  // ---------------------------------- //

  nookBuff = (char*)INIT_NOOK_BUFF();

  if(strlen(filePath) > 0) {
    nookFile = loadFileToMem(filePath);
  }

  startNook();
  return 0;
}

WINDOW *create_newwin(int height, int width, int starty, int startx);
void destroy_win(WINDOW *local_win);

void startNook() 
{
  WINDOW *win;
  int row,col;
  int ch;
  int startx, starty, width, height;

  initscr();
  keypad(stdscr, TRUE);
  noecho();
  getmaxyx(stdscr, row, col);
  printw("5 hours of coding this t-t");
  while((ch = getch()) != KEY_F(1))
	{	
    switch(ch) 
    {
      case KEY_ENTER:
				destroy_win(win);
				win = create_newwin(height, width, starty,--startx);
				break; 
    }
  }
  refresh();
	getch();
	endwin();
}

WINDOW *create_newwin(int height, int width, int starty, int startx)
{	WINDOW *local_win;

	local_win = newwin(height, width, starty, startx);
	box(local_win, 0 , 0);		/* 0, 0 gives default characters 
					 * for the vertical and horizontal
					 * lines			*/
	wrefresh(local_win);		/* Show that box 		*/

	return local_win;
}

void destroy_win(WINDOW *local_win)
{	
	/* box(local_win, ' ', ' '); : This won't produce the desired
	 * result of erasing the window. It will leave it's four corners 
	 * and so an ugly remnant of window. 
	 */
	wborder(local_win, ' ', ' ', ' ',' ',' ',' ',' ',' ');
	/* The parameters taken are 
	 * 1. win: the window on which to operate
	 * 2. ls: character to be used for the left side of the window 
	 * 3. rs: character to be used for the right side of the window 
	 * 4. ts: character to be used for the top side of the window 
	 * 5. bs: character to be used for the bottom side of the window 
	 * 6. tl: character to be used for the top left corner of the window 
	 * 7. tr: character to be used for the top right corner of the window 
	 * 8. bl: character to be used for the bottom left corner of the window 
	 * 9. br: character to be used for the bottom right corner of the window
	 */
	wrefresh(local_win);
	delwin(local_win);
}

FILE* loadFileToMem(const char *fileToLoad)
{
  FILE* fp;
  fp = fopen(fileToLoad, "w+");
  if (fp == NULL)
    ERROR_RETURN("File could not be loaded nor created", NULL);
  return fp;
}

