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

  // Serve connections
  while (true) {
    struct sockaddr_in client_addr = {};
    socklen_t addrlen = sizeof(client_addr);
    int client_fd = accept(socket_fd, (struct sockaddr *) &client_addr, &addrlen);
    if (client_fd < 0) {
      continue;
    }

    while (true) {
      int32_t err = one_request(client_fd);
      if (err) {
        break;
      }
    }

    close(client_fd);
  }

  return 0;
}

int32_t one_request(int client_fd) {
  char read_buffer[msg_buffer_len] = {};
  int32_t err;

  // Read message size
  err = read_full(client_fd, read_buffer, msg_len_size);
  if (err) {
    return err;
  }

  uint32_t msg_len;
  memcpy(&msg_len, read_buffer, msg_len_size);
  if (msg_len > max_msg_len) {
    return -1;
  }

  // Read message
  err = read_full(client_fd, &read_buffer[msg_len_size], msg_len);
  if (err) {
    return err;
  }

  read_buffer[msg_len_size + msg_len] = '\0';

  printf("Client message: %s\n", &read_buffer[4]);

  // Echo client message
  err =  write_all(client_fd, read_buffer, msg_len_size + msg_len);
  return err;
}