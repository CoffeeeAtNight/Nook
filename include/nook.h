#ifndef NOOK_H
#define NOOK_H
#include <stdio.h>
#include <ncurses.h>
#include <string.h>
#include <stdlib.h>

#define INIT_BUFF_SIZE 4096
#define INIT_NOOK_BUFF() malloc(INIT_BUFF_SIZE)
#define ERROR_RETURN(msg, ret_val)          \
  do {                                      \
    fprintf(stderr, "Error: %s\n"           \
                    "File: %s, Line: %d\n", \
            msg, __FILE__, __LINE__);       \
    return ret_val;                         \
  } while (0)


int bootNook(const char* filePath);
void startNook();
FILE* loadFileToMem(const char* fileToLoad);

#endif // !NOOK_H
