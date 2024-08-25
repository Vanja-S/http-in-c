// Copyright 2024 Vanja S.

#include <stdlib.h>
#include "lib.h"

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


