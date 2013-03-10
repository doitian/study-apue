EXECUTABLE_SOURCES := $(wildcard src/*/*.c)
EXECUTABLES := $(patsubst src/%.c,bin/%,$(EXECUTABLE_SOURCES))
SOURCES := $(EXECUTABLE_SOURCES) lib/myapue.c
OBJECTS := $(patsubst %.c,%.o,$(SOURCES))
CFLAGS = -Ilib -Wall
LDFLAGS = -lm
CC = cc
LD = cc

all: $(EXECUTABLES)

clean:
	rm -f $(EXECUTABLES) $(OBJECTS)

$(EXECUTABLES): bin/%: src/%.o lib/myapue.o
	mkdir -p `dirname $@`
	$(LD) $(LDFLAGS) -o $@ $^

$(OBJECTS): %.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@


.PHONY: all clean
