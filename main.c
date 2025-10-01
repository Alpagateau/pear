#include <string.h>
#include <stdio.h>
#include "pear.h"

int main(int argc, char **argv)
{
  compile_flags_t cf = {0};
  if(argc == 1)
  {
    printf("Pear Programming Language %s\n", VERSION);
    printf("Usage :\n");
    printf("  pear <files> -[v|c|o]\n");
    return 0;
  }

  //Read the compile flags
  for(int i = 1; i < argc; i++)
  {
    if(strcmp(argv[i], "-v") == 0)
      cf.verbose = true;
    if(strcmp(argv[i], "-c") == 0)
      cf.out_c = true;
  }
  return 0;
}
