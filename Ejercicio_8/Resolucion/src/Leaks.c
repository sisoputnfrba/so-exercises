/*
 * Copyright (C) 2012 Sistemas Operativos - UTN FRBA. All rights reserved.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "Factura.h"

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char **argv) {
	char* folder = "resources";
	char* file_name = "ticket.txt";
	char* absolute_path = malloc(strlen(folder) + strlen("/") + strlen(file_name) + 1);
	sprintf(absolute_path, "%s/%s", folder, file_name);

	FILE* file = fopen(absolute_path, "r");
	t_factura* factura = factura_from_file(file);
	factura_print(factura);

	factura_destroy(factura);
	fclose(file);
	free(absolute_path);

	return EXIT_SUCCESS;
}

