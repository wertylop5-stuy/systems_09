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
			sprintf(res, "%s\n\t%s", res, entry->d_name);
		}
	}
	
	return res;
}

off_t get_files_size(char *curr_dir) {
	DIR *dir;
	dir = opendir(curr_dir);
	
	struct dirent *entry;		//readdir() constructs a struct dirent then returns it
	struct stat file;		//stat() will directly set the values in struct stat
	char path[64];			//dir + filename
	off_t total = 0;
	
	int status;
	
	while (entry = readdir(dir)) {
		
		//if regular file
		if (entry->d_type == DT_REG) {
			sprintf(path, "%s/%s", curr_dir, entry->d_name);
			
			//printf("%s\n", path);
			
			status = stat(path, &file);
			if (status < 0) {
				fprintf(stderr, "error %d: %s\n", errno, strerror(errno));
				exit(1);
			}
			//printf("size of %s: %lu\n", entry->d_name, file.st_size);
			
			total += file.st_size;
		}
		
	}
	
	
	return total;
}

off_t get_full_dir_size(char *curr_dir) {
	DIR *dir;
	dir = opendir(curr_dir);
	
	struct dirent *entry;		//readdir() constructs a struct dirent then returns it
	struct stat file;		//stat() will directly set the values in struct stat
	char path[64];			//dir + filename
	off_t total = 0;
	
	int status;
	
	while (entry = readdir(dir)) {
		//printf("entry: %s\n", entry->d_name);
		sprintf(path, "%s/%s", curr_dir, entry->d_name);
		//printf("path: %s\n", path);

		if (entry->d_type == DT_REG) {
			
			status = stat(path, &file);
			if (status < 0) {
				fprintf(stderr, "error %d: %s\n", errno, strerror(errno));
				exit(1);
			}
			//printf("size of %s: %lu\n", path, file.st_size);
			
			total += file.st_size;
		}
		//0 means equal, and 0 is false. therefore, skip it if its 0
		else if (strncmp(entry->d_name, "..", strlen(entry->d_name)) && strncmp(entry->d_name, ".", strlen(entry->d_name))){
			//printf("dir case: %s\n", entry->d_name);
			
			sprintf(path, "%s/%s", curr_dir, entry->d_name);
			total += get_full_dir_size(path);
			//sprintf(path, "%s", curr_dir);
		}
	}
	
	return total;
}


char* better_size(off_t size) {
	float more_info = (float)size;
	char *out = malloc(30*sizeof(char));
	
	if (size < 1024) {
		sprintf(out, "B: %lu", size);
		return out;
	}
	
	char counter = 0;
	while(more_info > 1024) {
		counter++;
		more_info /= 1024;
	}
	
	switch(counter) {
		case 0:
			sprintf(out, "B: %f", more_info);
		break;
		
		case 1:
			sprintf(out, "KB: %f", more_info);
		break;

		case 2:
			sprintf(out, "MB: %f", more_info);
		break;
	
		case 3:
			sprintf(out, "GB: %f", more_info);
		break;
	}
	
	return out;
}


