#include "myapue.h"

#include <stdlib.h>
#include <dirent.h>
#include <unistd.h>
#include <sys/stat.h>
#include <stdio.h>

static void ls_dir(const char* prefix, const char* path);
static void ls(const char* path);

int main(int argc, char* argv[]) {
  char *cwd;
  int i;

  if (argc == 1) {
    cwd = getcwd(NULL, 0);
    err_assert(cwd != NULL);

    ls_dir(NULL, cwd);
    
    free(cwd);
  } else {
    for (i = 1; i < argc; ++i) {
      ls(argv[i]);
    }
  }
  
  return EXIT_SUCCESS;
}

static void ls_file(const char* prefix, const char* path) {
  if (NULL == prefix) {
    printf("%s\n", path);
  } else {
    printf("%s/%s\n", prefix, path);
  }
}

static void ls_dir(const char* prefix, const char* path) {
  DIR* dir;
  struct dirent* entry;

  dir = opendir(path);
  err_assert(NULL != dir);
  
  while (NULL != (entry = readdir(dir))) {
    ls_file(prefix, entry->d_name);
  }
}

static void ls(const char* path) {
  struct stat file_stat;
  err_assert(-1 != stat(path, &file_stat));
  if (S_ISDIR(file_stat.st_mode)) {
    ls_dir(path, path);
  } else {
    ls_file(path, path);
  }
}
