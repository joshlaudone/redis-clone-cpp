#include "common.h"

int32_t read_full(int socket_fd, char *buffer, size_t bytes_to_read) {
  ssize_t return_val;
  while (bytes_to_read > 0) {
    return_val = read(socket_fd, buffer, bytes_to_read);
    if (return_val <= 0) {
      return -1;
    }
    bytes_to_read -= (size_t) return_val;
    buffer += return_val;
  }
  return 0;
}

int32_t write_all(int socket_fd, char *buffer, size_t bytes_to_send) {
  ssize_t return_val;
  while (bytes_to_send > 0) {
    return_val = write(socket_fd, buffer, bytes_to_send);
    if (return_val <= 0) {
      return -1;
    }
    bytes_to_send -= (size_t) return_val;
    buffer += return_val;
  }
  return 0;
}