#include "myapue.h"

#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <stdio.h>
#include <unistd.h>
#include <pwd.h>
#include <grp.h>
#include <sys/types.h>

static void print_id(const char* id_or_name);
static void print_id_uid(uid_t uid);

int main(int argc, char* argv[]) {
  if (argc == 1) {
    print_id_uid(getuid());
  } else {
    print_id(argv[1]);
  }
  
  return EXIT_SUCCESS;
}

static const char* get_group_name_by_gid(gid_t gid) {
  struct group* group = NULL;
  
  group = getgrgid(gid);
  err_assert(NULL != group);

  return group->gr_name;
}

static void print_id_pwent(const struct passwd* pwent) {
  const struct group* grp;
  char** member;
  int first_supplement_group = 1;

  printf("uid=%d(%s)", pwent->pw_uid, pwent->pw_name);
  printf(" gid=%d(%s)", pwent->pw_gid, get_group_name_by_gid(pwent->pw_gid));

  // find out all supplement groups
  setgrent();
  errno = 0;
  while (NULL != (grp = getgrent())) {
    member = grp->gr_mem;
    while (NULL != *member) {
      if (0 == strcmp(*member, pwent->pw_name)) {
        if (first_supplement_group) {
          first_supplement_group = 0;
          printf(" groups=");
        } else {
          printf(",");
        }
        printf("%d(%s)", grp->gr_gid, grp->gr_name);
      }
      ++member;
    }
    
    errno = 0;
  }
  err_assert(errno == 0);
  
  endgrent();

  fputs("\n", stdout);
}

static void print_id_name(const char* name) {
  struct passwd* pwent = NULL;

  pwent = getpwnam(name);
  err_assert(NULL != pwent);
  
  print_id_pwent(pwent);
}

static void print_id_uid(uid_t uid) {
  struct passwd* pwent = NULL;

  pwent = getpwuid(uid);
  err_assert(NULL != pwent);
  
  print_id_pwent(pwent);
}

static void print_id(const char* id_or_name) {
  char* endpos = NULL;
  long id = 0;

  id = strtol(id_or_name, &endpos, 10);
  if (*endpos == '\0') {
    /* valid id */
    print_id_uid((uid_t)id);
  } else {
    print_id_name(id_or_name);
  }
}
