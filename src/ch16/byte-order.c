#include <stdlib.h>
#include <inttypes.h>
#include <stdio.h>

union byte_order_checker {
  uint16_t word;
  uint8_t bytes[2];
};

int main(int argc, char* argv[]) {
  union byte_order_checker checker;
  checker.word = 1;
  
  if (checker.bytes[0]) {
    printf("Little Endian\n");
  } else {
    printf("Big Endian\n");
  }

  return EXIT_SUCCESS;
}
