#include <string.h>
#include <stdio.h>
#include <stdlib.h>

void HeaderSplit_(char* body, char* name, char* resolve){
		
	char *ptr = strtok(body, "\r\n");
	while(ptr != NULL){
		ptr = strtok(NULL, "\r\n");
		if(ptr != NULL && strstr(ptr, name) != NULL){
			char *namesplit = strtok(ptr, " ");
			namesplit = strtok(NULL, " "); // 
			
			puts(namesplit);
			sprintf(resolve, "%s", namesplit);
		}
	}
};

// V2 
//Use "http" at the beginning because Header_Name is irregular
int HeaderSplit_to_Url(char* body, char* name, char* resolve){
	char* r_cpy = (char*)malloc(sizeof(char) * strlen(body));
	char* check;
	sprintf(r_cpy, "%s", body);
	char *ptr = strtok(r_cpy, "\r\n");
	while(ptr != NULL){
		ptr = strtok(NULL, "\r\n");
		if(ptr != NULL && strstr(ptr, name) != NULL){
			check = strstr(ptr, name);
			if(check == NULL) return -1;
			sprintf(resolve, "%s", check);
			free(r_cpy);
			break; // 
		}
	}
	return 0;
}
