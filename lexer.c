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
  lexer_t lexer = {
    .file = f,
    .position = 0
  };
  return true;
}

int consume_char(lexer_t *lexer)
{
  int c = fgetc(lexer->file);
  return c;
}

int peek_char(lexer_t *lexer)
{
  int c = fgetc(lexer->file);
  fseek(lexer->file, -1, SEEK_CUR);
  return c;
}


