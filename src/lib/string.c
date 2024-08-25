// Copyright 2024 Vanja S.

#include <string.h>
#include <stdlib.h>
#include "lib.h"

char* concat(const char *s1, const char *s2) {
    const size_t len1 = strlen(s1);
    const size_t len2 = strlen(s2);
    char *result = malloc(len1 + len2 + 1);  // +1 for the null-terminator
    memcpy(result, s1, len1);
    memcpy(result + len1, s2, len2 + 1);  // +1 to copy the null-terminator
    return result;
}

char* uint_to_string(unsigned n) {
  unsigned len = num_of_digits(n);
  char* str = malloc(sizeof(char) * len);
  int i = 0;

  while (n > 0) {
    str[i++] = n % 10 + '0';
    n /= 10;
  }

  str[i] = '\0';

  for (int j = 0, k = i - 1; j < k; j++, k--) {
        char temp = str[j];
        str[j] = str[k];
        str[k] = temp;
  }

  return str;
}


