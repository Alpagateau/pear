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
    .position = 0
  };
  if(verbose)
  {
    printf("Lexing file : %s\n", filepath);
    printf("Is first lexem a space ? %d\n", read_whitespace(&lexer));
  }
   
  return true;
}

int consume_char(lexer_t *lexer)
{
  int c = getc(lexer->file);
  fseek(lexer->file, 1, SEEK_CUR);
  return c;
}

int peek_char(lexer_t *lexer)
{
  int c = fgetc(lexer->file);
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

bool read_whitespace(lexer_t *lexer)
{
  int peeked = peek_char(lexer);
  if(peeked > 255)
    return false;
  
  char c = (unsigned char)(peeked & 0xFF);
  bool any = false;
  bool many = false;
  do{
    switch(c)
    {
      case ' ':
      case '\n':
      case '\t':
      case '\v':
      case '\r':
        many = true;
        any = true;
        consume_char(lexer);
        c = (unsigned char)(peeked & 0xFF); 
        printf("Got a whitespace : %d\n", c);
        break;
      default: 
        many = false; 
        printf("Not a whitespace : %d\n", c);
        break;
    }
  }while(many);
  return any;
}

bool read_identifier(lexer_t *lexer)
{
  return true;
}
