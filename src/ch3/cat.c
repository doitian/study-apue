#include <myapue.h>

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

static const char* STDIN_FILENAME = "-";
static const int BUF_SIZE = 256;

static void catfd(int fd);
static void catfile(const char* path);

int main(int argc, char* argv[]) {
  size_t i = 0;

  if (argc == 1) {
    catfd(STDIN_FILENO);
  } else {
    for (i = 1; i < argc; ++i) {
      if (0 == strncmp(STDIN_FILENAME, argv[i], 1)) {
        catfd(STDIN_FILENO);
      } else {
        catfile(argv[i]);
      }
    }
  }
  
  return EXIT_SUCCESS;
}

void catfd(int fd) {
  char buf[BUF_SIZE];
  ssize_t bytes;
  
  while (0 < (bytes = read(fd, buf, BUF_SIZE))) {
    err_assert(bytes == write(STDOUT_FILENO, buf, bytes));
  }

  err_assert(bytes == 0);
}

void catfile(const char* path) {
  int fd;

  fd = open(path, O_RDONLY);
  err_assert(fd =! -1);
  catfd(fd);
  close(fd);
}
