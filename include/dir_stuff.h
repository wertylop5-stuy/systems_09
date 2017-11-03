#ifndef DIR_STUFF_H
#define DIR_STUFF_H

//off_t is in fcntl.h
#include<fcntl.h>
#include<dirent.h>

char* list_files(char *);
char* get_regular_files(char *);
char* get_directories(char *);

off_t get_files_size(char *);
off_t get_full_dir_size(char *);

char* better_size(off_t);

#endif
