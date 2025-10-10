#include "lexer.h"

bool lex_file(char* filepath, lexem_ll_t *lexems, bool verbose)
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
    .stream_position = 0,
    .line_number = 0,
    .char_number = 0
  };
  if(verbose)
  {
    printf("Lexing file : %s\n", filepath);
    printf("Is first lexem a space ? %d\n", read_whitespaces(&lexer));
  }
   
  return true;
}

int consume_char(lexer_t *lexer)
{
  int c = fgetc(lexer->file);
  if(c == '\n')
  {
    lexer->char_number = 0;
    lexer->line_number++;
  }
  lexer->stream_position++;
  return c;
}

int peek_char(lexer_t *lexer)
{
  int c;
  c = fgetc(lexer->file);
  ungetc(c, lexer->file);
  return c;
}

int ll_lexem_append(lexem_ll_t *root, lexem_t val)
{
  if(root->next != NULL)
    ll_lexem_append(root->next, val);
  else 
  {
    if(root->is_written != 0)
    {
      root->next = (lexem_ll_t*)malloc(sizeof(lexem_ll_t));
      if(root->next == NULL)
      {
        return 1;
      }
      root->next->is_written = 1;
      root->next->lexem = val;
    }
    else 
    {
      root->lexem = val;
      root->is_written = 1; 
    }
  }
  return 0;
}

int ll_lexem_pop(lexem_ll_t *root, lexem_t *out)
{
  if(root->next->next == NULL)
  {
    if((void*)out != NULL)
      *out = (root->next->lexem);
    *(root->next) = (lexem_ll_t){0};
    free((root->next));
    root->next = NULL;
  }
  return 0;
}

int ll_lexem_size(lexem_ll_t *root)
{
  if(root->next == NULL)
    return 1;
  else 
    return 1 + ll_lexem_size(root->next);
}

lexem_t ll_lexem_getat(lexem_ll_t *root, unsigned int index)
{
  if(index == 0)
  {
    //*size_out = STRING_SIZE;
    return (root->lexem);
  }
  else 
  {
    if(root->next == NULL)
    {
      return (lexem_t){0};
    }
    else { 
      return ll_lexem_getat(root->next, index-1);
    }
  }
  return (lexem_t){0};
}

bool read_function(lexer_t *lexer)
{
  return true;
}



bool read_whitespaces(lexer_t *lexer)
{
  bool done = false;
  int count = 0;
  do 
  {
    done = read_whitespace(lexer);
    if(done)
      count++;
  }
  while(done);
  return (count > 0);
}

bool read_whitespace(lexer_t *lexer)
{
  int peeked = peek_char(lexer);
  if(peeked > 255)
    return false;
  
  char c = (char)peeked;
  static char whitespaces[] = {'\n', ' ', '\t', '\r'};

  for(char i = 0; i < 4; i++)
  {
    if(c == whitespaces[i])
    {
      consume_char(lexer);
      return true;
    }
  }
}

bool read_identifier(lexer_t *lexer)
{
  return true;
}
