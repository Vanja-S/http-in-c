// Copyright 2024 Vanja S.

#include "log.h"
#include <stdio.h>
#include <stdlib.h>

enum LogLevel g_log_level = INFO;

void set_log_level(enum LogLevel log_level) {
  extern enum LogLevel g_log_level;
  g_log_level = log_level;
}

void log(char* msg) {
  printf("[LOG]: %s\n", msg);
  fflush(stdout);
}

void debug(char* msg) {
  printf("[DEBUG]: %s\n", msg);
  fflush(stdout);
}

void error(char* msg) {
  perror(msg);
  exit(1);
}
