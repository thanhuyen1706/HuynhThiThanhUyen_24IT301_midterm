#include "ls.h"
void parse_options(int argc, char *argv[], Options *opts, int *first_path_idx) {
    opts->show_all = 0;
    opts->long_format = 0;
    opts->recursive = 0;
    opts->reverse = 0;
    opts->sort_time = 0;

    int i;
    for (i = 1; i < argc; i++) {
        if (argv[i][0] == '-' && argv[i][1] != '\0') {
            int j = 1;
            while (argv[i][j] != '\0') {
                switch (argv[i][j]) {
                    case 'a':
                        opts->show_all = 1;
                        break;
                    case 'l':
                        opts->long_format = 1;
                        break;
                    case 'R':
                        opts->recursive = 1;
                        break;
                    case 'r':
                        opts->reverse = 1;
                        break;
                    case 't':
                        opts->sort_time = 1;
                        break;
                    default:
                        fprintf(stderr, "my_ls: invalid option -- '%c'\n", argv[i][j]);
                        exit(1);
                }
                j++;
            }
        } else {
            break;
        }
    }
    *first_path_idx = i;
}
void list_directory(const char *path, const Options *opts) {
    DIR *dir = opendir(path);
    if (!dir) {
        perror("my_ls");
        return;
    }

    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        if (!opts->show_all && entry->d_name[0] == '.') {
            continue;
        }
        printf("%s  ", entry->d_name);
    }
    printf("\n");
    closedir(dir);
}
