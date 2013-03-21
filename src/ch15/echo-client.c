#include "myapue.h"
#include "echo-server.h"

#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

int main(int argc, char* argv[]) {
  /* Create message queue, and write key to file */
  key_t key = 0;
  int qid = 0;
  struct echo_server_message msg;

  if (argc == 1) {
    return EXIT_SUCCESS;
  }

  key = ftok(ECHO_SERVER_KEY_FILE, ECHO_SERVER_PROJECT_ID);
  err_assert(-1 != key);

  qid = msgget(key, 0666);
  err_assert(qid != -1);

  msg.mtype = 1;
  msg.mtext[ECHO_SERVER_MESSAGE_NBYTES - 1] = '\0';
  strncpy(msg.mtext, argv[1], ECHO_SERVER_MESSAGE_NBYTES - 1);

  err_assert(-1 != msgsnd(qid, &msg, ECHO_SERVER_MESSAGE_NBYTES, 0));

  return EXIT_SUCCESS;
}
