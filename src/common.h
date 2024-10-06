#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>

int32_t read_full(int socket_fd, char *buffer, size_t bytes_to_read);
int32_t write_all(int socket_fd, char *buffer, size_t bytes_to_send);

// Message consists of a 4 byte uint32, then up to 4096 bytes of message
const size_t msg_len_size = 4;
const size_t max_msg_len = 4096;
const size_t msg_buffer_len = max_msg_len + msg_len_size + 1;