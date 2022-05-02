#include  <stdio.h>
#include  <string.h>
#include  <sysexits.h>
#include  <stdlib.h>
#include  <ctype.h>
#include  "document.h"

int rip_memset(char *line, int size);
int follow_command(Document *doc, char *command);
int exe_add_paragraph_after(Document *doc, char *command);
int exe_add_line_after(Document *doc, char *command);
int exe_print_document(Document *doc, char *command);
int exe_append_line(Document *doc, char *command);
int exe_remove_line(Document *doc, char *command);
int exe_load_file(Document *doc, char *command);
int exe_replace_text(Document *doc, char *command);
int exe_highlight_text(Document *doc, char *command);
int exe_remove_text(Document *doc, char *command);
int exe_save_document(Document *doc, char *command);
int exe_reset_document(Document *doc, char *command);

int main(int argc, char* argv[]) {

	Document doc;
	FILE *input = stdin;
	const char* doc_name = "main_document";

	char command[MAX_STR_SIZE + 1] = "", command_two[MAX_STR_SIZE + 1] = "";

	if(init_document(&doc, doc_name) == FAILURE) {

		printf("Initialization Failed\n");

	} else {
	
		if(argc == 1) {
	
			printf("> ");

			fgets(command, MAX_STR_SIZE + 1, stdin);

			while((strcmp(command, "quit\n") != 0) && (strcmp(command, "exit\n") != 0)) {

				sscanf(command, "%s", command_two);

				if(command_two[0] != '#' && strlen(command_two) != 0) {


					follow_command(&doc, command);

				}

				printf("> ");

				rip_memset(command, MAX_STR_SIZE + 1);
				rip_memset(command_two, MAX_STR_SIZE + 1); 

				fgets(command, MAX_STR_SIZE + 1, stdin);

			} 	

		} else if(argc == 2) {

			input = fopen(argv[1], "r");

			if(input == NULL) {

				fprintf(stderr, "%s cannot be opened.\n", argv[1]);
				exit(EX_OSERR);

			} else {

				while(fgets(command, MAX_STR_SIZE + 1, input) != NULL) {

					if((strcmp(command, "quit\n") != 0) && (strcmp(command, "exit\n") != 0)) {

						sscanf(command, " %s", command_two);

						if(command_two[0] != '#' && strlen(command_two) != 0) {

							follow_command(&doc, command);

						}

					}

					rip_memset(command, MAX_STR_SIZE + 1);
					rip_memset(command_two, MAX_STR_SIZE + 1); 

				}

			} 

		} else {
	
			fprintf(stderr, "Usage: user_interface\n");
			fprintf(stderr, "Usage: user_interface %s", argv[1]);
			exit(EX_USAGE);	

		}

	}

	fclose(input);

	exit(EXIT_SUCCESS);


}

int rip_memset(char *line, int size) {

	int i;

	for(i = 0; i < size; i++) {

		line[i] = '\0';

	}

	return SUCCESS;
} 


int follow_command(Document *doc, char* command) {

	int stat = FAILURE;

	if((strcmp(command, "quit\n") != 0 && strstr(command, "quit") != NULL) || 
	(strcmp(command, "exit\n") != 0 && strstr(command, "exit") != NULL)) {



	} else if(strstr(command, "add_paragraph_after") != NULL) {

		stat = exe_add_paragraph_after(doc, command);

	}  else if(strstr(command, "add_line_after") != NULL) {

		stat = exe_add_line_after(doc, command);

	} else if(strstr(command, "print_document") != NULL) {

		stat = exe_print_document(doc, command);

	} else if(strstr(command, "append_line") != NULL) {

		stat = exe_append_line(doc, command);

	} else if(strstr(command, "remove_line") != NULL) {

		stat = exe_remove_line(doc, command);

	} else if(strstr(command, "load_file") != NULL) {

		stat = exe_load_file(doc, command);

	} else if(strstr(command, "replace_text") != NULL) {

		stat = exe_replace_text(doc, command);

	} else if(strstr(command, "highlight_text") != NULL) {

		stat = exe_highlight_text(doc, command);

	} else if(strstr(command, "remove_text") != NULL) {

		stat = exe_remove_text(doc, command);

	} else if(strstr(command, "save_document") != NULL) {

		stat = exe_save_document(doc, command);

	} else if(strstr(command, "reset_document") != NULL) {

		stat = exe_reset_document(doc, command);

	}

	if(stat == FAILURE) {

		printf("Invalid Command\n");

	}

	return SUCCESS;

}

int exe_add_paragraph_after(Document *doc, char *command) {

	char c_name[MAX_STR_SIZE + 1] = "", extra[MAX_STR_SIZE + 1] = "";
	int para_num = -1;

	if(sscanf(command, " %s%d%s", c_name, &para_num, extra) == 2 && para_num >= 0) {

		if(add_paragraph_after(doc, para_num) == FAILURE) {

			printf("add_paragraph_after failed\n");

		}

		return SUCCESS;

	} else {

		return FAILURE;

	}

}

int exe_add_line_after(Document *doc, char *command) {

	char c_name[MAX_STR_SIZE + 1] = "", line[MAX_STR_SIZE + 1] = "", no_next_line[MAX_STR_SIZE + 1] = "";
	int para_num = -1, line_num = -1;

	if(sscanf(command, "%s%d%d%s", c_name, &para_num, &line_num, line) == 4 && strstr(command, "*") != NULL
		&& para_num > 0 && line_num >= 0) {

		strcpy(line, strchr(command, '*') + 1);
		strncpy(no_next_line, line,  strlen(line) - 1);

		if(add_line_after(doc, para_num, line_num, no_next_line) == FAILURE) {

			printf("add_line_after failed\n");

		}

		return SUCCESS;

	} else {

		return FAILURE;

	}	

	return SUCCESS;	

}

int exe_print_document(Document *doc, char *command) {

	char c_name[MAX_STR_SIZE + 1] = "", extra[MAX_STR_SIZE + 1] = "";

	if(sscanf(command, "%s%s", c_name, extra) == 1) {

		if(print_document(doc) == FAILURE) {

			printf("print_document failed\n");

		}

		return SUCCESS;

	} else {

		return FAILURE;

	}

}



int exe_append_line(Document *doc, char *command) {

	char c_name[MAX_STR_SIZE + 1] = "", line[MAX_STR_SIZE + 1] = "", no_next_line[MAX_STR_SIZE + 1] = "";
	int para_num = -1;

	if(sscanf(command, "%s%d%s", c_name, &para_num, line) == 3 && strstr(command, "*") != NULL && para_num > 0) {

		strcpy(line, strchr(command, '*') + 1);
		strncpy(no_next_line, line,  strlen(line) - 1);


		if(append_line(doc, para_num, no_next_line) == FAILURE) {

			printf("append_line failed\n");

		}

		return SUCCESS;

	} else {

		return FAILURE;

	}

}


int exe_remove_line(Document *doc, char *command) {

	char c_name[MAX_STR_SIZE + 1] = "", extra[MAX_STR_SIZE + 1] = "";
	int para_num = -1, line_num = -1;

	if(sscanf(command, "%s%d%d%s", c_name, &para_num, &line_num, extra) == 3 && para_num > 0 && line_num > 0) {

		if(remove_line(doc, para_num, line_num) == FAILURE) {

			printf("remove_line failed\n");

		}

		return SUCCESS;

	} else {

		return FAILURE;

	}

}

int exe_load_file(Document *doc, char *command) {

	char c_name[MAX_STR_SIZE + 1] = "", file_n[MAX_STR_SIZE + 1] = "", extra[MAX_STR_SIZE + 1] = "";
	
	if(sscanf(command, "%s%s%s", c_name, file_n, extra) == 2) {

		if(load_file(doc, file_n) == FAILURE) {

			printf("load_file failed\n");

		}

		return SUCCESS;

	} else {

		return FAILURE;

	}
}

int exe_replace_text(Document *doc, char *command) {

	char c_name[MAX_STR_SIZE + 1] = "", target[MAX_STR_SIZE + 1] = "", replace[MAX_STR_SIZE + 1] = "";
	char *target_s, *target_e, *replace_s, *replace_e;
	char final_target[MAX_STR_SIZE + 1] = "", final_replace[MAX_STR_SIZE + 1] = "";

	if(sscanf(command, "%s%s%s", c_name, target, replace) == 3 ) {

		target_s = strstr(command, "\"");
	
		if(target_s  != NULL) {

			target_e = strstr(target_s + 1, "\"");

			if(target_e != NULL) {

				replace_s = strstr(target_e + 1, "\"");

				if(replace_s != NULL) {

					replace_e = strstr(replace_s + 1, "\"");

					if(replace_e != NULL) {	

						strncpy(final_target, target_s + 1, target_e - target_s);
						strncpy(final_replace, replace_s + 1, replace_e - replace_s);

						final_target[strlen(final_target) - 1] = '\0';
						final_replace[strlen(final_replace) - 1] = '\0';

		
						if(replace_text(doc, final_target, final_replace) == FAILURE) {

							printf("replace_text failed\n");
						}

						return SUCCESS;

					}

				}

			}

		}

	} else {

		return FAILURE;

	}

}


int exe_highlight_text(Document *doc, char *command) {

	char c_name[MAX_STR_SIZE + 1] = "", target[MAX_STR_SIZE + 1] = "";
	char *target_s, *target_e, final_target[MAX_STR_SIZE + 1] = "";

	if(sscanf(command,"%s%s", c_name, target) == 2) {

		target_s = strstr(command, "\"");
	
		if(target_s  != NULL) {

			target_e = strstr(target_s + 1, "\"");

			if(target_e != NULL) {

				strncpy(final_target, target_s + 1, target_e - target_s);

				final_target[strlen(final_target) - 1] = '\0';

			}
	
			highlight_text(doc, final_target);

			return SUCCESS;	

		}
	
	} else {

		return FAILURE;

	}

}

int exe_remove_text(Document *doc, char *command) {

	char c_name[MAX_STR_SIZE + 1] = "", target[MAX_STR_SIZE + 1] = "";
	char *target_s, *target_e, final_target[MAX_STR_SIZE + 1] = "";

	if(sscanf(command,"%s%s", c_name, target) == 2) {

		target_s = strstr(command, "\"");
	
		if(target_s  != NULL) {

			target_e = strstr(target_s + 1, "\"");

			if(target_e != NULL) {

				strncpy(final_target, target_s + 1, target_e - target_s);

				final_target[strlen(final_target) - 1] = '\0';

			}

			remove_text(doc, final_target);

			return SUCCESS;	

		}

	} else {

		return FAILURE;

	}

}

int exe_save_document(Document *doc, char *command) {

	char c_name[MAX_STR_SIZE + 1] = "", f_name[MAX_STR_SIZE + 1] = "", extra[MAX_STR_SIZE + 1] = "";
	
	if(sscanf(command, "%s%s%s", c_name, f_name, extra) == 2) {

		if(save_document(doc, f_name) == FAILURE) {


			printf("save_document failed\n");

		}

		return SUCCESS;

	} else {

		return FAILURE;

	}

}

int exe_reset_document(Document *doc, char *command) {

	char c_name[MAX_STR_SIZE + 1] = "", extra[MAX_STR_SIZE + 1] = "";

	if(sscanf(command, "%s%s", c_name, extra) == 1) {

		reset_document(doc);

		return SUCCESS;

	} else {

		return FAILURE;

	}

}
