#include "client_main.h"

int main(int argc, char *argv[]) {
  int32_t err;

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

  err = query(socket_fd, "Hello 1");
  if (err) {
    return err;
  }

  err = query(socket_fd, "Hello 2");
  if (err) {
    return err;
  }

  err = query(socket_fd, "Hello 3");
  if (err) {
    return err;
  }

  close(socket_fd);

  return 0;
}

int32_t query(int socket_fd, const char *message) {
  char read_buffer[msg_buffer_len] = {};
  char write_buffer[msg_buffer_len] = {};
  uint32_t msg_len;
  int32_t err;

  msg_len = (uint32_t) strlen(message);
  memcpy(write_buffer, &msg_len, msg_len_size);
  memcpy(&write_buffer[msg_len_size], message, msg_len);
  err = write_all(socket_fd, write_buffer, msg_len_size + msg_len);
  if (err) {
    fprintf(stderr, "Writing Message Failed\n");
    return err;
  }

  // Read message size
  err = read_full(socket_fd, read_buffer, msg_len_size);
  if (err) {
    fprintf(stderr, "Reading Message Size Failed\n");
    return err;
  }

  memcpy(&msg_len, read_buffer, msg_len_size);
  if (msg_len > max_msg_len) {
    return -1;
  }

  // Read message
  err = read_full(socket_fd, &read_buffer[msg_len_size], msg_len);
  if (err) {
    fprintf(stderr, "Reading Message Failed\n");
    return err;
  }

  read_buffer[msg_len_size + msg_len] = '\0';

  printf("Server message: %s\n", &read_buffer[4]);

  return 0;
}