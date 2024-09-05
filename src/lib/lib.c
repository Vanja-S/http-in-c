// Copyright 2024 Vanja S.

#include <sys/socket.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <stdio.h>

#include "../log/log.h"
#include "lib.h"

unsigned num_of_digits(const unsigned n) {
    if (n < 10) return 1;
    return 1 + num_of_digits(n / 10);
}

char* extract_peer_addr(struct sockaddr_storage their_addr, int connfd) {
  struct sockaddr_in* sin = (struct sockaddr_in*)&their_addr;
  socklen_t sin_size = sizeof(struct sockaddr);
  if (getpeername(connfd, (struct sockaddr*)sin, &sin_size) == -1) {
    error("getpeername");
    return NULL;
  }
  static char msg[INET_ADDRSTRLEN];
  if (inet_ntop(AF_INET, &(sin->sin_addr), msg, INET_ADDRSTRLEN) == NULL) {
    error("inet_ntop");
    return NULL;
  }

  return msg;
}

void concat_char_buffer(char** mem_segment, char* buffer, int total_buffers, int buffer_size) {
  log("here");
  *mem_segment = realloc(*mem_segment, total_buffers * buffer_size);
  if (*mem_segment == NULL) {
    error("Failed to reallocate memory");
    exit(EXIT_FAILURE);
  }
  memcpy(*mem_segment + (total_buffers-1) * buffer_size, buffer, buffer_size);
}
