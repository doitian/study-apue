#define ECHO_SERVER_KEY_FILE_MODE S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH
#define ECHO_SERVER_KEY_FILE "./tmp/echo-server.key"
#define ECHO_SERVER_MESSAGE_NBYTES 4096
#define ECHO_SERVER_PROJECT_ID 0

struct echo_server_message {
  long mtype;
  char mtext[ECHO_SERVER_MESSAGE_NBYTES];
};

