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
 
  string_ll_t args = {0};

  //Read the compile flags
  for(int i = 1; i < argc; i++)
  {
    if(strcmp(argv[i], "-v") == 0)
    {
      cf.verbose = true;
    }
    else if(strcmp(argv[i], "-c") == 0)
    {
      cf.out_c = true;
    }
    else 
    {
      ll_append(&args, argv[i]);
    }
  }

  if(cf.verbose)
  {
    int size = ll_size(&args);
    char buf[STRING_SIZE] = {0};
    printf("Read %d arguments\n", size);
    for(int i = 0; i < size; i++)
    {
      ll_cpyat(&args, i, buf);
      printf("Parsed arg %d : %s | Is a pear file ? %d\n", i, buf, is_pear_file(buf));
    }
  }

  return 0;
}
