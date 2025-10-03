#pragma once
#include "pear.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct lexem lexem_t;

enum lexem_types 
{
  kw_fonction,
  kw_retourner,
  kw_debut,
  kw_fin,
  kw_si ,
  kw_alors,
  kw_sinon,
  kw_tantque,
  kw_faire,
  kw_pour,
  kw_de,
  kw_a,
  kw_répéter,
  kw_fois,
  //types
  kw_entier,
  kw_tableau,
  kw_long,
  //literals
  lit_num, 
  lit_identifier,
  //operators
  op_binary,
  op_unary,
  op_expr,
  //separatos 
  sep_semicol,
  sep_coma,
  sep_ws,
  sep_openbra,
  sep_closebra,
  sep_opensq,
  sep_closeq
};

struct lexem
{
  enum lexem_types type;
  int line_num;
  int char_num;
  union var {
    int int_value;
    char op_type;
    char identifier[STRING_SIZE];
  };
};

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

bool lex_file(char* filepath, bool verbose);


