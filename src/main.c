#include "../include/nook.h"

#define EXIT_SUCCESS 0
#define EXIT_ERROR   1

int main(int argc, char *argv[])
{
  // File provided
  if(argc == 2)
    if(bootNook(argv[1]) == 1) 
      return EXIT_ERROR;

  // File not provided
  if(argc < 2)
    if(bootNook("") == 1)
      return EXIT_ERROR;

  return EXIT_SUCCESS;
}
