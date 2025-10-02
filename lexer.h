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
};

struct lexem
{
  enum lexem_types type;
  int line_num;
  int char_num;
  union var {
    int int_value;
    char identifier[STRING_SIZE];
  };
};

bool lex_file(char* filepath, bool verbose);
