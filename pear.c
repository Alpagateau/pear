#include "pear.h"

GENERATE_DA_IMP(string_t)

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

