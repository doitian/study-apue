#include "myapue.h"
#include <errno.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <stdio.h>

static const int MAXLINE = 4096;
static void err_doit(int, const char *, va_list);

void err_ret(const char *fmt, ...) {
  va_list ap;
  
  va_start(ap, fmt);
  err_doit(errno, fmt, ap);
  va_end(ap);
}

void err_sys(const char *fmt, ...) {
  va_list ap;
  
  va_start(ap, fmt);
  err_doit(errno, fmt, ap);
  exit(EXIT_FAILURE);
  va_end(ap);
}

void err_assert(int test_result) {
  if (!test_result) {
    err_sys("Fatal Error");
  }
}

void err_doit(int error, const char *fmt, va_list ap) {
  char buf[MAXLINE];
  ssize_t pos;
  
  vsnprintf(buf, MAXLINE - 1, fmt, ap);
  pos = strlen(buf);

  snprintf(buf + pos, MAXLINE - pos - 1, ": %s\n", strerror(error));

  fflush(stdout);
  fputs(buf, stderr);
  fflush(stderr);
}
