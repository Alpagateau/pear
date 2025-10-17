#include <string.h>
#include <stdio.h>
#include "pear.h"
#include "lexer.h"

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
 
  struct da_string_t args = {0};

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
      struct string a;
      strcpy(a.value, argv[i]);
      da_string_t_append(&args, a);
    }
  }

  int size = args.len;
  char buf[STRING_SIZE] = {0};
  printf("Read %d arguments\n", size);
  for(int i = 0; i < size; i++)
  {
    strcpy(buf, args.values[i].value);
    bool a = is_pear_file(buf);
    if(cf.verbose){
      printf("Parsed arg %d : %s | Is a pear file ? %d\n", i, buf, a);
    }
    if(a)
    {
      struct da_lexem_t l = {0};
      lex_file(buf, &l, cf.verbose);
      for(int i = 0; i < l.len; i++)
      {
        print_lexem(l.values[i]);
      }
    }
  }
  return 0;
}
