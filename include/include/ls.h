#ifndef LS_H
#define LS_H

#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

typedef struct {
    int show_all;      
    int long_format; 
    int recursive;     
    int reverse;        
    int sort_time;     
} Options;

void parse_options(int argc, char *argv[], Options *opts, int *first_path_idx);
void list_directory(const char *path, const Options *opts);

#endif
