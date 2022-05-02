#include<stdio.h>

int valid_character(char character);
int draw_rectangle(char character, int width, int length);
int draw_triangle(char character, int size);

int main() {

	int choice = -1, length = -1, width = -1, size = -1;
	char character = 'j';

	while(choice != 0) {

		printf("Enter 1(rectangle), 2(triangle), 3(other), 0(quit): ");
		scanf(" %d", &choice);
		
		if(choice == 0) {

			printf("Bye Bye.\n");		

		} else if(choice == 1) {
			
			printf("Enter character, width and length: ");
			scanf(" %c%d%d", &character, &width, &length);
	
			if(draw_rectangle(character, width, length) == 0) {

				printf("Invalid data provided.\n");

			}

		} else if(choice == 2) {

			printf("Enter character and size: ");
			scanf(" %c%d", &character, &size);
			
			if(draw_triangle(character, size) == 0) {

				printf("Invalid data provided.\n");	
	
			}

		} else if(choice >= 4) {

			printf("Invalid choice.\n");

		}

	} 

	return 0;

}


int valid_character(char character) {

	if(character == '*' || character == '%' ||character == '#') {

		return 1;
	
	} else {

		return 0;

	}

}

int draw_rectangle(char character,int length, int width) {

	int row, col = 0;

	if(valid_character(character) == 1 && length > 0 && width > 0) {

		for(row = 0; row < length; row++) {

			for(col = 0; col < width; col++) {

				printf("%c", character);

			}	
		
			printf("\n");

		}
	
		return 1;

	} else {

		return 0;

	}

}

int draw_triangle(char character, int size) {

	int row, line, space = 0;

	if(valid_character(character) == 1 && size > 0) {

		for(line = 0; line < size; line++) {

			for(space = (size - line); space > 1; space--) {

				printf(" ");
		
			} 

			for(row = 0; row <= (line * 2); row++) {

				printf("%c", character);

			} 

			printf("\n");

		}
	
		return 1;

	} else {

		return 0;

	}

}
