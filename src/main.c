// Copyright 2024 Vanja Stojanović

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>


#define SERVER_PORT 80


int main(int argc, char *argv[]) {
  // 1. Implement socket listening and accept requests
  // 2. Parse and read the requests
  // 3. Respond with appropriate response
  // It will only support GET and POST methods
  // and implement all error codes
  int sockfd;
  int sockopt;

  if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
    // Handle error that socket couldn't be opened
  }

  // Set socket options
  sockopt = setsockopt();  

  return EXIT_SUCCESS;
}
