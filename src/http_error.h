// Copyright 2024 Vanja S.

#ifndef SRC_HTTP_ERROR_H_
#define SRC_HTTP_ERROR_H_

#include <stdint.h>

struct HTTPError {
  uint16_t status_code;
  char status_message[];
};

HTTPError* create_error(uint16_t status_code, char statusMessage[]);

char* error_to_string(HTTPError* http_error);

#endif  // SRC_HTTP_ERROR_H_

