#include <stdlib.h>

#ifndef DA_GROWTH_FACTOR
#define DA_GROWTH_FACTOR 1.5
#endif

#define CONCAT(A, B) A ## B
#define CONCAT3(A, B, C) A ## B ## C

#define GENERATE_DA_PRO(NAME) \
struct CONCAT(da_, NAME) \
{ \
  NAME *values; \
  int len; \
  int capacity; \
}; \
 \
struct CONCAT(da_, NAME) *CONCAT3(da_, NAME, _append)(struct CONCAT(da_, NAME) *da, NAME a); \

#define GENERATE_DA_IMP(NAME) \
struct CONCAT(da_, NAME) *CONCAT3(da_, NAME, _append)(struct CONCAT(da_, NAME) *da, NAME a) \
{ \
  if(da->values == NULL) \
  { \
    da->len = 1; \
    da->capacity = 1; \
    da->values = (NAME *)malloc(sizeof(NAME)); \
    da->values[0] = a; \
  } \
  else \
  { \
    if(da->len == da->capacity) \
    { \
      int new_size = (int)( da->capacity * DA_GROWTH_FACTOR ); \
      if(new_size == da->capacity) new_size ++; \
       \
      NAME *new_buffer = (NAME *)malloc(sizeof(NAME) * new_size); \
      for(int i = 0; i < da->len; i++) \
      { \
        new_buffer[i] = da->values[i]; \
      } \
      free(da->values); \
      da->values = new_buffer; \
      da->capacity = new_size; \
    } \
    da->values[da->len++] = a; \
  } \
  return da; \
} \
