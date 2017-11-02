#include<stdio.h>
#include<sys/stat.h>
#include<dirent.h>
#include<unistd.h>
#include<fcntl.h>
#include<string.h>
#include<errno.h>
#include<stdlib.h>

#include"include/dir_stuff.h"

char* list_files(char *dir) {
	char *res = malloc(256*sizeof(char));
	sprintf(res, "%s\n%s", 
		get_regular_files(dir),
		get_directories(dir)
	);
	
	return res;
}

char* get_regular_files(char *curr_dir) {
	DIR *dir;
	dir = opendir(curr_dir);
	
	struct dirent *entry;
	char *res = malloc(128*sizeof(char));
	sprintf(res, "Regular files:\n");
	
	while (entry = readdir(dir)) {
		if (entry->d_type == DT_REG) {
			sprintf(res, "%s\n\t%s", res, entry->d_name);
			sprintf(res, "%s\n\t%s", res, entry->d_name);
		}
	}
	
	return res;
}

char* get_directories(char *curr_dir) {
	DIR *dir;
	dir = opendir(curr_dir);
	
	struct dirent *entry;
	char *res = malloc(128*sizeof(char));
	sprintf(res, "Directories:\n");
	
	while (entry = readdir(dir)) {
		if (entry->d_type == DT_DIR) {
			res = strcat(res, entry->d_name);
			res = strcat(res, "\n");
		}
	}
	
	return res;
}

off_t get_files_size(char *dir) {
	return 0;
}

