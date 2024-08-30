// Copyright 2024 Vanja Stojanović

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#include "lib/lib.h"
#include "log/log.h"

#define SERVER_PORT 80
#define RECV_BUFFER 1024


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
  sockaddrinfo.ai_family = AF_INET;
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
    close(sockfd);
    error("Bind failed!");
  }

  freeaddrinfo(servinfo);
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

    log(extract_peer_addr(their_addr, connfd));

    if (!fork()) {
      close(sockfd);
      char buffer[RECV_BUFFER];
      if (recv(connfd, buffer, RECV_BUFFER, MSG_DONTWAIT) > 0) {
        printf("%s", buffer);
      }
      close(connfd);
      return EXIT_SUCCESS;
    }
    close(connfd);
  }

  return EXIT_SUCCESS;
}


