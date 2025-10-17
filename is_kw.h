#include "lexer.h"
#define STR(X) #X
#define GEN_IS_KW(KEYWORD, N) \
bool CONCAT(is_kw_, KEYWORD)(lexer_t *lexer){ \
  char buffer[N] = {}; \
  peek_str(lexer, buffer, N); \
  return (strcmp(buffer, STR(KEYWORD)) == 0); \
} \
lexem_t CONCAT(new_, KEYWORD)(lexer_t *lexer) \
{ \
  for(int i = 0; i < N; i++){consume_char(lexer);} \
  return (lexem_t){ \
    .type = CONCAT(kw_, KEYWORD), \
    .line_num = lexer->line_number, \
    .char_num = lexer->char_number, \
    .debut = lexer->stream_position - N, \
    .fin = lexer->stream_position \
  }; \
} \
