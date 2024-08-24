// Copyright 2024 Vanja S.

#ifndef SRC_HTTP_ERROR_H_
#define SRC_HTTP_ERROR_H_

#include <stdint.h>

struct HTTPError {
  uint16_t statusCode;
  char statusMessage[];
};

HTTPError* create_error(uint16_t statusCode, char statusMessage[]);

char* error_to_string(HTTPError* httpError);

#endif  // SRC_HTTP_ERROR_H_

