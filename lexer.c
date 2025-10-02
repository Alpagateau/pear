#include "lexer.h"

bool lex_file(char* filepath, bool verbose)
{
  FILE* f = fopen(filepath, "r");
  if(f == NULL)
  {
    if(verbose)
      printf("couldnt open file %s. skipping it\n", filepath);
    return false;
  }
  return true;
}
