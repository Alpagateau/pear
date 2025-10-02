#pragma once
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

int ll_append(string_ll_t *root, char* val)
{
  if(root->next != NULL)
    ll_append(root->next, val);
  else 
  {
    if(root->is_written != 0)
    {
      root->next = (string_ll_t*)malloc(sizeof(string_ll_t));
      if(root->next == NULL)
      {
        return 1;
      }
      root->next->is_written = 1;
      strcpy(root->next->value, val);
    }
    else 
    {
      strcpy(root->value, val);
      root->is_written = 1; 
    }
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

int ll_size(string_ll_t *root)
{
  if(root->next == NULL)
    return 1;
  else 
    return 1 + ll_size(root->next);
}

int ll_cpyat(string_ll_t *root, unsigned int index, char* buffer)
{
  if(index == 0)
    strcpy(buffer, root->value);
  else 
  {
    if(root->next == NULL)
      return 1;
    else 
      return ll_cpyat(root->next, index-1, buffer);
  }
  return 0;
}

char* ll_getat(string_ll_t *root, unsigned int index, int* size_out)
{
  if(index == 0)
  {
    *size_out = STRING_SIZE;
    return root->value;
  }
  else 
  {
    if(root->next == NULL)
    {
      *size_out = 0;
      return NULL;
    }
    else { 
      return ll_getat(root->next, index-1, size_out);
    }
  }
  return 0;
}

bool is_pear_file(char* filename){
  int len = strlen(filename);
  if(len < 4)
    return false;
  char* ext = (filename + len - 5);
  if(strcmp(ext, ".pear") == 0)
    return true;
  else 
    return false;
}
