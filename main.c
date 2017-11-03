#include<stdio.h>

#include"include/dir_stuff.h"

int main() {

	//printf("Size of files in '.': %s\n", better_size(get_files_size("include")));
	printf("Size of files (du -abc method) in '.': %s\n", better_size(my_du_abc(".")));
	//printf("Size of files (du -abc method) in '.': %lu\n", my_du_abc("."));
	
	printf("Simple size of files in '.': %lu\n", get_files_size("."));
	
	printf("%s\n", list_files("./"));
	
	return 0;
}
