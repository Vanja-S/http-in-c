// Copyright 2024 Vanja S.

#include <stdio.h>
#include <string.h>

#include "http.h"

/*
 * parse_request_line takes in the first line of an HTTP request
 * and returns 0 if everything is okay, or a HTTP error code if
 * something is wrong with the request.
 */
int parse_request_line(char * rl) {
  int i = 0;
  // Parse the method
  char method_buff[8];
  memset(method_buff, 0, sizeof(char) * 8);
  for (; *(rl+i) != ' '; i++) {
    if (i > 6) {
      return 400;
    }
    method_buff[i] = *(rl+i);
  }
  method_buff[7] = '\0';
  ++i;

  if (strcmp(method_buff, "GET") && strcmp(method_buff, "POST")) {
    return 405;
  }

  // Parse URI
  char uri_buff[201];
  memset(uri_buff, 0, sizeof(char) * 201);
  for (int j = 0; *(rl+i) != ' '; i++, j++) {
    if (j > 199) {
      return 414;
    }
    uri_buff[j] = *(rl+i);
  }
  uri_buff[200] = '\0';
  ++i;

  // Parse HTTP version
  char ver_buff[9];
  memset(ver_buff, 0, sizeof(char) * 9);
  for (int j = 0; *(rl+i) != '\r'; i++, j++) {
    if (*(rl+i) == '\r') break;
    ver_buff[j] = *(rl+i);
  }
  ver_buff[8] = '\0';

  if (strcmp(ver_buff, "HTTP/1.0") && strcmp(ver_buff, "HTTP/1.1")) {
    return 505;
  }

  // Handle the request
  if (strcmp(method_buff, "GET") == 0) {
    // Handle the get request
    printf("GET request recieved\n");
  } else if (strcmp(method_buff, "POST")) {
    // Handle the post request
    printf("POST request recieved\n");
  }


  return 0;
}


