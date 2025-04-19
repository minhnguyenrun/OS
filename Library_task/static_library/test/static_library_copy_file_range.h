#include <fcntl.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/stat.h>

int copy_part_from_paths(const char *src_path, const char *dst_path, off_t offset_src, off_t offset_dst, size_t size);

int copy_all_from_paths(const char *src_path, const char *dst_path);

int copy_part_from_fds(int fd_in, int fd_out, off_t offset_in, off_t offset_out, size_t size);

int copy_all_from_fds(int fd_in, int fd_out);
