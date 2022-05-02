#include "photo_album.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

Photo *create_photo(int id, const char *description) {

	Photo *to_return = malloc(sizeof(Photo));

	if(to_return == NULL) {

		return NULL;

	}

	if(description == NULL) {

		to_return->description = NULL;

	} else {	

		to_return->description = malloc(strlen(description) + 1);
		
		if(to_return->description == NULL) {

			return NULL;

		}

		strcpy(to_return->description, description);

	}

	to_return->id = id;

	return to_return;

}

void print_photo(Photo *photo) {

	if(photo != NULL && photo->description != NULL) {

		printf("Photo Id: %d, Description: %s\n", photo->id, photo->description);

	} else if(photo != NULL && photo->description == NULL) {

		printf("Photo Id: %d, Description: None\n", photo->id);

	}


}

void destroy_photo(Photo *photo) {

	if(photo != NULL) {

		free(photo->description);
		free(photo);

	}

}

void initialize_album(Album *album) {

	if(album != NULL) {

		album->size = 0;

	}

}

void print_album(const Album *album) {

	int i;

	if(album != NULL) {

		if(album->size == 0) {

			printf("Album has no photos.\n");

		} else {

			for(i = 0; i < album->size; i++) {

				print_photo(album->all_photos[i]);

			}

		}

	}

}

void destroy_album(Album *album) {

	int i;

	if(album != NULL) {

		for(i = 0; i < album->size; i++) {

			destroy_photo(album->all_photos[i]);

		}

	}

	album->size = 0;

}

void add_photo_to_album(Album *album, int id, const char *description) {

	Photo *to_add;

	if(album != NULL && (album->size < MAX_ALBUM_SIZE)) {

		to_add = create_photo(id, description);

		album->all_photos[album->size] = to_add;

		album->size++;

	}

}
