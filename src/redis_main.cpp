#include "redis_main.h"

int main(int argc, char *argv[]) {
  int socket_fd = socket(AF_INET, SOCK_STREAM, 0);

  int val = 1;
  setsockopt(socket_fd, SOL_SOCKET, SO_REUSEADDR, &val, sizeof(val));

  struct sockaddr_in addr = {};
  addr.sin_family = AF_INET;
  addr.sin_port = ntohs(1234);
  addr.sin_addr.s_addr = htons(INADDR_ANY);
  int rv = bind(socket_fd, (const sockaddr *)&addr, sizeof(addr));
  if (rv) {
    fprintf(stderr, "Failed to bind");
    return -1; 
  }

  rv = listen(socket_fd, SOMAXCONN);
  if (rv) {
    fprintf(stderr, "Failed to listen");
    return -1; 
  }

  while (true) {
    struct sockaddr_in client_addr = {};
    socklen_t addrlen = sizeof(client_addr);
    int client_fd = accept(socket_fd, (struct sockaddr *) &client_addr, &addrlen);
    if (client_fd < 0) {
      continue;
    }

    do_something(client_fd);
    close(client_fd);
  }
}

static void do_something(int client_fd) {
  char read_buffer[64] = {};

  ssize_t bytes_read = read(client_fd, read_buffer, sizeof(read_buffer) - 1);

  if (bytes_read < 0) {
    fprintf(stderr, "read() error");
    return;
  }

  printf("Client message: %s\n", read_buffer);

  char write_buffer[] = "world";
  write(client_fd, write_buffer, strlen(write_buffer));
}