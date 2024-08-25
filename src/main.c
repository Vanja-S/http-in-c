// Copyright 2024 Vanja Stojanović

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include "lib/lib.h"
#include "log/log.h"

#define SERVER_PORT 80


int main(int argc, char* argv[]) {
  // 1. Implement socket listening and accept requests
  // 2. Parse and read the requests
  // 3. Respond with appropriate response
  // It will only support GET and POST methods
  // and implement all error codes
  int status;
  int sockfd;
  struct addrinfo sockaddrinfo, *servinfo;
  struct sockaddr_storage their_addr;

  // init the socket
  if ((sockfd = socket(PF_INET, SOCK_STREAM, 0)) < 0) {
    error("Socket cannot be opened");
  }

  memset(&sockaddrinfo, 0, sizeof(sockaddrinfo));
  sockaddrinfo.ai_flags = AF_INET;
  sockaddrinfo.ai_socktype = SOCK_STREAM;
  sockaddrinfo.ai_flags = AI_PASSIVE;

  // prepare the address space and bind it
  status = getaddrinfo(NULL,
                       uint_to_string(SERVER_PORT),
                       &sockaddrinfo,
                       &servinfo);
  if (status != 0) {
    const char* gai_error = gai_strerror(status);
    error(concat("Cannot get socket info", gai_error));
  }

  status = setsockopt(sockfd,
                      SOL_SOCKET,
                      SO_REUSEADDR,
                      &(int){1},
                      sizeof(int));
  if (status == -1) {
    error("setsockopt error");
  }

  // bind the socket to a sockaddr_in
  if (bind(sockfd, servinfo->ai_addr, servinfo->ai_protocol) < 0) {
    error("Bind failed!");
  }

  // listen for incoming connections
  if (listen(sockfd, 10) < 0) {
    error("Listening failed!");
  }

  // server loop for accepting incoming connections

  while (1) {
    socklen_t sin_size = sizeof(their_addr);
    int connfd = accept(sockfd, (struct sockaddr*)&their_addr, &sin_size);
    if (connfd == -1) {
      perror("accept");
      continue;
    }


  }

  return EXIT_SUCCESS;
}


