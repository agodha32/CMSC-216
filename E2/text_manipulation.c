#include <stdio.h>
#include <string.h>
#include "text_manipulation.h"
#define MAX_LEN 80

int remove_spaces(const char *source, char *result, int *num_spaces_removed) {  

	int str_len = 0;
	int str_tra = 0;
	int new_str = 0;
	int spaces_removed = 0;
	int result_it = 0;

	if(source == NULL || strlen(source) == 0) {

		return FAILURE;

	}

	
	str_tra = strlen(source) - 1;

	while(source[str_len] == ' ') {

		spaces_removed++;
		str_len++;

	}	

	while(source[str_tra] == ' ') {

		spaces_removed++;
		str_tra--;

	}

	for(new_str = str_len; new_str <= str_tra; new_str++) {

		result[result_it] = source[new_str];
		result_it++;

	}

	result[result_it] = '\0';
    
	if(num_spaces_removed != NULL) {

		*num_spaces_removed = spaces_removed;

	}


    return SUCCESS;

}

int center(const char *source, int width, char *result) {       

	int str_len, after_space = 0, space_added = 0, space_to_add = 0;

	if(source == NULL || strlen(source) == 0 || width < strlen(source)) {

		return FAILURE;

	}
    
	space_to_add = ((width - strlen(source)) / 2);

	for(str_len = 0; str_len < space_to_add; str_len++) {

		result[str_len] = ' ';

	}

	for(after_space = 0; after_space < strlen(source); after_space++) {

		result[str_len] = source[after_space];
		str_len++;

	}
   
	space_added = str_len;

	for(str_len = 0; str_len < space_to_add; str_len++) {

		result[space_added] = ' ';
		space_added++;

	}

	result[space_added] = '\0';

	return SUCCESS;

}
