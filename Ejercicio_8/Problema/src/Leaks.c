/*
 * Runner.c
 *
 *  Created on: Apr 10, 2012
 *      Author: shinichi
 */

#include "Factura.h"

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char **argv) {
	char* folder = "resources";
	char* file_name = "ticket.txt";
	char* absolute_path = malloc(strlen(folder) + strlen("/") + strlen(file_name));
	sprintf(absolute_path, "%s/%s", folder, file_name);

	FILE* file = fopen(absolute_path, "r");
	t_factura* factura = factura_from_file(file);
	factura_print(factura);

	factura_destroy(factura);
	fclose(file);
	free(absolute_path);

	return EXIT_SUCCESS;
}

