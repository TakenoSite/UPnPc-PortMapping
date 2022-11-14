#include <stdio.h>
#include <string.h>
#include <stdlib.h>

static int char_int(char* str_){
	int to_int;
	sscanf(str_,"%d",&to_int);
	return to_int;
}


int status_check(char* r){
	short int_status_code;
	char* r_cpy = (char*)malloc(sizeof(char) * strlen(r)+32);
	if(r_cpy == NULL){
		return -1;
	};

	sprintf(r_cpy,"%s",r);

	char *ptr = strtok(r_cpy, "\r\n");
	char *status_code = strtok(ptr, " ");
	status_code = strtok(NULL, " ");
	int_status_code = char_int(status_code);
	free(r_cpy);

	return int_status_code;
}


