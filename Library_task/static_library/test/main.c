#include "static_library_copy_file_range.h"

int main(int argc, char *argv[]) {
    if (argc == 3) {
        const char *src = argv[1];
        const char *dst = argv[2];

        if (copy_all_from_paths(src, dst) == 0) {
            printf("Successfully copied the entire file.\n");
        } else {
            fprintf(stderr, "Error: failed to copy the entire file.\n");
            return 1;
        }
    } else if (argc == 6) {
        const char *src = argv[1];
        const char *dst = argv[2];
        off_t offset_src = atoll(argv[3]);
        off_t offset_dst = atoll(argv[4]);
        size_t size = atoi(argv[5]);

        if (copy_part_from_paths(src, dst, offset_src, offset_dst, size) == 0) {
            printf("Successfully copied %zu bytes from offset %lld to %lld.\n", size, (long long)offset_src, (long long)offset_dst);
        } else {
            fprintf(stderr, "Error: failed to copy a portion of the file.\n");
            return 1;
        }
    } else {
        fprintf(stderr, "Usage:\n");
        fprintf(stderr, "  %s <src> <dst>                         # copy the entire file\n", argv[0]);
        fprintf(stderr, "  %s <src> <dst> <offset_in> <offset_out> <size>  # copy a specific portion\n", argv[0]);
        return 1;
    }

    return 0;
}
