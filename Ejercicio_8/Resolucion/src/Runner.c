/*
 * Runner.c
 *
 *  Created on: Apr 10, 2012
 *      Author: shinichi
 */

#include <stdio.h>
#include "Factura.h"
#include <unistd.h>

int main(int argc, char **argv) {
	FILE* file = fopen("resources/ticket.txt", "r");
	t_factura* factura = factura_from_file(file);
	factura_print(factura);
	factura_destroy(factura);
	fclose(file);
	return 0;
}

