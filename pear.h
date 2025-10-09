#ifndef PEAR_H
#define PEAR_H
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define VERSION "0.0.1"
#define STRING_SIZE 255

typedef struct {
  bool verbose;
  bool out_c;
}compile_flags_t;

typedef struct string_ll string_ll_t;

struct string_ll{ 
  char value[STRING_SIZE];
  bool is_written;
  string_ll_t *next;
};

int ll_string_append(string_ll_t *root, char *val);

int ll_string_pop(string_ll_t *root, char* out);

int ll_string_size(string_ll_t *root);

int ll_string_cpyat(string_ll_t *root, unsigned int index, char* buffer);


char* ll_string_getat(string_ll_t *root, unsigned int index, int* size_out);

bool is_pear_file(char* filename);

#endif
