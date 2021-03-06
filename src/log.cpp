#include "log.h"

#include <stdarg.h>
#include <stdio.h>

void print_type(enum t_log_type type) {
  switch (type) {
  case debug:
    printf("[%sDEBG%s]", ANSI_GREEN, ANSI_RESET);
    break;
  case info:
    printf("[%sINFO%s]", ANSI_WHITE, ANSI_RESET);
    break;
  case warning:
    printf("[%sWARN%s]", ANSI_YELLOW, ANSI_RESET);
    break;
  case error:
    printf("[%sERR %s]", ANSI_RED, ANSI_RESET);
    break;
  }
}

void rtlog(enum t_log_type type, int line, const char *file, const char *fmt,
           ...) {
  // buffer we will use to print the message into
  char buffer[512];

  // print the type of log message
  print_type(type);

  // print the log message into the buffer
  va_list va;
  va_start(va, fmt);
  vsnprintf(buffer, sizeof(buffer), fmt, va);
  va_end(va);

  // print the file and line info, and the log message buffer
  printf("[%s:%d] %s\n", file, line, buffer);
}
