#include "static_library_copy_file_range.h"

ssize_t my_copy_file_range(int fd_in, off_t *off_in,
                           int fd_out, off_t *off_out,
                           size_t len, unsigned int flags) {
    return syscall(__NR_copy_file_range, fd_in, off_in, fd_out, off_out, len, flags);
}

int copy_part_from_paths(const char *src_path, const char *dst_path, off_t offset_src, off_t offset_dst, size_t size) {
    int fd_in = open(src_path, O_RDONLY | O_CREAT);
    if (fd_in < 0) return perror("open src"), -1;

    int fd_out = open(dst_path, O_WRONLY | O_CREAT, 0644);
    if (fd_out < 0) return perror("open dst"), close(fd_in), -1;

    ssize_t copied = my_copy_file_range(fd_in, &offset_src, fd_out, &offset_dst, size, 0);
    if (copied < 0) perror("copy_file_range");

    close(fd_in);
    close(fd_out);
    return (copied < 0) ? -1 : 0;
}


int copy_all_from_paths(const char *src_path, const char *dst_path) {
    int fd_in = open(src_path, O_RDONLY | O_CREAT);
    if (fd_in < 0) return perror("open src"), -1;

    int fd_out = open(dst_path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd_out < 0) return perror("open dst"), close(fd_in), -1;

    ssize_t n;
    off_t off_in = 0, off_out = 0;
    size_t chunk = 4096;

    while ((n = my_copy_file_range(fd_in, &off_in, fd_out, &off_out, chunk, 0)) > 0);
    if (n < 0) perror("copy_file_range");

    close(fd_in);
    close(fd_out);
    return (n < 0) ? -1 : 0;
}

int copy_part_from_fds(int fd_in, int fd_out, off_t offset_in, off_t offset_out, size_t size) {
    ssize_t copied = my_copy_file_range(fd_in, &offset_in, fd_out, &offset_out, size, 0);
    if (copied < 0) return perror("copy_file_range"), -1;
    return 0;
}

int copy_all_from_fds(int fd_in, int fd_out) {
    ssize_t n;
    off_t off_in = 0, off_out = 0;
    size_t chunk = 4096;

    while ((n = my_copy_file_range(fd_in, &off_in, fd_out, &off_out, chunk, 0)) > 0);
    if (n < 0) return perror("copy_file_range"), -1;
    return 0;
}
