/* Implement your shell here */
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sysexits.h> 
#include <err.h> 
#include <unistd.h>    
#include <sys/types.h>
#include <string.h>

# define MAX_STR_LEN 1024

int main () {

	int quit = 0;
	char total[MAX_STR_LEN + 1] = "", arg_one[MAX_STR_LEN + 1] = "", arg_two[MAX_STR_LEN + 1] = "";
	pid_t pid;
	char * arv[3];

	printf("shell_jr: ");
	fflush(stdout);

	if(fgets(total, MAX_STR_LEN + 1, stdin) == NULL) {

		quit = 1;

	}

	sscanf(total, "%s%s", arg_one, arg_two);

	if(strcmp(arg_one, "exit") == 0 || strcmp(arg_one, "hastalavista") == 0) {

		printf("See you\n");
		fflush(stdout);
		exit(0);

	}	

	while(quit != 1) {	

		if(strcmp(arg_one, "cd") == 0) {

			if(chdir(arg_two) != 0) {

				printf("Cannot change directory to %s", arg_two);
				fflush(stdout);
			}

		} else {

			if((pid = fork()) < 0) {

				err(EX_OSERR, "fork error");

			}
			
			if(pid) {

				wait(NULL);

			} else {
				arv[0] = arg_one;
				arv[1] = arg_two;
				arv[2] = NULL;
				execvp(arg_one, arv);					
				printf("Failed to execute %s", total);
				fflush(stdout);
				exit(EX_OSERR);

			}

		}

		memset(total, 0, MAX_STR_LEN);
		memset(arg_one, 0, MAX_STR_LEN);
		memset(arg_two, 0, MAX_STR_LEN);

		printf("shell_jr: ");
		fflush(stdout);
		if(fgets(total, MAX_STR_LEN + 1, stdin) == NULL) {

			quit = 1;

		}

		sscanf(total, "%s%s", arg_one, arg_two);	

		if(strcmp(arg_one, "exit") == 0 || strcmp(arg_one, "hastalavista") == 0) {

			printf("See you\n");
			fflush(stdout);
			exit(0);

		}	

	}
	
	return 0;

}
