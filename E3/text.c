#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "photo_album.h"
#include "my_memory_checker_216.h"

int main() {

	Album album;
	Photo *to;  
 
	start_memory_check(); /* Start memory check */

	initialize_album(&album);

	to = create_photo(1, NULL);	

	print_photo(to);

	print_album(&album);

	destroy_album(&album);
	destroy_photo(to);

	stop_memory_check(); /* End memory check */

	return EXIT_SUCCESS;

}
