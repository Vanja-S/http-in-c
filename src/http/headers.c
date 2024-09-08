// Copyright 2024 Vanja S.

#include <string.h>

#include "headers.h"

int header_exists(const char* header, char* headers_seg) {
  if (strstr(header, headers_seg) != NULL) {
    return 1;
  }
  return 0;
}
