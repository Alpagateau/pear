#include "lexer.h"
#include "pear.h"
#include <stdio.h>

GENERATE_DA_IMP(lexem_t)

bool lex_file(char* filepath, da_lexem_t *lexems, bool verbose)
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

  printf("Lexing file : %s\n", filepath);
  while(!feof(lexer.file) ){
    lexem_t l = read_whitespaces(&lexer);
    if(l.type == db_null)
      l = read_identifier(&lexer); 
    if(l.type == db_null)
      l =  read_parenthesis(&lexer);
    if(l.type != db_null)
      print_lexem(&l);
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

lexem_t read_function(lexer_t *lexer)
{
  lexem_t lex = {};
  
  return lex;
}

lexem_t read_whitespaces(lexer_t *lexer)
{
  bool done = false;
  int count = -1;
  do 
  {
    count++;
    done = read_whitespace(lexer);
  }
  while(done);
  lexem_t lex = (lexem_t){
    .type = sep_ws, 
    .char_num = lexer->char_number, 
    .line_num = lexer->line_number,
    .identifier = {0}
  };
  return (count > 0) ? lex : (lexem_t){.type = db_null};
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
  return false;
}

lexem_t read_identifier(lexer_t *lexer)
{
  lexem_t lex = {0};
  lex.char_num = lexer->char_number;
  lex.line_num = lexer->line_number;
  char c1 = (char)peek_char(lexer);
  if(!is_alpha(c1))
  {
    lex.type = db_null;
    printf("Is no alpha : %c\n", c1);
  }
  else 
  {
    char ident[STRING_SIZE] = {0};
    int len = 0;
    char c = consume_char(lexer);
    while(is_alphanum(c))
    {
      ident[len] = c;
      len++;
      c = consume_char(lexer);
    }

    lex.type = lit_ident;
    strcpy(lex.identifier, ident);
  }
  return lex;
}

bool is_alpha(char c)
{
  return ( c >= 'A') && ( c <= 'z') && ( c <= 'Z' || c >= 'a' );
}

bool is_num(char c)
{
  return (c >= '0') && (c <= '9');
}

bool is_alphanum(char c)
{
  return is_alpha(c) || is_num(c) || (c == '_');
}

void print_lexem(lexem_t *lexem)
{
  printf("< lexem #%d : %d; %d >\n", (int)lexem->type, lexem->line_num, lexem->char_num);
}

lexem_t read_parenthesis(lexer_t *lexer)
{
  lexem_t lex = {0};
  lex.char_num = lexer->char_number;
  lex.line_num = lexer->line_number;
  char c = peek_char(lexer);
  switch(c)
  {
    case '(':
      consume_char(lexer);
      lex.type = sep_openpar;
      break;
    case ')':
      consume_char(lexer);
      lex.type = sep_closepar;
      break;
    case '{':
      consume_char(lexer);
      lex.type = sep_openbra;
      break;
    case '}':
      consume_char(lexer);
      lex.type = sep_closebra;
      break;
    case '[':
      consume_char(lexer);
      lex.type = sep_opensq;
      break;
    case ']':
      consume_char(lexer);
      lex.type = sep_closesq;
      break;
    default: 
      lex.type = db_null;
      break;
  }
  return lex;
}
