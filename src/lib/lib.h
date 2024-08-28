// Copyright 2024 Vanja S.

#ifndef SRC_LIB_LIB_H_
#define SRC_LIB_LIB_H_

// string.c
char* uint_to_string(const unsigned n);
char* concat(const char *s1, const char *s2);

// lib.c
unsigned num_of_digits(const unsigned n);
char* extract_peer_addr(struct sockaddr_storage their_addr, int connfd);

#endif  // SRC_LIB_LIB_H_
