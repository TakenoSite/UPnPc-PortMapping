#include <stdio.h>
#include <string.h>
#include <stdlib.h>

static void revStr(char* str){
    int size = strlen(str);
    int i,j;
    char tmp = {0};
    
    for(i=0, j=size - 1; i<size / 2; i++, j--){
        tmp = str[i];
        str[i] = str[j];
        str[j] = tmp;
    }
    return;    
}


int tag_item_tag(char* r_tag_item, char* id, char* resolve){
	
	char *start_tag = (char*)malloc(sizeof(char) * (strlen(id) + 16));
	char *end_tag = (char*)malloc(sizeof(char) * (strlen(id) + 16));
	char *r= (char*)malloc(sizeof(char) * strlen(r_tag_item) + 32);
	int end_tag_len;
	int start_tag_len;
	char *str_str;
	
	if(start_tag == NULL && end_tag ==NULL && r == NULL) return -3;
	sprintf(r, "%s", r_tag_item);
	sprintf(start_tag, "<%s>",id);
	sprintf(end_tag, "</%s>",id);
	
	revStr(end_tag);
	
	end_tag_len = strlen(end_tag);
	start_tag_len = strlen(start_tag);
	
	revStr(r);
	str_str = strstr(r, end_tag);
	free(end_tag);
	if(str_str != NULL){
		sprintf(r,"%s", &str_str[end_tag_len]);
	}else{
		free(start_tag);
		free(r);
		return -1;
	}
	
	revStr(r);
	str_str = strstr(r, start_tag);
	free(start_tag);
	if(str_str != NULL){
		sprintf(r, "%s", &str_str[start_tag_len]);
		//puts(r);
		sprintf(resolve, "%s", r);
		free(r);
	}else{
		free(r);
		return -2;
	}
	
	return 0;
}


