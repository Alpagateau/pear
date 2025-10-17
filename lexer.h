#ifndef LEXER_H
#define LEXER_H
//Trying to keep every function as specific as possible 
//to make portability to other OS easier

#pragma once
#include "pear.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct lexem lexem_t;

enum lexem_types 
{
  db_null = 0 ,
  db_error    ,
  kw_fonction ,
  kw_retourner,
  kw_debut    ,
  kw_fin      ,
  kw_si       ,
  kw_alors    ,
  kw_sinon    ,
  kw_tantque  ,
  kw_faire    ,
  kw_pour     ,
  kw_de       ,
  kw_a        ,
  kw_repeter  ,
  kw_fois     ,
  //types
  kw_entier   ,
  kw_tableau  ,
  kw_long     ,
  //literals
  lit_num     , 
  lit_ident   ,
  //operators
  op_binary   ,
  op_unary    ,
  op_expr     ,
  //separatos 
  sep_semicol ,
  sep_coma    ,
  sep_ws      ,
  sep_openbra ,
  sep_closebra,
  sep_opensq  ,
  sep_closesq ,
  sep_openpar ,
  sep_closepar
};

struct lexem
{
  enum lexem_types type;
  int line_num;
  int char_num;
  int debut;
  int fin;
  union {
    int int_value;
    char op_type;
    char identifier[STRING_SIZE];
  };
};

GENERATE_DA_PRO(lexem_t)

typedef struct lexer lexer_t;
struct lexer 
{
  FILE* file;
  int stream_position;
  int line_number;
  int char_number;
};

//Consumes a character from the file stream
//  -> returns the char read (0-255)
//  -> returns 257 if eof
int consume_char(lexer_t *lexer);
int peek_char(lexer_t *lexer);
void peek_str(lexer_t *lexer, 
              char buffer[], 
              int len);
bool lex_file(
  char* filepath, 
  struct da_lexem_t *lexems, 
  bool verbose);

bool is_kw_return(lexer_t *lexer);
void print_lexem(lexem_t l);

#endif
