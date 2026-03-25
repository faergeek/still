#ifndef ARRAY_H
#define ARRAY_H

#include <stddef.h>
#include <stdlib.h>

struct array_header {
  size_t capacity;
  size_t length;
  char contents[];
};

size_t array_length(void *array);

void *array_grow_if_needed(void *array, size_t element_size,
                           size_t new_capacity);

#define array_push(array, element)                                       \
  do {                                                                   \
    (array) = array_grow_if_needed((array), sizeof(*array),              \
                                   array_length(array) + 1);             \
    (array)[((struct array_header *)(array) - 1)->length++] = (element); \
  } while (0)

#define array_free(array)                       \
  do {                                          \
    if (array) {                                \
      free((struct array_header *)(array) - 1); \
      (array) = NULL;                           \
    }                                           \
  } while (0)

#endif
