#include "../include/nook.h"
#include <ncurses.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

static inline char *INIT_NOOK_BUFF(size_t allocSize) {
  if (allocSize == 0)
    return (char *)calloc(INIT_BUFF_SIZE, sizeof(char));
  return (char *)calloc(allocSize, sizeof(char));
}

int bootNook(const char *filePath) {
  // ---------------------------------- //

  char *nookBuff = NULL;

  // ---------------------------------- //

  printf("[D] Trying to read file into mem ... \n");
  if (strlen(filePath) > 0) {
    printf("Size of allocated buffer is: %zu \n",
           loadFileToMem(filePath, &nookBuff));
  }

  startNook(nookBuff, filePath);
  return 0;
}

void startNook(char *nookBuff, const char *filePath) {
  initscr();
  raw();
  keypad(stdscr, TRUE);

  int x = 0, y = 0;

  while (1) {
    move(y, x);
    int ch = getch();

    switch (ch) {
    case KEY_UP:
      if (y > 0)
        y--;
      break;
    case KEY_DOWN:
      if (y < HEIGHT - 1)
        y++;
      break;
    case KEY_LEFT:
      if (x > 0)
        x--;
      break;
    case KEY_RIGHT:
      if (x < WIDTH - 1)
        x++;
      break;
    case 27: // esc
      endwin();
      return;
    case '\n':
      y++;
      x = 0;
      break;
    case KEY_BACKSPACE:
      if (x > 0) {
        x--;
        nookBuff[y * WIDTH + x] = ' ';
      } else if (x == 0) {
        y--;
      }
      break;
    default:
      if (ch >= 32 && ch <= 126) {
        nookBuff[y * WIDTH + x] = ch;
        x++;
      }
    }
    clear();
    int len = strlen(nookBuff);
    int rows = (len + WIDTH - 1) / WIDTH;
    for (int i = 0; i < rows; i++) {
      mvprintw(i, 0, "%.*s", WIDTH, &nookBuff[i * WIDTH]);
    }
  }

  storeBuffToFile(nookBuff, filePath);

  cleanUp(nookBuff);
  endwin();
}

void storeBuffToFile(char *nookBuff, const char *filePath) {
  printf("Storing changes in file");
  FILE *fp;

  if ((fp = fopen(filePath, "w+")) == NULL) {
    printf("Error occurred while trying to store changes in file");
  }

  memcpy(filePath, nookBuff, sizeof(nookBuff));
}

size_t loadFileToMem(const char *fileToLoad, char **nookBuff) {
  printf("[D] Loading file into mem \n");
  FILE *fp;
  char ch;
  size_t size;

  if ((fp = fopen(fileToLoad, "r+")) == NULL)
    if ((fp = fopen(fileToLoad, "w+")) == NULL)
      ERROR_RETURN("Error occurred trying to read/create the file", 1);

  fseek(fp, 0, SEEK_END);
  size = ftell(fp);
  fseek(fp, 0, SEEK_SET);

  *nookBuff = INIT_NOOK_BUFF(size);

  size_t i = 0;
  while ((ch = fgetc(fp)) != EOF && i < size) {
    (*nookBuff)[i++] = ch;
  }
  (*nookBuff)[i] = '\0';

  fclose(fp);
  return size;
}

void cleanUp(char *nookBuff) {
  free(nookBuff);
  return;
}
