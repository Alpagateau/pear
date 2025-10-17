#include "lexer.h"
#include "is_kw.h"
#include "pear.h"
#include <stdio.h>

GENERATE_DA_IMP(lexem_t)

GEN_IS_KW(a, 1)
GEN_IS_KW(si, 2)
GEN_IS_KW(de, 2)
GEN_IS_KW(fin, 3)
GEN_IS_KW(pour, 4)
GEN_IS_KW(fois, 4)
GEN_IS_KW(long, 4)
GEN_IS_KW(debut, 5)
GEN_IS_KW(alors, 5)
GEN_IS_KW(sinon, 5)
GEN_IS_KW(faire, 5)
GEN_IS_KW(entier, 6)
GEN_IS_KW(tantque, 7)
GEN_IS_KW(repeter, 7)
GEN_IS_KW(tableau, 7)
GEN_IS_KW(fonction, 8)
GEN_IS_KW(retourner, 9)

static char *lexem_name(lexem_t l){
  switch(l.type)
  {
    case kw_fonction : return "fonction" ;
    case kw_retourner: return "retourner";
    case kw_debut    : return "debut"    ;
    case kw_fin      : return "fin"      ;
    case kw_si       : return "si"       ;
    case kw_alors    : return "alors"    ;
    case kw_sinon    : return "sinon"    ;
    case kw_tantque  : return "tantque"  ;
    case kw_faire    : return "faire"    ;
    default          : return ""         ;
  }
}

bool lex_file(char *filepath, struct da_lexem_t *lexems, bool verbose) {
  FILE *f = fopen(filepath, "r");
  if (f == NULL) {
    if (verbose)
      printf("couldnt open file %s. skipping it\n", filepath);
    return false;
  }
  lexer_t lexer = {
      .file = f, .stream_position = 0, .line_number = 0, .char_number = 0};

  printf("Lexing file : %s\n", filepath);
  while (!feof(lexer.file)) {

    if (is_kw_fonction(&lexer)) {
      da_lexem_t_append(lexems, new_fonction(&lexer));
      continue;
    }

    if (is_kw_retourner(&lexer)) {
      da_lexem_t_append(lexems, new_retourner(&lexer));
      continue;
    }

    if (is_kw_debut(&lexer)) {
      da_lexem_t_append(lexems, new_debut(&lexer));
      continue;
    }

    if (is_kw_fin(&lexer)) {
      da_lexem_t_append(lexems, new_fin(&lexer));
      continue;
    }

    if (is_kw_si(&lexer)) {
      da_lexem_t_append(lexems, new_si(&lexer));
      continue;
    }

    if (is_kw_alors(&lexer)) {
      da_lexem_t_append(lexems, new_alors(&lexer));
      continue;
    }

    if (is_kw_sinon(&lexer)) {
      da_lexem_t_append(lexems, new_sinon(&lexer));
      continue;
    }

    if (is_kw_tantque(&lexer)) {
      da_lexem_t_append(lexems, new_tantque(&lexer));
      continue;
    }

    if (is_kw_faire(&lexer)) {
      da_lexem_t_append(lexems, new_faire(&lexer));
      continue;
    }

    if (is_kw_pour(&lexer)) {
      da_lexem_t_append(lexems, new_pour(&lexer));
      continue;
    }

    if (is_kw_de(&lexer)) {
      da_lexem_t_append(lexems, new_de(&lexer));
      continue;
    }

    if (is_kw_a(&lexer)) {
      da_lexem_t_append(lexems, new_a(&lexer));
      continue;
    }

    if (is_kw_repeter(&lexer)) {
      da_lexem_t_append(lexems, new_repeter(&lexer));
      continue;
    }

    if (is_kw_fois(&lexer)) {
      da_lexem_t_append(lexems, new_fois(&lexer));
      continue;
    }

    // types
    if (is_kw_entier(&lexer)) {
      da_lexem_t_append(lexems, new_entier(&lexer));
      continue;
    }

    if (is_kw_tableau(&lexer)) {
      da_lexem_t_append(lexems, new_tableau(&lexer));
      continue;
    }

    if (is_kw_long(&lexer)) {
      da_lexem_t_append(lexems, new_long(&lexer));
      continue;
    }
    consume_char(&lexer);
  }
  return true;
}

int consume_char(lexer_t *lexer) {
  int c = fgetc(lexer->file);
  if (c == '\n') {
    lexer->char_number = 0;
    lexer->line_number++;
  }
  lexer->stream_position++;
  return c;
}

int peek_char(lexer_t *lexer) {
  int c;
  c = fgetc(lexer->file);
  ungetc(c, lexer->file);
  return c;
}

void peek_str(lexer_t *lexer, char buffer[], int len) {
  for (int i = 0; i < len; i++) {
    int c = fgetc(lexer->file);
    buffer[i] = (c <= 255) ? (unsigned char)c : 0;
  }
  for (int i = len - 1; i >= 0; i--) {
    ungetc(buffer[i], lexer->file);
  }
}

void print_lexem(lexem_t l)
{
  printf("LEXEM : %s at (%d, %d)\n", lexem_name(l), l.line_num, l.char_num);
}
