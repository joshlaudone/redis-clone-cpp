#include "client_main.h"

int main(int argc, char *argv[]) {
  int socket_fd = socket(AF_INET, SOCK_STREAM, 0);

  struct sockaddr_in addr = {};
  addr.sin_family = AF_INET;
  addr.sin_port = ntohs(1234);
  addr.sin_addr.s_addr = ntohl(INADDR_LOOPBACK);
  int rv = connect(socket_fd, (const sockaddr *)&addr, sizeof(addr));
  if (rv) {
    fprintf(stderr, "Failed to connect");
    return -1; 
  }


  char msg[] = "hello";
  write(socket_fd, msg, sizeof(msg));

  char read_buffer[64] = {};
  ssize_t n = read(socket_fd, read_buffer, sizeof(read_buffer) - 1);
  if (n < 0) {
    fprintf(stderr, "read fail");
    return -1;
  }

  printf("Server message: %s\n", read_buffer);
  close(socket_fd);

}