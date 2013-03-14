#include "myapue.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

static char** extract_env(char* argv[]);

int main(int argc, char* argv[]) {
  char** args = extract_env(argv);

  err_assert(*args != NULL);
  err_assert(-1 != execvp(*args, args));

  return EXIT_SUCCESS;
}

/* tests whether the string is ENV=value */
static int is_env(const char* str) {
  return strchr(str, '=') != NULL;
}

static char** extract_env(char* argv[]) {
  size_t i = 0;

  for (i = 1; (argv[i] != NULL && is_env(argv[i])); ++i) {
    err_assert(0 == putenv(argv[i]));
  }
  return argv + i;
}
