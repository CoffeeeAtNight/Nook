#ifndef NOOK_H
#define NOOK_H
#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INIT_BUFF_SIZE 4096
#define WIDTH 80
#define HEIGHT 25
#define ERROR_RETURN(msg, ret_val)                                             \
  do {                                                                         \
    fprintf(stderr,                                                            \
            "Error: %s\n"                                                      \
            "File: %s, Line: %d\n",                                            \
            msg, __FILE__, __LINE__);                                          \
    return ret_val;                                                            \
  } while (0)

int bootNook(const char *filePath);
void startNook(char *nookBuff);
size_t loadFileToMem(const char *fileToLoad, char **nookBuff);
static inline char *INIT_NOOK_BUFF(size_t allocSize);
void cleanUp(char *nookBuff);
void storeBuffToFile(char *nookBuff, const char *filePath);

#endif // !NOOK_H
