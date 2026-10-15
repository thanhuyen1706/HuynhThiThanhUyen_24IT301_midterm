#include "ls.h"

int main(int argc, char *argv[]) {
    Options opts;
    int first_path_idx;

    parse_options(argc, argv, &opts, &first_path_idx);
    if (first_path_idx >= argc) {
        list_directory(".", &opts);
    } else {
        int i;
        for (i = first_path_idx; i < argc; i++) {
            if (argc - first_path_idx > 1) {
                printf("%s:\n", argv[i]);
            }
            list_directory(argv[i], &opts);
            if (i < argc - 1) {
                printf("\n");
            }
        }
    }

    return 0;
}
