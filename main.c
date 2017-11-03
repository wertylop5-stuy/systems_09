#include<stdio.h>

#include"include/dir_stuff.h"

int main() {
	//printf("Size of files in '.': %lu\n", get_files_size("./"));
	//printf("Size of files in '.': %s\n", better_size(get_files_size("include")));
	printf("Size of files in '.': %s\n", better_size(get_full_dir_size(".")));
	
	printf("%s\n", list_files("./"));
	
	return 0;
}
