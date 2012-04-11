/*
 * Cliente.c
 *
 *  Created on: Apr 10, 2012
 *      Author: shinichi
 */

#include "Cliente.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define CLIENTE_NAME_MAX_LENGTH 256

t_cliente* cliente_create(char* nombre, char* apellido, int codigo_cliente) {
	t_cliente* cliente = malloc(sizeof(t_cliente));
	cliente->nombre = nombre;
	cliente->apellido = apellido;
	cliente->codigo_cliente = codigo_cliente;

	return cliente;
}

void cliente_destroy(t_cliente* cliente) {
	free(cliente->nombre);
	free(cliente->apellido);
	free(cliente);
}

t_cliente* cliente_from_file(FILE* file) {
	char* nombre = malloc(CLIENTE_NAME_MAX_LENGTH);
	char* apellido = malloc(CLIENTE_NAME_MAX_LENGTH);
	int codigo_cliente = 0;
	fscanf(file, "%d,%[^,],%s\n", &codigo_cliente, nombre, apellido);
	return cliente_create(nombre, apellido, codigo_cliente);
}
