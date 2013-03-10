#include <myapue.h>

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

static const char* RECORD_A = "ABCDEF";
static const char* RECORD_B = "abcdef";
static const int BUFSIZE = 4096;

int main(int argc, char* argv[]) {
  int fd;
  ssize_t bytes;
  char buff[BUFSIZE];

  if (argc != 2) {
    fprintf(stderr, "Usage: ex6 file\n");
    exit(EXIT_FAILURE);
  }

  fd = open(argv[1], O_RDWR | O_APPEND | O_CREAT | O_TRUNC);
  err_assert(fd != -1);

  // write abcdef
  bytes = strlen(RECORD_A);
  err_assert(bytes == write(fd, RECORD_A, bytes));
  bytes = strlen(RECORD_B);
  err_assert(bytes == write(fd, RECORD_B, bytes));

  // test seek and read
  err_assert(-1 != lseek(fd, 0, SEEK_SET));
  bytes = strlen(RECORD_A);
  err_assert(bytes == read(fd, buff, bytes));
  printf("lseek 0 then read: %s\n", buff);

  // test seek and write
  err_assert(-1 != lseek(fd, 0, SEEK_SET));
  bytes = strlen(RECORD_B);
  err_assert(bytes == write(fd, RECORD_B, bytes));

  bytes = strlen(RECORD_A);
  err_assert(bytes == pread(fd, buff, bytes, 0));
  printf("lseek 0 then write: %s\n", buff);

  // test pwrite
  bytes = strlen(RECORD_B);
  err_assert(bytes == pwrite(fd, RECORD_B, bytes, 0));

  bytes = strlen(RECORD_A);
  err_assert(bytes == pread(fd, buff, bytes, 0));
  printf("pwrite: %s\n", buff);

  return EXIT_SUCCESS;
}
