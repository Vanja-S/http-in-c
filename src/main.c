// Copyright 2024 Vanja Stojanović

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include "lib/lib.h"
#include "log.h"

#define SERVER_PORT 80

char* concat(const char *s1, const char *s2);

int main(int argc, char* argv[]) {
  // 1. Implement socket listening and accept requests
  // 2. Parse and read the requests
  // 3. Respond with appropriate response
  // It will only support GET and POST methods
  // and implement all error codes
  int status;
  int sockfd;
  struct addrinfo sockaddrinfo, *servinfo;

  // init the socket
  if ((sockfd = socket(PF_INET, SOCK_STREAM, 0)) < 0) {
    error("Socket cannot be opened");
  }

  memset(&sockaddrinfo, 0, sizeof(sockaddrinfo));
  sockaddrinfo.ai_flags = AF_INET;
  sockaddrinfo.ai_socktype = SOCK_STREAM;
  sockaddrinfo.ai_flags = AI_PASSIVE;

  // prepare the address space and bind it
  if ((status = getaddrinfo(NULL, uint_to_string(SERVER_PORT), &sockaddrinfo, &servinfo)) != 0) {
    const char* gai_error = gai_strerror(status);
    error(concat("Cannot get socket info", gai_error));
  }

  if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &(int){1}, sizeof(int)) == -1) {
    error("setsockopt error");
  }

  // bind the socket to a sockaddr_in
  if (bind(sockfd, servinfo->ai_addr, servinfo->ai_protocol)) {
    error("Bind failed!");
  }

  return EXIT_SUCCESS;
}

char* concat(const char *s1, const char *s2) {
    const size_t len1 = strlen(s1);
    const size_t len2 = strlen(s2);
    char *result = malloc(len1 + len2 + 1);  // +1 for the null-terminator
    memcpy(result, s1, len1);
    memcpy(result + len1, s2, len2 + 1);  // +1 to copy the null-terminator
    return result;
}
