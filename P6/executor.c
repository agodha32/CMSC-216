/*
 	Student id: 117123173
 */

#include <stdio.h>
#include "command.h"
#include "executor.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sysexits.h>
#include <fcntl.h>
#include <err.h>

/*
 * static void print_tree(struct tree *t);
 */

static int implement_exe(struct tree *t, int parent_input_fd, int output_parent_fd); 

int execute(struct tree *t) {

	if(t != NULL) {

		return implement_exe(t, -1, -1); 

	} else {

		return 0;
	
	}

}

static int implement_exe(struct tree *t, int parent_input_fd, int output_parent_fd) {

	pid_t pid;
	int stat, pass, pipe_file[2];

	if(t->conjunction == NONE) {

		if(strcmp(t->argv[0], "cd") == 0) {

			if(t->argv[1] != NULL && chdir(t->argv[1]) == -1) {

				perror(t->argv[1]);

			}

		} else if(strcmp(t->argv[0], "exit") == 0) {

			exit(0);

		} else {

			pid = fork();

			if(pid < 0) {

				err(EX_OSERR, "fork error");
				exit(1);

			}

			if(pid != 0) {

				wait(&stat);
				return stat;

			} 

			if(pid == 0) {

				if(t->input != NULL) {

					parent_input_fd = open(t->input, O_RDONLY);

					if(parent_input_fd == -1) {

						err(EX_OSERR, "Can't open input file");
						exit(1);

					} else {

						if(dup2(parent_input_fd, STDIN_FILENO) < 0) {

							err(EX_OSERR, "dup2 error");
							exit(1);

						}

						close(parent_input_fd);

					}

				}

				if(t->output != NULL) {

					output_parent_fd = open(t->output, O_WRONLY | O_TRUNC | O_CREAT, 0664);
					
					if(output_parent_fd == -1) {

						err(EX_OSERR, "Can't open output file");
						exit(1);

					} else {

						if(dup2(output_parent_fd, STDOUT_FILENO) < 0) {

							err(EX_OSERR, "dup2 error");
							exit(1);

						}

						close(output_parent_fd);

					}

				}			

				execvp(t->argv[0], t->argv);
				fprintf(stderr, "Failed to execute %s.\n", t->argv[0]);
				fflush(stdout);
				exit(EX_OSERR);

			}

		}

	} else if(t->conjunction == AND) {

		if(t->input != NULL) {

			parent_input_fd = open(t->input, O_RDONLY);

			if(parent_input_fd == -1) {

				err(EX_OSERR, "Can't open input file");

			}

		}

		if(t->output != NULL) {

			output_parent_fd = open(t->output, O_WRONLY | O_TRUNC | O_CREAT, 0664);
					
			if(output_parent_fd == -1) {

				err(EX_OSERR, "Can't open output file");

			} 

		}

		pass = implement_exe(t->left, parent_input_fd, output_parent_fd);

		if(pass == 0) {

			implement_exe(t->right, parent_input_fd, output_parent_fd);

		}
			

	} else if(t->conjunction == PIPE) {

		if(t->left != NULL && t->left->output != NULL) {

			printf("Ambiguous output redirect.\n");
			fflush(stdout);

		} else if(t->right != NULL && t->right->input != NULL) {

			printf("Ambiguous input redirect.\n");
			fflush(stdout);

		}

		pipe(pipe_file);

		pid = fork();
		
		if(pid < 0) {

			err(EX_OSERR, "fork error");
			exit(1);

		}			

		if(pid == 0) {

			close(pipe_file[0]);

			if(dup2(pipe_file[1], STDOUT_FILENO) < 0) {

				err(EX_OSERR, "dup2 error");
				exit(1);

			}

			if(t->left->input != NULL) {

				parent_input_fd = open(t->left->input, O_RDONLY);

				if(parent_input_fd < 0) {

					err(EX_OSERR, "Input file can not be opened");
					exit(1);

				}

			}

			implement_exe(t->left, parent_input_fd, pipe_file[1]);
			close(pipe_file[1]);
			exit(0);

		}

		if(pid != 0) {

			close(pipe_file[1]);
			
			if(dup2(pipe_file[0], STDIN_FILENO) < 0) {

				err(EX_OSERR, "dup2 error");
				exit(1);

			}

			if(t->right->output != NULL) {

				output_parent_fd = open(t->right->output, O_WRONLY | O_TRUNC | O_CREAT, 0664);

				if(output_parent_fd < 0) {

					err(EX_OSERR, "Output file can not be opened");
					exit(1);

				}

			}

			implement_exe(t->right, pipe_file[0], output_parent_fd);
			close(pipe_file[0]);
			wait(NULL);

		}

	} else if(t->conjunction == SUBSHELL) {

		pid = fork();

		if(pid < 0) {

			err(EX_OSERR, "fork error");
			exit(1);

		}

		if(pid != 0) {

			wait(&stat);

		 } 

		if(pid == 0) {

			
			if(t->input != NULL) {

				parent_input_fd = open(t->input, O_RDONLY);

				if(parent_input_fd < 0) {

					err(EX_OSERR, "Unable to open input");
					exit(1);

				}

			}

			if(t->output != NULL) {

				output_parent_fd = open(t->input, O_WRONLY | O_TRUNC | O_CREAT, 0664);

				if(output_parent_fd < 0) {

					err(EX_OSERR, "Unable to open output");
					exit(1);

				}

			}

			implement_exe(t->left, parent_input_fd, output_parent_fd);
			exit(0);

		}

	}

	return 0;

}

/*
 * static void print_tree(struct tree *t) {
 * 	
 * 		if (t != NULL) {
 *
 * 		        	print_tree(t->left);
 *
 * 		        	        	if (t->conjunction == NONE) {
 *
 * 		        	        				 printf("NONE: %s, ", t->argv[0]);
 *
 * 		        	        				 		} else {
 *
 * 		        	        				 					printf("%s, ", conj[t->conjunction]);
 *
 * 		        	        				 					        	}
 *
 * 		        	        				 					        	        	printf("IR: %s, ", t->input);
 * 		        	        				 					        	        	        	printf("OR: %s\n", t->output);
 * 		        	        				 					        	        	        			print_tree(t->right);
 *
 * 		        	        				 					        	        	        				}
 *
 * 		        	        				 					        	        	        				}
 * 		        	        				 					        	        	        				*/

