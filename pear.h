#ifndef PEAR_H
#define PEAR_H
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "dynamic_array.h"
#define VERSION "0.0.1"
#define STRING_SIZE 255

typedef struct {
  bool verbose;
  bool out_c;
}compile_flags_t;

typedef struct string string_t;

struct string{ 
  char value[STRING_SIZE];
};

GENERATE_DA_PRO(string_t)

bool is_pear_file(char* filename);

#endif
