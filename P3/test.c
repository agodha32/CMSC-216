#include <stdio.h>
#include <string.h>
#include "document.h"

int main() {

	Document doc; 
	const char *doc_name = "Exercise Description";

	init_document(&doc, doc_name);

	load_file(&doc, "doc1.txt" );
 	print_document(&doc);

	return 0;
}
