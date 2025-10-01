#pragma once
#include <stdlib.h>
#include <stdbool.h>

#define VERSION "0.0.1"
#define STRING_SIZE 255

typedef struct {
  bool verbose;
  bool out_c;
}compile_flags_t;

typedef struct string_ll string_ll_t;

struct string_ll{ 
  char value[STRING_SIZE];
  string_ll_t *next;
};

int ll_append(string_ll_t *root, char* val)
{
  if(root->next != NULL)
    ll_append(root->next, val);
  else 
  {
    root->next = (string_ll_t*)malloc(sizeof(string_ll_t));
    strcpy(root->next->value, val);
  }
  return 0;
}

int ll_pop(string_ll_t *root, char* out)
{
  if(root->next->next == NULL)
  {
    if(out != NULL)
      strcpy(out, root->next->value);
    *(root->next) = (string_ll_t){0};
    free((root->next));
    root->next = NULL;
  }
  return 0;
}
