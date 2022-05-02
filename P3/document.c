#include "document.h"
#include <stdio.h>
#include <string.h>

int init_document(Document *doc, const char *name) {

	int length =  1000;

	length = (name != NULL) ? strlen(name) : 1000; 

	if(doc == NULL || length > MAX_STR_SIZE || length < 1) {

		return FAILURE;

	} else {

		doc->number_of_paragraphs = 0;
		strcpy(doc->name, name);
		
		return SUCCESS;

	}

}

int reset_document(Document *doc) {

	if(doc == NULL) {

		return FAILURE;

	} else {

		doc->number_of_paragraphs = 0;

		return SUCCESS;

	}

}

int print_document(Document *doc) {

	int num_para = 100, para_count, num_line = 100, line_count;

	if(doc == NULL) {

		return FAILURE;

	} else {

		num_para = doc->number_of_paragraphs;

		printf("Document name: \"%s\"\n", doc->name);
		printf("Number of Paragraphs: %d\n", num_para);

		for(para_count = 0; para_count < num_para; para_count++) {
			
			if(doc->paragraphs[para_count].number_of_lines > 0) {
	
				num_line = doc->paragraphs[para_count].number_of_lines;	
	
				for(line_count = 0; line_count < num_line; line_count++) {

					printf("%s\n", doc->paragraphs[para_count].lines[line_count]);

				}	


			}
			
			if(para_count < (num_para - 1)) {

				printf("\n");

			}

		}

		return SUCCESS;

	}

}

int add_paragraph_after(Document *doc, int paragraph_number) {

	int middle = 0, num_para = 0;

	if(doc == NULL || paragraph_number < 0 || paragraph_number > MAX_PARAGRAPHS || 
		paragraph_number > doc->number_of_paragraphs || doc->number_of_paragraphs == MAX_PARAGRAPHS) {

		return FAILURE;

	} else {

		num_para = doc->number_of_paragraphs;

		if(paragraph_number == num_para) {

			doc->paragraphs[num_para].number_of_lines = 0;

		} else {

			for(middle = num_para; middle >= paragraph_number; middle--) {

				doc->paragraphs[middle + 1] = doc->paragraphs[middle];

			}

			doc->paragraphs[paragraph_number].number_of_lines = 0;

		}

		doc->number_of_paragraphs++;

		return SUCCESS;

	}

}

int add_line_after(Document *doc, int paragraph_number, int line_number, const char *new_line) {

	int line = 0, num_para = 50, num_line;

	if(doc == NULL || new_line == NULL) { 
		return FAILURE;

	}

	num_para = doc->number_of_paragraphs;
	num_line = doc->paragraphs[paragraph_number - 1].number_of_lines;

	if(paragraph_number < 0 || paragraph_number > num_para || line_number < 0|| 
		num_line >= MAX_PARAGRAPH_LINES || line_number > num_line) {

		return FAILURE;

	}	

	if(line_number == num_line) {

		strcpy(doc->paragraphs[paragraph_number - 1].lines[line_number], new_line);

	} else {

		for(line = num_line; line >= line_number; line--) {

			strcpy(doc->paragraphs[paragraph_number - 1].lines[line + 1],
				doc->paragraphs[paragraph_number - 1].lines[line]); 
	
		}

		strcpy(doc->paragraphs[paragraph_number - 1].lines[line_number],
			new_line);

	}

	doc->paragraphs[paragraph_number - 1].number_of_lines++;

	return SUCCESS;

}

int get_number_lines_paragraph(Document *doc, int paragraph_number, int *number_of_lines) {


	if(doc == NULL || number_of_lines == NULL || paragraph_number < 0 ||
		paragraph_number > doc->number_of_paragraphs) {

		return FAILURE;

	} else {

		*number_of_lines = doc->paragraphs[paragraph_number - 1].number_of_lines;	

		return SUCCESS;

	}		

}

int append_line(Document *doc, int paragraph_number, const char *new_line) {

	int num_para = 50, num_line;

	if(doc == NULL || new_line == NULL) { 

		return FAILURE;

	}

	num_para = doc->number_of_paragraphs;
	num_line = doc->paragraphs[paragraph_number - 1].number_of_lines;

	if(paragraph_number < 0 || paragraph_number > num_para) {

		return FAILURE;

	}	

	add_line_after(doc, paragraph_number, num_line, new_line);

	return SUCCESS;

}

int remove_line(Document *doc, int paragraph_number, int line_number) {

	int num_line = 0, i;

	if(doc == NULL || paragraph_number < 0 || paragraph_number > doc->number_of_paragraphs ||
		line_number < 0 || line_number > doc->paragraphs[paragraph_number - 1].number_of_lines) {

		return FAILURE;

	}

	num_line = doc->paragraphs[paragraph_number - 1].number_of_lines;

	for(i = line_number - 1; i < (num_line - 1); i++) {

			strcpy(doc->paragraphs[paragraph_number - 1].lines[i], 
				doc->paragraphs[paragraph_number - 1].lines[i + 1]);

	}  
	
	doc->paragraphs[paragraph_number - 1].number_of_lines--;

	return SUCCESS;

}


int load_document(Document *doc, char data[][MAX_STR_SIZE + 1], int data_lines) {

	int x, para = 0, line = 0;

	if(doc == NULL || data == NULL || data_lines == 0) {

		return FAILURE;

	}

	add_paragraph_after(doc, para);

	for(x = 0; x < data_lines; x++) {

		if(strcmp(data[x], "") == 0) {

			para++;
			line = 0;
			add_paragraph_after(doc, para);			

		} else {

			add_line_after(doc, para + 1, line, data[x]);
			line++;

		}

	}

	return SUCCESS;

}

int replace_text(Document *doc, const char *target, const char *replacement) {

	int i, j, num_para = 0, num_line = 0, len_t = 0, len_r = 0;
	char *found ,temp[MAX_STR_SIZE + 1] = "\0";
	
	if(doc == NULL || target == NULL || replacement ==  NULL) {

		return FAILURE;

	} else {

		num_para = doc->number_of_paragraphs;
		len_t = strlen(target);
		len_r = strlen(replacement);

		for(i = 0; i < num_para; i++) {

			num_line = doc->paragraphs[i].number_of_lines;

			for(j = 0; j < num_line; j++) {

				found = strstr(doc->paragraphs[i].lines[j], target);

				while(found != NULL) {

					strcpy(temp, found);
					strcpy(found, "");
					strcat(found, replacement);
					strcat(found + len_r, temp + len_t);

					found = strstr(found + len_r, target);

				}

			}

		}

		return SUCCESS;

	}

}

int highlight_text(Document *doc, const char *target) {

	char to_add[MAX_STR_SIZE + 1] = "";

	if(doc ==  NULL || target == NULL) {

		return FAILURE;

	} else {

		strcat(to_add, HIGHLIGHT_START_STR);
		strcat(to_add, target);
		strcat(to_add, HIGHLIGHT_END_STR);

		replace_text(doc, target, to_add);

		return SUCCESS;

	}

}

int remove_text(Document *doc, const char *target) {

	if(doc == NULL || target == NULL) {

		return FAILURE;

	} else {

		replace_text(doc, target, "");
		
		return SUCCESS;

	}

}

int ri_memset(char *command, int size) {

	int i;

	for(i = 0; i < size; i++) {

		command[i] = '\0';

	}

	return SUCCESS;

}

int load_file(Document *doc, const char *filename) {

	int para = 0, line = 0; 
	char input_read[MAX_STR_SIZE + 1] = "", insert[MAX_STR_SIZE + 1] = "";
	FILE *input = fopen(filename, "r");

	if(doc == NULL || filename == NULL || input == NULL) {

		return FAILURE;

	}

	add_paragraph_after(doc, para);
	
	while(fgets(input_read, MAX_STR_SIZE + 1, input) != NULL) {

		strncpy(insert, input_read, strlen(input_read) - 1); 

		if(strcmp(insert, "") == 0 || strcmp(insert, " ") == 0) {

			para++;
			line = 0;
			add_paragraph_after(doc, para);			

		} else {

			add_line_after(doc, para + 1, line, insert);
			line++;

		}

		ri_memset(insert, MAX_STR_SIZE + 1);
		ri_memset(input_read, MAX_STR_SIZE +1);
	}

	return SUCCESS;

}


int save_document(Document *doc, const char *filename) {

	int num_para = 0, num_line = 0, x, y;
	FILE *output = fopen(filename, "w"); 

	if(doc == NULL || filename == NULL || output == NULL) {

		return FAILURE;

	}

	num_para = doc->number_of_paragraphs;

	for(x = 0; x < num_para; x++) {

		num_line = doc->paragraphs[x].number_of_lines;

		for(y = 0; y < num_line; y++) {

			fputs(doc->paragraphs[x].lines[y], output);
			
			if(y < num_line) {

				fputs("\n", output);

			}	

		}

		if((x + 1) < num_para) {

			fputs("\n", output);

		}

	}

	fclose(output);
	return SUCCESS;

}
