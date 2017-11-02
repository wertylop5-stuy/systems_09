#include<stdio.h>

#include"include/dir_stuff.h"

int main() {
	printf("%s\n", list_files("./"));
	
	return 0;
}
