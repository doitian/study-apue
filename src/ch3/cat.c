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
    if (bytes != write(STDOUT_FILENO, buf, bytes)) {
      fprintf(stderr, "Write error: %s\n", strerror(errno));
      exit(EXIT_FAILURE);
    }
  }

  if (bytes != 0) {
    fprintf(stderr, "Read error: %s\n", strerror(errno));
    exit(EXIT_FAILURE);
  }
}

void catfile(const char* path) {
  int fd;

  fd = open(path, O_RDONLY);
  if (fd < 0) {
    fprintf(stderr, "Cannot open the file %s: %s\n", path, strerror(errno));
    exit(EXIT_FAILURE);
  }
  catfd(fd);
  close(fd);
}
