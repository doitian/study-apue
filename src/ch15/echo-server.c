#include "myapue.h"
#include "echo-server.h"

#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

int main(int argc, char* argv[]) {
  /* Create message queue, and write key to file */
  key_t key = 0;
  int qid = 0;
  struct echo_server_message msg;

  err_assert(-1 != creat(ECHO_SERVER_KEY_FILE, ECHO_SERVER_KEY_FILE_MODE));

  key = ftok(ECHO_SERVER_KEY_FILE, ECHO_SERVER_PROJECT_ID);
  err_assert(-1 != key);

  qid = msgget(key, 0666 | IPC_CREAT);
  err_assert(qid != -1);

  for(;;) {
    err_assert(-1 != msgrcv(qid, &msg, ECHO_SERVER_MESSAGE_NBYTES, 0, 0));
    fputs(msg.mtext, stdout);
    fputs("\n", stdout);
  }

  return EXIT_SUCCESS;
}
