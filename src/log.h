// Copyright 2024 Vanja S.

#ifndef SRC_LOG_H_
#define SRC_LOG_H_

enum LogLevel {
  DEBUG,
  INFO,
  ERROR
};

extern enum LogLevel g_log_level;

void set_log_level(enum LogLevel log_level);

void log(char* msg);

void debug(char* msg);

void error(char* msg);

#endif  // SRC_LOG_H_
