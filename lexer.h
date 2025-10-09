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
  db_null     ,
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
  kw_répéter  ,
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
  sep_closeq
};

struct lexem
{
  enum lexem_types type;
  int line_num;
  int char_num;
  union {
    int int_value;
    char op_type;
    char identifier[STRING_SIZE];
  };
};

typedef struct lexem_ll lexem_ll_t;
struct lexem_ll
{
  lexem_t lexem;
  int is_written;
  lexem_ll_t *next; 
};

int ll_lexem_append(lexem_ll_t *root, lexem_t value);
int ll_lexem_pop(lexem_ll_t *root, lexem_t *value);
lexem_t ll_lexem_getat(lexem_ll_t *root, unsigned int index);


typedef struct lexer lexer_t;
struct lexer 
{
  FILE* file;
  int position;
};

//Consumes a character from the file stream
//  -> returns the char read (0-255)
//  -> returns 257 if eof
int consume_char(lexer_t *lexer);
int peek_char(lexer_t *lexer);
bool lex_file(char* filepath, lexem_ll_t *lexems, bool verbose);
bool read_function(lexer_t *lexer);
bool read_whitespace(lexer_t *lexer);
bool read_identifier(lexer_t *lexer);

#endif
